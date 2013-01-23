/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'cpu' in SOPC Builder design 'BeInMotion_qsys'
 * SOPC Builder design path: C:/dev_beinmotion/BeInMotion_lab/BeInMotion_qsys.sopcinfo
 *
 * Generated: Tue Jan 22 22:50:34 EST 2013
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_qsys"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x21020
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "tiny"
#define ALT_CPU_DATA_ADDR_WIDTH 0x12
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x10020
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 0
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 0
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_ICACHE_SIZE 0
#define ALT_CPU_INST_ADDR_WIDTH 0x12
#define ALT_CPU_NAME "cpu"
#define ALT_CPU_RESET_ADDR 0x21800


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x21020
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "tiny"
#define NIOS2_DATA_ADDR_WIDTH 0x12
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x10020
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 0
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 0
#define NIOS2_ICACHE_LINE_SIZE_LOG2 0
#define NIOS2_ICACHE_SIZE 0
#define NIOS2_INST_ADDR_WIDTH 0x12
#define NIOS2_RESET_ADDR 0x21800


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_EPCS_FLASH_CONTROLLER
#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SPI
#define __ALTERA_AVALON_SYSID_QSYS
#define __ALTERA_AVALON_TIMER
#define __ALTERA_AVALON_UART
#define __ALTERA_NIOS2_QSYS
#define __ALTPLL
#define __DC_MOTOR_CONTROLLER
#define __I2C_MASTER_TOP
#define __IR_RECEIVER
#define __LCD_INTERFACE
#define __PID_CONTROLLER_TOP
#define __ST_MOTOR_TOP


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone IV E"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart"
#define ALT_STDERR_BASE 0x22160
#define ALT_STDERR_DEV jtag_uart
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart"
#define ALT_STDIN_BASE 0x22160
#define ALT_STDIN_DEV jtag_uart
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart"
#define ALT_STDOUT_BASE 0x22160
#define ALT_STDOUT_DEV jtag_uart
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "BeInMotion_qsys"


/*
 * bat_cc_al_n configuration
 *
 */

#define ALT_MODULE_CLASS_bat_cc_al_n altera_avalon_pio
#define BAT_CC_AL_N_BASE 0x220b0
#define BAT_CC_AL_N_BIT_CLEARING_EDGE_REGISTER 0
#define BAT_CC_AL_N_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BAT_CC_AL_N_CAPTURE 0
#define BAT_CC_AL_N_DATA_WIDTH 1
#define BAT_CC_AL_N_DO_TEST_BENCH_WIRING 0
#define BAT_CC_AL_N_DRIVEN_SIM_VALUE 0x0
#define BAT_CC_AL_N_EDGE_TYPE "NONE"
#define BAT_CC_AL_N_FREQ 50000000u
#define BAT_CC_AL_N_HAS_IN 0
#define BAT_CC_AL_N_HAS_OUT 0
#define BAT_CC_AL_N_HAS_TRI 1
#define BAT_CC_AL_N_IRQ -1
#define BAT_CC_AL_N_IRQ_INTERRUPT_CONTROLLER_ID -1
#define BAT_CC_AL_N_IRQ_TYPE "NONE"
#define BAT_CC_AL_N_NAME "/dev/bat_cc_al_n"
#define BAT_CC_AL_N_RESET_VALUE 0x0
#define BAT_CC_AL_N_SPAN 16
#define BAT_CC_AL_N_TYPE "altera_avalon_pio"


/*
 * bat_gas_gauge configuration
 *
 */

#define ALT_MODULE_CLASS_bat_gas_gauge i2c_master_top
#define BAT_GAS_GAUGE_BASE 0x22040
#define BAT_GAS_GAUGE_IRQ 7
#define BAT_GAS_GAUGE_IRQ_INTERRUPT_CONTROLLER_ID 0
#define BAT_GAS_GAUGE_NAME "/dev/bat_gas_gauge"
#define BAT_GAS_GAUGE_SPAN 32
#define BAT_GAS_GAUGE_TYPE "i2c_master_top"


/*
 * dc1_pwm1 configuration
 *
 */

