#
# Copyright (c) 2011 Atmel Corporation. All rights reserved.
#
# \asf_license_start
#
# \page License
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. The name of Atmel may not be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# 4. This software may only be redistributed and used in connection with an
#    Atmel microcontroller product.
#
# THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
# WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
# EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
# \asf_license_stop
#

# Path to top level ASF directory relative to this project directory.
PRJ_PATH = $(XDK_ASF)

# Target CPU architecture: cortex-m3, cortex-m4
ARCH = cortex-m0plus

# Target part: none, sam3n4 or sam4l4aa
PART = samd21e18

# Application target name. Given with suffix .a for library and .elf for a
# standalone application.
TARGET_FLASH = sennet-samd_flash.elf
TARGET_SRAM = sennet-samd_sram.elf

# List of C source files.
CSRCS = \
       common/services/freertos/dbg_print/dbg_print.c     \
       common/utils/interrupt/interrupt_sam_nvic.c        \
       common2/services/delay/sam0/cycle_counter.c        \
       sam0/drivers/extint/extint_callback.c              \
       sam0/drivers/extint/extint_sam_d_r_h/extint.c      \
       sam0/drivers/nvm/nvm.c                             \
       sam0/drivers/port/port.c                           \
       sam0/drivers/rtc/rtc_sam_d_r_h/rtc_count.c         \
       sam0/drivers/rtc/rtc_sam_d_r_h/rtc_count_interrupt.c \
       sam0/drivers/sercom/i2c/i2c_sam0/i2c_master.c      \
       sam0/drivers/sercom/sercom.c                       \
       sam0/drivers/sercom/sercom_interrupt.c             \
       sam0/drivers/sercom/spi/spi.c                      \
       sam0/drivers/sercom/usart/usart.c                  \
       sam0/drivers/sercom/usart/usart_interrupt.c        \
       sam0/drivers/system/clock/clock_samd21_r21_da_ha1/clock.c \
       sam0/drivers/system/clock/clock_samd21_r21_da_ha1/gclk.c \
       sam0/drivers/system/interrupt/system_interrupt.c   \
       sam0/drivers/system/pinmux/pinmux.c                \
       sam0/drivers/system/system.c                       \
       sam0/utils/cmsis/samd21/source/gcc/startup_samd21.c \
       sam0/utils/cmsis/samd21/source/system_samd21.c     \
       sam0/utils/syscalls/gcc/syscalls.c                 \
       thirdparty/freertos/freertos-10.4.1/Source/croutine.c \
       thirdparty/freertos/freertos-10.4.1/Source/event_groups.c \
       thirdparty/freertos/freertos-10.4.1/Source/list.c  \
       thirdparty/freertos/freertos-10.4.1/Source/portable/GCC/ARM_CM0/port.c \
       thirdparty/freertos/freertos-10.4.1/Source/portable/MemMang/heap_1.c \
       thirdparty/freertos/freertos-10.4.1/Source/queue.c \
       thirdparty/freertos/freertos-10.4.1/Source/stream_buffer.c \
       thirdparty/freertos/freertos-10.4.1/Source/tasks.c \
       thirdparty/freertos/freertos-10.4.1/Source/timers.c \
       BSEC/bme680.c                                      \
       BSEC/bsec_integration.c                            \
       BSEC/bsec_iot_example.c                            \
       BSEC/bsec_serialized_configurations_iaq.c          \
       EPD/Config/DEV_Config.c                            \
       EPD/e-Paper/EPD_2in13.c                            \
       EPD/EPD_2in13_test.c                               \
       EPD/Fonts/font12.c                                 \
       EPD/Fonts/font16.c                                 \
       EPD/Fonts/font20.c                                 \
       EPD/Fonts/font24.c                                 \
       EPD/Fonts/font8.c                                  \
       EPD/GUI/GUI_Paint.c                                \
       EPD/ImageData.c                                    \
       drv_keyboard.c                                     \
       drv_nrf24l01p.c                                    \
       hal_delay.c                                        \
       hal_extint.c                                       \
       hal_gpio.c                                         \
       hal_i2c.c                                          \
       hal_rtc.c                                          \
       hal_spi.c                                          \
       main.c                                             \
       radio.c

# List of assembler source files.
ASSRCS = 

