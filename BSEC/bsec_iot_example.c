/*
 * Copyright (C) 2017 Robert Bosch. All Rights Reserved. 
 *
 * Disclaimer
 *
 * Common:
 * Bosch Sensortec products are developed for the consumer goods industry. They may only be used
 * within the parameters of the respective valid product data sheet.  Bosch Sensortec products are
 * provided with the express understanding that there is no warranty of fitness for a particular purpose.
 * They are not fit for use in life-sustaining, safety or security sensitive systems or any system or device
 * that may lead to bodily harm or property damage if the system or device malfunctions. In addition,
 * Bosch Sensortec products are not fit for use in products which interact with motor vehicle systems.
 * The resale and/or use of products are at the purchasers own risk and his own responsibility. The
 * examination of fitness for the intended use is the sole responsibility of the Purchaser.
 *
 * The purchaser shall indemnify Bosch Sensortec from all third party claims, including any claims for
 * incidental, or consequential damages, arising from any product use not covered by the parameters of
 * the respective valid product data sheet or not approved by Bosch Sensortec and reimburse Bosch
 * Sensortec for all costs in connection with such claims.
 *
 * The purchaser must monitor the market for the purchased products, particularly with regard to
 * product safety and inform Bosch Sensortec without delay of all security relevant incidents.
 *
 * Engineering Samples are marked with an asterisk (*) or (e). Samples may vary from the valid
 * technical specifications of the product series. They are therefore not intended or fit for resale to third
 * parties or for use in end products. Their sole purpose is internal client testing. The testing of an
 * engineering sample may in no way replace the testing of a product series. Bosch Sensortec
 * assumes no liability for the use of engineering samples. By accepting the engineering samples, the
 * Purchaser agrees to indemnify Bosch Sensortec from all claims arising from the use of engineering
 * samples.
 *
 * Special:
 * This software module (hereinafter called "Software") and any information on application-sheets
 * (hereinafter called "Information") is provided free of charge for the sole purpose to support your
 * application work. The Software and Information is subject to the following terms and conditions:
 *
 * The Software is specifically designed for the exclusive use for Bosch Sensortec products by
 * personnel who have special experience and training. Do not use this Software if you do not have the
 * proper experience or training.
 *
 * This Software package is provided `` as is `` and without any expressed or implied warranties,
 * including without limitation, the implied warranties of merchantability and fitness for a particular
 * purpose.
 *
 * Bosch Sensortec and their representatives and agents deny any liability for the functional impairment
 * of this Software in terms of fitness, performance and safety. Bosch Sensortec and their
 * representatives and agents shall not be liable for any direct or indirect damages or injury, except as
 * otherwise stipulated in mandatory applicable law.
 *
 * The Information provided is believed to be accurate and reliable. Bosch Sensortec assumes no
 * responsibility for the consequences of use of such Information nor for any infringement of patents or
 * other rights of third parties which may result from its use. No license is granted by implication or
 * otherwise under any patent or patent rights of Bosch. Specifications mentioned in the Information are
 * subject to change without notice.
 *
 * It is not allowed to deliver the source code of the Software to any third party without permission of
 * Bosch Sensortec.
 *
 */

/*!
 * @file bsec_iot_example.c
 *
 * @brief
 * Example for using of BSEC library in a fixed configuration with the BME680 sensor.
 * This works by running an endless loop in the bsec_iot_loop() function.
 */

/*!
 * @addtogroup bsec_examples BSEC Examples
 * @brief BSEC usage examples
 * @{*/

/**********************************************************************************************************************/
/* header files */
/**********************************************************************************************************************/

#include "bsec_integration.h"
#include "bsec_iot_example.h"
#include "bsec_serialized_configurations_iaq.h"

#include <asf.h>
#include <hal_i2c.h>
#include <hal_nvm.h>
#include <radio.h>
#include <sensor_data.h>
#include <string.h>

/**********************************************************************************************************************/
/* functions */
/**********************************************************************************************************************/

/*!
 * @brief           Write operation in either I2C or SPI
 *
 * param[in]        dev_addr        I2C or SPI device address
 * param[in]        reg_addr        register address
 * param[in]        reg_data_ptr    pointer to the data to be written
 * param[in]        data_len        number of bytes to be written
 *
 * @return          result of the bus communication function
 */
static int8_t bus_write(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data_ptr, uint16_t data_len)
{
    return hal_i2c_write(dev_addr, reg_addr, reg_data_ptr, data_len);
}

/*!
 * @brief           Read operation in either I2C or SPI
 *
 * param[in]        dev_addr        I2C or SPI device address
 * param[in]        reg_addr        register address
 * param[out]       reg_data_ptr    pointer to the memory to be used to store the read data
 * param[in]        data_len        number of bytes to be read
 *
 * @return          result of the bus communication function
 */
static int8_t bus_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data_ptr, uint16_t data_len)
{
    return hal_i2c_read(dev_addr, reg_addr, reg_data_ptr, data_len);
}

/*!
 * @brief           System specific implementation of sleep function
 *
 * @param[in]       t_ms    time in milliseconds
 *
 * @return          none
 */