#define ALT_MODULE_CLASS_dc1_pwm1 DC_Motor_Controller
#define DC1_PWM1_BASE 0x22140
#define DC1_PWM1_IRQ -1
#define DC1_PWM1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define DC1_PWM1_NAME "/dev/dc1_pwm1"
#define DC1_PWM1_SPAN 16
#define DC1_PWM1_TYPE "DC_Motor_Controller"


/*
 * dc1_pwm2 configuration
 *
 */

#define ALT_MODULE_CLASS_dc1_pwm2 DC_Motor_Controller
#define DC1_PWM2_BASE 0x22120
#define DC1_PWM2_IRQ -1
#define DC1_PWM2_IRQ_INTERRUPT_CONTROLLER_ID -1
#define DC1_PWM2_NAME "/dev/dc1_pwm2"
#define DC1_PWM2_SPAN 16
#define DC1_PWM2_TYPE "DC_Motor_Controller"


/*
 * dc2_pwm1 configuration
 *
 */

#define ALT_MODULE_CLASS_dc2_pwm1 DC_Motor_Controller
#define DC2_PWM1_BASE 0x22150
#define DC2_PWM1_IRQ -1
#define DC2_PWM1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define DC2_PWM1_NAME "/dev/dc2_pwm1"
#define DC2_PWM1_SPAN 16
#define DC2_PWM1_TYPE "DC_Motor_Controller"


/*
 * dc2_pwm2 configuration
 *
 */

#define ALT_MODULE_CLASS_dc2_pwm2 DC_Motor_Controller
#define DC2_PWM2_BASE 0x22130
#define DC2_PWM2_IRQ -1
#define DC2_PWM2_IRQ_INTERRUPT_CONTROLLER_ID -1
#define DC2_PWM2_NAME "/dev/dc2_pwm2"
#define DC2_PWM2_SPAN 16
#define DC2_PWM2_TYPE "DC_Motor_Controller"


/*
 * epcs configuration
 *
 */

#define ALT_MODULE_CLASS_epcs altera_avalon_epcs_flash_controller
#define EPCS_BASE 0x21800
#define EPCS_IRQ 4
#define EPCS_IRQ_INTERRUPT_CONTROLLER_ID 0
#define EPCS_NAME "/dev/epcs"
#define EPCS_REGISTER_OFFSET 1024
#define EPCS_SPAN 2048
#define EPCS_TYPE "altera_avalon_epcs_flash_controller"


/*
 * hal configuration
 *
 */

#define ALT_MAX_FD 32
#define ALT_SYS_CLK TIMER
#define ALT_TIMESTAMP_CLK none


/*
 * ir_led1 configuration
 *
 */

#define ALT_MODULE_CLASS_ir_led1 altera_avalon_pio
#define IR_LED1_BASE 0x220c0
#define IR_LED1_BIT_CLEARING_EDGE_REGISTER 0
#define IR_LED1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define IR_LED1_CAPTURE 0
#define IR_LED1_DATA_WIDTH 1
#define IR_LED1_DO_TEST_BENCH_WIRING 0
#define IR_LED1_DRIVEN_SIM_VALUE 0x0
#define IR_LED1_EDGE_TYPE "NONE"
#define IR_LED1_FREQ 50000000u
#define IR_LED1_HAS_IN 0
#define IR_LED1_HAS_OUT 1
#define IR_LED1_HAS_TRI 0
#define IR_LED1_IRQ -1
#define IR_LED1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define IR_LED1_IRQ_TYPE "NONE"
#define IR_LED1_NAME "/dev/ir_led1"
#define IR_LED1_RESET_VALUE 0x0
#define IR_LED1_SPAN 16
#define IR_LED1_TYPE "altera_avalon_pio"


/*
 * ir_led2 configuration
 *
 */

#define ALT_MODULE_CLASS_ir_led2 altera_avalon_pio
#define IR_LED2_BASE 0x220d0
#define IR_LED2_BIT_CLEARING_EDGE_REGISTER 0
#define IR_LED2_BIT_MODIFYING_OUTPUT_REGISTER 0
#define IR_LED2_CAPTURE 0
#define IR_LED2_DATA_WIDTH 1
#define IR_LED2_DO_TEST_BENCH_WIRING 0
#define IR_LED2_DRIVEN_SIM_VALUE 0x0
#define IR_LED2_EDGE_TYPE "NONE"
#define IR_LED2_FREQ 50000000u
#define IR_LED2_HAS_IN 0
#define IR_LED2_HAS_OUT 1
#define IR_LED2_HAS_TRI 0
#define IR_LED2_IRQ -1
#define IR_LED2_IRQ_INTERRUPT_CONTROLLER_ID -1
#define IR_LED2_IRQ_TYPE "NONE"
#define IR_LED2_NAME "/dev/ir_led2"
#define IR_LED2_RESET_VALUE 0x0
#define IR_LED2_SPAN 16
#define IR_LED2_TYPE "altera_avalon_pio"


