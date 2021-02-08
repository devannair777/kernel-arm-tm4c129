#ifndef __BOARD_MODULES_H__
#define __BOARD_MODULES_H__

#define TARGET_IS_TM4C129_RA1
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/rom.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "cmsis/tm4c_cmsis.h"

void clk_init(void);

void led_init(void);

void led_on(char index);

void led_off(char index);

#endif //__BOARD_MODULES_H__