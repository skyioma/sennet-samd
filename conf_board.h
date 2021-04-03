/**
 * \file
 *
 * \brief SAM D21 dummy board configuration.
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef CONF_BOARD_H_INCLUDED
#define CONF_BOARD_H_INCLUDED

#define DEBUG_USART_MODULE             SERCOM1
#define DEBUG_USART_SERCOM_MUX_SETTING USART_RX_1_TX_0_XCK_1
#define DEBUG_USART_SERCOM_PINMUX_PAD0 PINMUX_PA00D_SERCOM1_PAD0
#define DEBUG_USART_SERCOM_PINMUX_PAD1 PINMUX_PA01D_SERCOM1_PAD1
#define DEBUG_USART_SERCOM_PINMUX_PAD2 PINMUX_UNUSED
#define DEBUG_USART_SERCOM_PINMUX_PAD3 PINMUX_UNUSED

// MISO @ PA08
// MOSI @ PA10
// SCK @ PA11
#define SPI_MODULE                     SERCOM0
#define SPI_MUX_SETTING                SPI_SIGNAL_MUX_SETTING_E
#define SPI_PINMUX_PAD0                PINMUX_PA08C_SERCOM0_PAD0
#define SPI_PINMUX_PAD1                PINMUX_UNUSED
#define SPI_PINMUX_PAD2                PINMUX_PA10C_SERCOM0_PAD2
#define SPI_PINMUX_PAD3                PINMUX_PA11C_SERCOM0_PAD3

#endif /* CONF_BOARD_H_INCLUDED */