/*
 * ir_rx1 configuration
 *
 */

#define ALT_MODULE_CLASS_ir_rx1 ir_receiver
#define IR_RX1_BASE 0x22168
#define IR_RX1_IRQ 5
#define IR_RX1_IRQ_INTERRUPT_CONTROLLER_ID 0
#define IR_RX1_NAME "/dev/ir_rx1"
#define IR_RX1_SPAN 8
#define IR_RX1_TYPE "ir_receiver"


/*
 * ir_rx2 configuration
 *
 */

#define ALT_MODULE_CLASS_ir_rx2 ir_receiver
#define IR_RX2_BASE 0x22170
#define IR_RX2_IRQ 6
#define IR_RX2_IRQ_INTERRUPT_CONTROLLER_ID 0
#define IR_RX2_NAME "/dev/ir_rx2"
#define IR_RX2_SPAN 8
#define IR_RX2_TYPE "ir_receiver"


/*
 * jtag_uart configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart altera_avalon_jtag_uart
#define JTAG_UART_BASE 0x22160
#define JTAG_UART_IRQ 0
#define JTAG_UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_NAME "/dev/jtag_uart"
#define JTAG_UART_READ_DEPTH 64
#define JTAG_UART_READ_THRESHOLD 8
#define JTAG_UART_SPAN 8
#define JTAG_UART_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_WRITE_DEPTH 64
#define JTAG_UART_WRITE_THRESHOLD 8


/*
 * lcd_intf configuration
 *
 */

#define ALT_MODULE_CLASS_lcd_intf LCD_Interface
#define LCD_INTF_BASE 0x22178
#define LCD_INTF_IRQ -1
#define LCD_INTF_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LCD_INTF_NAME "/dev/lcd_intf"
#define LCD_INTF_SPAN 8
#define LCD_INTF_TYPE "LCD_Interface"


/*
 * onchip_ram configuration
 *
 */

#define ALT_MODULE_CLASS_onchip_ram altera_avalon_onchip_memory2
#define ONCHIP_RAM_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define ONCHIP_RAM_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define ONCHIP_RAM_BASE 0x10000
#define ONCHIP_RAM_CONTENTS_INFO ""
#define ONCHIP_RAM_DUAL_PORT 0
#define ONCHIP_RAM_GUI_RAM_BLOCK_TYPE "Automatic"
#define ONCHIP_RAM_INIT_CONTENTS_FILE "onchip_ram"
#define ONCHIP_RAM_INIT_MEM_CONTENT 1
#define ONCHIP_RAM_INSTANCE_ID "NONE"
#define ONCHIP_RAM_IRQ -1
#define ONCHIP_RAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ONCHIP_RAM_NAME "/dev/onchip_ram"
#define ONCHIP_RAM_NON_DEFAULT_INIT_FILE_ENABLED 0
#define ONCHIP_RAM_RAM_BLOCK_TYPE "Auto"
#define ONCHIP_RAM_READ_DURING_WRITE_MODE "DONT_CARE"
#define ONCHIP_RAM_SINGLE_CLOCK_OP 0
#define ONCHIP_RAM_SIZE_MULTIPLE 1
#define ONCHIP_RAM_SIZE_VALUE 40000u
#define ONCHIP_RAM_SPAN 40000
#define ONCHIP_RAM_TYPE "altera_avalon_onchip_memory2"
#define ONCHIP_RAM_WRITABLE 1


/*
 * pb configuration
 *
 */

