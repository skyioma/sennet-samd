/**
 * \file
 *
 * \brief SAM D21 RTC Count (Callback)
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */

#include "hal_rtc.h"

#include <asf.h>

static void rtc_callback(void);

static struct rtc_module rtc_instance;

void rtc_callback()
{
}

void hal_rtc_init()
{
  struct rtc_count_config config_rtc_count;

  rtc_count_get_config_defaults(&config_rtc_count);

  config_rtc_count.prescaler           = RTC_COUNT_PRESCALER_DIV_1;
  config_rtc_count.mode                = RTC_COUNT_MODE_32BIT;
  config_rtc_count.continuously_update = true;

  rtc_count_init(&rtc_instance, RTC, &config_rtc_count);
  rtc_count_register_callback(&rtc_instance, rtc_callback, RTC_COUNT_CALLBACK_COMPARE_0);
}

void vPortSuppressTicksAndSleep(TickType_t xExpectedIdleTime)
{
  SysTick->CTRL = SysTick->CTRL & ~SysTick_CTRL_ENABLE_Msk;

  if (xExpectedIdleTime > 10) {
    rtc_count_set_count(&rtc_instance, 0);
    rtc_count_set_compare(&rtc_instance, xExpectedIdleTime - 3, RTC_COUNT_COMPARE_0);

    rtc_count_enable(&rtc_instance);
    rtc_count_enable_callback(&rtc_instance, RTC_COUNT_CALLBACK_COMPARE_0);

    system_set_sleepmode(SYSTEM_SLEEPMODE_STANDBY);
    system_sleep();

    rtc_count_disable_callback(&rtc_instance, RTC_COUNT_CALLBACK_COMPARE_0);
    rtc_count_disable(&rtc_instance);

    const uint32_t slept_ticks = rtc_count_get_count(&rtc_instance);

    if (slept_ticks <= xExpectedIdleTime) {
      vTaskStepTick(slept_ticks);
    } else {
      // NOTE Fake it!
      vTaskStepTick(xExpectedIdleTime);
    }
  } else {
    delay_ms(xExpectedIdleTime);
    vTaskStepTick(xExpectedIdleTime);
  }

  SysTick->CTRL = SysTick->CTRL | SysTick_CTRL_ENABLE_Msk;
}
