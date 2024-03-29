#ifndef __BOARD_MODULES_H__
#define __BOARD_MODULES_H__

#define TARGET_IS_TM4C129_RA1
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/sysctl.h"
#include "driverlib/fpu.h"
#include "utils/uartstdio.h"
#include "config.h"

void ConfigureUART(uint32_t sys_clk);

void uart_init(uint32_t sys_clk);

uint32_t clk_init(void);

void led_init(void);

void led_on(char index);

void led_off(char index);

#endif //__BOARD_MODULES_H__