static void sleep(uint32_t t_ms)
{
    vTaskDelay(pdMS_TO_TICKS(t_ms));
}

/*!
 * @brief           Capture the system time in microseconds
 *
 * @return          system_current_time    current system timestamp in microseconds
 */
static int64_t get_timestamp_us(void)
{
    return (int64_t)xTaskGetTickCount() * 1000;
}

/*!
 * @brief           Handling of the ready outputs
 *
 * @param[in]       timestamp       time in nanoseconds
 * @param[in]       iaq             IAQ signal
 * @param[in]       iaq_accuracy    accuracy of IAQ signal
 * @param[in]       temperature     temperature signal
 * @param[in]       humidity        humidity signal
 * @param[in]       pressure        pressure signal
 * @param[in]       raw_temperature raw temperature signal
 * @param[in]       raw_humidity    raw humidity signal
 * @param[in]       gas             raw gas sensor signal
 * @param[in]       bsec_status     value returned by the bsec_do_steps() call
 *
 * @return          none
 */
static void output_ready(int64_t timestamp, float iaq, uint8_t iaq_accuracy, float temperature, float humidity,
     float pressure, float raw_temperature, float raw_humidity, float gas, bsec_library_return_t bsec_status,
     float static_iaq, float co2_equivalent, float breath_voc_equivalent)
{
    char buf[256];

    sprintf(buf,
            "[%d]: IAQ*/st %.3f[%u]/%.3f T*/P/H* %.1f[%.1f]/%.1f/%.1f[%.1f]"
            " GAS %.3f CO2 %.3f VOC %.3f\r\n",
            bsec_status, iaq, iaq_accuracy, static_iaq, temperature,
            raw_temperature, pressure, humidity, raw_humidity, gas,
            co2_equivalent, breath_voc_equivalent);
    dbg_print_str(buf);

    sensor_update_bme680_data(bsec_status, iaq, iaq_accuracy, static_iaq, temperature, pressure, humidity);
    radio_send_bme680_data(bsec_status, iaq, iaq_accuracy, static_iaq, temperature, pressure, humidity);
}

/*!
 * @brief           Load previous library state from non-volatile memory
 *
 * @param[in,out]   state_buffer    buffer to hold the loaded state string
 * @param[in]       n_buffer        size of the allocated state buffer
 *
 * @return          number of bytes copied to state_buffer
 */
static uint32_t state_load(uint8_t *state_buffer, uint32_t n_buffer)
{
    const uint32_t length = hal_nvm_bsec_state_load(state_buffer, n_buffer);

    dbg_print_str(length > 0 ? "bsec state loaded\r\n" : "failed to load bsec state\r\n");

    return length;
}

/*!
 * @brief           Save library state to non-volatile memory
 *
 * @param[in]       state_buffer    buffer holding the state to be stored
 * @param[in]       length          length of the state string to be stored
 *
 * @return          none
 */
static void state_save(const uint8_t *state_buffer, uint32_t length)
{
    if (hal_nvm_bsec_state_save(state_buffer, length) == length)
        dbg_print_str("bsec state saved\r\n");
    else
        dbg_print_str("failed to save bsec state\r\n");
}
 
/*!
 * @brief           Load library config from non-volatile memory
 *
 * @param[in,out]   config_buffer    buffer to hold the loaded state string
 * @param[in]       n_buffer        size of the allocated state buffer
 *
 * @return          number of bytes copied to config_buffer
 */
static uint32_t config_load(uint8_t *config_buffer, uint32_t n_buffer)
{
    const uint32_t bsec_config_size = sizeof(bsec_config_iaq);

    if (n_buffer < bsec_config_size)
        return 0;

    memcpy(config_buffer, bsec_config_iaq, bsec_config_size);
    return bsec_config_size;
}

/*!
 * @brief       Main function which configures BSEC library and then reads and processes the data from sensor based
 *              on timer ticks
 *
 * @return      result of the processing
 */
static int bsec_iot_main(void)
{
    return_values_init ret;
    
    /* Call to the function which initializes the BSEC library 
     * Switch on ultra-low-power mode and provide no temperature offset */
    ret = bsec_iot_init(BSEC_SAMPLE_RATE_ULP, 0.0f, bus_write, bus_read, sleep, state_load, config_load);
    if (ret.bme680_status)
    {
        /* Could not intialize BME680 */
        return (int)ret.bme680_status;
    }
    else if (ret.bsec_status)
    {
        /* Could not intialize BSEC library */
        return (int)ret.bsec_status;
    }
    
    /* Call to endless loop function which reads and processes data based on sensor settings */
    /* State is saved every 864 samples, which means every 864 * 300 secs = 3 days  */
    bsec_iot_loop(sleep, get_timestamp_us, output_ready, state_save, 864);
    
    return 0;
}

void bsec_iot_task(void *params)
{
    (void)bsec_iot_main();
    dbg_print_str("bsec_iot_main finished!\r\n");

    while (1) {}

    (void)params;
}

/*! @}*/
// vim: ts=4 sw=4 fileformat=dos