# List of include paths.
INC_PATH = \
       common/boards                                      \
       common/services/freertos/dbg_print                 \
       common/utils                                       \
       common2/services/delay                             \
       common2/services/delay/sam0                        \
       sam0/boards                                        \
       sam0/boards/dummy                                  \
       sam0/drivers/extint                                \
       sam0/drivers/extint/extint_sam_d_r_h               \
       sam0/drivers/nvm                                   \
       sam0/drivers/port                                  \
       sam0/drivers/rtc                                   \
       sam0/drivers/rtc/rtc_sam_d_r_h                     \
       sam0/drivers/sercom                                \
       sam0/drivers/sercom/i2c                            \
       sam0/drivers/sercom/i2c/i2c_sam0                   \
       sam0/drivers/sercom/spi                            \
       sam0/drivers/sercom/usart                          \
       sam0/drivers/system                                \
       sam0/drivers/system/clock                          \
       sam0/drivers/system/clock/clock_samd21_r21_da_ha1  \
       sam0/drivers/system/interrupt                      \
       sam0/drivers/system/interrupt/system_interrupt_samd21 \
       sam0/drivers/system/pinmux                         \
       sam0/drivers/system/power                          \
       sam0/drivers/system/power/power_sam_d_r_h          \
       sam0/drivers/system/reset                          \
       sam0/drivers/system/reset/reset_sam_d_r_h          \
       sam0/utils                                         \
       sam0/utils/cmsis/samd21/include                    \
       sam0/utils/cmsis/samd21/source                     \
       sam0/utils/header_files                            \
       sam0/utils/preprocessor                            \
       thirdparty/CMSIS/Include                           \
       thirdparty/CMSIS/Lib/GCC                           \
       thirdparty/freertos/freertos-10.4.1/Source/include \
       thirdparty/freertos/freertos-10.4.1/Source/portable/GCC/ARM_CM0

# Additional search paths for libraries.
LIB_PATH =  \
       thirdparty/CMSIS/Lib/GCC                           \
       .

# List of libraries to use during linking.
LIBS =  \
       arm_cortexM0l_math                                 \
       algobsec

# Path relative to top level directory pointing to a linker script.
LINKER_SCRIPT_FLASH = sam0/utils/linker_scripts/samd21/gcc/samd21e18a_flash.ld
LINKER_SCRIPT_SRAM  = sam0/utils/linker_scripts/samd21/gcc/samd21e18a_sram.ld

# Path relative to top level directory pointing to a linker script.
DEBUG_SCRIPT_FLASH = sam0/boards/samd21_xplained_pro/debug_scripts/gcc/samd21_xplained_pro_flash.gdb
DEBUG_SCRIPT_SRAM  = sam0/boards/samd21_xplained_pro/debug_scripts/gcc/samd21_xplained_pro_sram.gdb

# Project type parameter: all, sram or flash
PROJECT_TYPE        = flash

# Additional options for debugging. By default the common Makefile.in will
# add -g3.
DBGFLAGS = 

# Application optimization used during compilation and linking:
# -O0, -O1, -O2, -O3 or -Os
OPTIMIZATION = -O1

# Extra flags to use when archiving.
ARFLAGS = 

# Extra flags to use when assembling.
ASFLAGS = 

# Extra flags to use when compiling.
CFLAGS = -I. -IEPD -IBSEC

# Extra flags to use when preprocessing.
#
# Preprocessor symbol definitions
#   To add a definition use the format "-D name[=definition]".
#   To cancel a definition use the format "-U name".
#
# The most relevant symbols to define for the preprocessor are:
#   BOARD      Target board in use, see boards/board.h for a list.
#   EXT_BOARD  Optional extension board in use, see boards/board.h for a list.
CPPFLAGS = \
       -D ARM_MATH_CM0PLUS=true                           \
       -D BME680_FLOAT_POINT_COMPENSATION                 \
       -D BOARD=DUMMY_BOARD                               \
       -D CYCLE_MODE -D F_CPU=8000000                     \
       -D EXTINT_CALLBACK_MODE=true                       \
       -D I2C_MASTER_CALLBACK_MODE=false                  \
       -D RTC_COUNT_ASYNC=true                            \
       -D SPI_CALLBACK_MODE=false                         \
       -D USART_CALLBACK_MODE=true                        \
       -D __FREERTOS__                                    \
       -D __SAMD21E18A__

# Extra flags to use when linking
LDFLAGS = \
       -lc -u _printf_float -LBSEC

# Pre- and post-build commands
PREBUILD_CMD = 
POSTBUILD_CMD = 