#define ALT_MODULE_CLASS_pb altera_avalon_pio
#define PB_BASE 0x220a0
#define PB_BIT_CLEARING_EDGE_REGISTER 0
#define PB_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PB_CAPTURE 0
#define PB_DATA_WIDTH 7
#define PB_DO_TEST_BENCH_WIRING 0
#define PB_DRIVEN_SIM_VALUE 0x0
#define PB_EDGE_TYPE "NONE"
#define PB_FREQ 50000000u
#define PB_HAS_IN 1
#define PB_HAS_OUT 0
#define PB_HAS_TRI 0
#define PB_IRQ -1
#define PB_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PB_IRQ_TYPE "NONE"
#define PB_NAME "/dev/pb"
#define PB_RESET_VALUE 0x0
#define PB_SPAN 16
#define PB_TYPE "altera_avalon_pio"


/*
 * pid_con_m1 configuration
 *
 */

#define ALT_MODULE_CLASS_pid_con_m1 pid_controller_top
#define PID_CON_M1_BASE 0x0
#define PID_CON_M1_IRQ -1
#define PID_CON_M1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PID_CON_M1_NAME "/dev/pid_con_m1"
#define PID_CON_M1_SPAN 32
#define PID_CON_M1_TYPE "pid_controller_top"


/*
 * pid_con_m2 configuration
 *
 */

#define ALT_MODULE_CLASS_pid_con_m2 pid_controller_top
#define PID_CON_M2_BASE 0x20
#define PID_CON_M2_IRQ -1
#define PID_CON_M2_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PID_CON_M2_NAME "/dev/pid_con_m2"
#define PID_CON_M2_SPAN 32
#define PID_CON_M2_TYPE "pid_controller_top"


/*
 * pll configuration
 *
 */

#define ALT_MODULE_CLASS_pll altpll
#define PLL_BASE 0x22110
#define PLL_IRQ -1
#define PLL_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PLL_NAME "/dev/pll"
#define PLL_SPAN 16
#define PLL_TYPE "altpll"


/*
 * proximity_ir configuration
 *
 */

#define ALT_MODULE_CLASS_proximity_ir i2c_master_top
#define PROXIMITY_IR_BASE 0x22060
#define PROXIMITY_IR_IRQ 8
#define PROXIMITY_IR_IRQ_INTERRUPT_CONTROLLER_ID 0
#define PROXIMITY_IR_NAME "/dev/proximity_ir"
#define PROXIMITY_IR_SPAN 32
#define PROXIMITY_IR_TYPE "i2c_master_top"


/*
 * ps_din configuration
 *
 */

#define ALT_MODULE_CLASS_ps_din altera_avalon_pio
#define PS_DIN_BASE 0x220e0
#define PS_DIN_BIT_CLEARING_EDGE_REGISTER 0
#define PS_DIN_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PS_DIN_CAPTURE 1
#define PS_DIN_DATA_WIDTH 1
#define PS_DIN_DO_TEST_BENCH_WIRING 0
#define PS_DIN_DRIVEN_SIM_VALUE 0x0
#define PS_DIN_EDGE_TYPE "ANY"
#define PS_DIN_FREQ 1000000u
#define PS_DIN_HAS_IN 1
#define PS_DIN_HAS_OUT 0
#define PS_DIN_HAS_TRI 0
#define PS_DIN_IRQ 3
#define PS_DIN_IRQ_INTERRUPT_CONTROLLER_ID 0
#define PS_DIN_IRQ_TYPE "EDGE"
#define PS_DIN_NAME "/dev/ps_din"
#define PS_DIN_RESET_VALUE 0x0
#define PS_DIN_SPAN 16
#define PS_DIN_TYPE "altera_avalon_pio"


/*
 * ps_en configuration
 *
 */

#define ALT_MODULE_CLASS_ps_en altera_avalon_pio
#define PS_EN_BASE 0x220f0
#define PS_EN_BIT_CLEARING_EDGE_REGISTER 0
#define PS_EN_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PS_EN_CAPTURE 0
#define PS_EN_DATA_WIDTH 1
#define PS_EN_DO_TEST_BENCH_WIRING 0
#define PS_EN_DRIVEN_SIM_VALUE 0x0
#define PS_EN_EDGE_TYPE "NONE"
#define PS_EN_FREQ 50000000u
#define PS_EN_HAS_IN 0
#define PS_EN_HAS_OUT 1
#define PS_EN_HAS_TRI 0
#define PS_EN_IRQ -1
#define PS_EN_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PS_EN_IRQ_TYPE "NONE"
#define PS_EN_NAME "/dev/ps_en"
#define PS_EN_RESET_VALUE 0x0
#define PS_EN_SPAN 16
#define PS_EN_TYPE "altera_avalon_pio"


/*
 * ps_led_on configuration
 *
 */

#define ALT_MODULE_CLASS_ps_led_on altera_avalon_pio
#define PS_LED_ON_BASE 0x22100
#define PS_LED_ON_BIT_CLEARING_EDGE_REGISTER 0
#define PS_LED_ON_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PS_LED_ON_CAPTURE 0
#define PS_LED_ON_DATA_WIDTH 1
#define PS_LED_ON_DO_TEST_BENCH_WIRING 0
#define PS_LED_ON_DRIVEN_SIM_VALUE 0x0
#define PS_LED_ON_EDGE_TYPE "NONE"
#define PS_LED_ON_FREQ 50000000u
#define PS_LED_ON_HAS_IN 0
#define PS_LED_ON_HAS_OUT 1
#define PS_LED_ON_HAS_TRI 0
#define PS_LED_ON_IRQ -1
#define PS_LED_ON_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PS_LED_ON_IRQ_TYPE "NONE"
#define PS_LED_ON_NAME "/dev/ps_led_on"
#define PS_LED_ON_RESET_VALUE 0x0
#define PS_LED_ON_SPAN 16
#define PS_LED_ON_TYPE "altera_avalon_pio"


/*
 * st_current_sensor configuration
 *
 */

#define ALT_MODULE_CLASS_st_current_sensor altera_avalon_spi
#define ST_CURRENT_SENSOR_BASE 0x22020
#define ST_CURRENT_SENSOR_CLOCKMULT 1
#define ST_CURRENT_SENSOR_CLOCKPHASE 0
#define ST_CURRENT_SENSOR_CLOCKPOLARITY 0
#define ST_CURRENT_SENSOR_CLOCKUNITS "Hz"
#define ST_CURRENT_SENSOR_DATABITS 16
#define ST_CURRENT_SENSOR_DATAWIDTH 16
#define ST_CURRENT_SENSOR_DELAYMULT "1.0E-9"
#define ST_CURRENT_SENSOR_DELAYUNITS "ns"
#define ST_CURRENT_SENSOR_EXTRADELAY 0
#define ST_CURRENT_SENSOR_INSERT_SYNC 0
#define ST_CURRENT_SENSOR_IRQ 2
#define ST_CURRENT_SENSOR_IRQ_INTERRUPT_CONTROLLER_ID 0
#define ST_CURRENT_SENSOR_ISMASTER 1
#define ST_CURRENT_SENSOR_LSBFIRST 0
#define ST_CURRENT_SENSOR_NAME "/dev/st_current_sensor"
#define ST_CURRENT_SENSOR_NUMSLAVES 1
#define ST_CURRENT_SENSOR_PREFIX "spi_"
#define ST_CURRENT_SENSOR_SPAN 32
#define ST_CURRENT_SENSOR_SYNC_REG_DEPTH 2
#define ST_CURRENT_SENSOR_TARGETCLOCK 1000000u
#define ST_CURRENT_SENSOR_TARGETSSDELAY "0.0"
#define ST_CURRENT_SENSOR_TYPE "altera_avalon_spi"


/*
 * stpr_motor_cntrl configuration
 *
 */

#define ALT_MODULE_CLASS_stpr_motor_cntrl st_motor_top
#define STPR_MOTOR_CNTRL_BASE 0x40
#define STPR_MOTOR_CNTRL_IRQ -1
#define STPR_MOTOR_CNTRL_IRQ_INTERRUPT_CONTROLLER_ID -1
#define STPR_MOTOR_CNTRL_NAME "/dev/stpr_motor_cntrl"
#define STPR_MOTOR_CNTRL_SPAN 32
#define STPR_MOTOR_CNTRL_TYPE "st_motor_top"


/*
 * sysid configuration
 *
 */

#define ALT_MODULE_CLASS_sysid altera_avalon_sysid_qsys
#define SYSID_BASE 0x80
#define SYSID_ID 0
#define SYSID_IRQ -1
#define SYSID_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_NAME "/dev/sysid"
#define SYSID_SPAN 8
#define SYSID_TIMESTAMP 1358912147
#define SYSID_TYPE "altera_avalon_sysid_qsys"


/*
 * timer configuration
 *
 */

#define ALT_MODULE_CLASS_timer altera_avalon_timer
#define TIMER_ALWAYS_RUN 0
#define TIMER_BASE 0x22000
#define TIMER_COUNTER_SIZE 32
#define TIMER_FIXED_PERIOD 0
#define TIMER_FREQ 50000000u
#define TIMER_IRQ 1
#define TIMER_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_LOAD_VALUE 49999ull
#define TIMER_MULT 0.0010
#define TIMER_NAME "/dev/timer"
#define TIMER_PERIOD 1
#define TIMER_PERIOD_UNITS "ms"
#define TIMER_RESET_OUTPUT 0
#define TIMER_SNAPSHOT 1
#define TIMER_SPAN 32
#define TIMER_TICKS_PER_SEC 1000u
#define TIMER_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_TYPE "altera_avalon_timer"


/*
 * uart_0 configuration
 *
 */

#define ALT_MODULE_CLASS_uart_0 altera_avalon_uart
#define UART_0_BASE 0x60
#define UART_0_BAUD 9600
#define UART_0_DATA_BITS 8
#define UART_0_FIXED_BAUD 1
#define UART_0_FREQ 50000000u
#define UART_0_IRQ 9
#define UART_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define UART_0_NAME "/dev/uart_0"
#define UART_0_PARITY 'N'
#define UART_0_SIM_CHAR_STREAM ""
#define UART_0_SIM_TRUE_BAUD 0
#define UART_0_SPAN 32
#define UART_0_STOP_BITS 1
#define UART_0_SYNC_REG_DEPTH 2
#define UART_0_TYPE "altera_avalon_uart"
#define UART_0_USE_CTS_RTS 1
#define UART_0_USE_EOP_REGISTER 0


/*
 * user_io configuration
 *
 */

#define ALT_MODULE_CLASS_user_io altera_avalon_pio
#define USER_IO_BASE 0x22080
#define USER_IO_BIT_CLEARING_EDGE_REGISTER 0
#define USER_IO_BIT_MODIFYING_OUTPUT_REGISTER 0
#define USER_IO_CAPTURE 0
#define USER_IO_DATA_WIDTH 8
#define USER_IO_DO_TEST_BENCH_WIRING 0
#define USER_IO_DRIVEN_SIM_VALUE 0x0
#define USER_IO_EDGE_TYPE "NONE"
#define USER_IO_FREQ 50000000u
#define USER_IO_HAS_IN 0
#define USER_IO_HAS_OUT 0
#define USER_IO_HAS_TRI 1
#define USER_IO_IRQ -1
#define USER_IO_IRQ_INTERRUPT_CONTROLLER_ID -1
#define USER_IO_IRQ_TYPE "NONE"
#define USER_IO_NAME "/dev/user_io"
#define USER_IO_RESET_VALUE 0x0
#define USER_IO_SPAN 16
#define USER_IO_TYPE "altera_avalon_pio"


/*
 * user_led configuration
 *
 */

#define ALT_MODULE_CLASS_user_led altera_avalon_pio
#define USER_LED_BASE 0x22090
#define USER_LED_BIT_CLEARING_EDGE_REGISTER 0
#define USER_LED_BIT_MODIFYING_OUTPUT_REGISTER 0
#define USER_LED_CAPTURE 0
#define USER_LED_DATA_WIDTH 3
#define USER_LED_DO_TEST_BENCH_WIRING 0
#define USER_LED_DRIVEN_SIM_VALUE 0x0
#define USER_LED_EDGE_TYPE "NONE"
#define USER_LED_FREQ 50000000u
#define USER_LED_HAS_IN 0
#define USER_LED_HAS_OUT 1
#define USER_LED_HAS_TRI 0
#define USER_LED_IRQ -1
#define USER_LED_IRQ_INTERRUPT_CONTROLLER_ID -1
#define USER_LED_IRQ_TYPE "NONE"
#define USER_LED_NAME "/dev/user_led"
#define USER_LED_RESET_VALUE 0x0
#define USER_LED_SPAN 16
#define USER_LED_TYPE "altera_avalon_pio"

#endif /* __SYSTEM_H_ */
