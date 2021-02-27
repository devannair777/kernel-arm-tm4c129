#ifndef __BOARD_MODULES_H__
#define __BOARD_MODULES_H__

#define TARGET_IS_TM4C129_RA1
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/rom.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/sysctl.h"
#include "driverlib/fpu.h"
#include "utils/uartstdio.h"
#include <uc_ao.h>
#include "config.h"
#include "cmsis/tm4c_cmsis.h"

void ConfigureUART(uint32_t sys_clk);

void uart_init(uint32_t sys_clk);

uint32_t clk_init(void);

void led_init(void);

void led_on(char index);

void led_off(char index);

enum EventSignals {
    BUTTON_PRESSED_SIG = USER_SIG,
    BUTTON_RELEASED_SIG,
    TIMEOUT_SIG,
    /* ... */
};

#define BSP_ASSERT(check_)                 \
    if (!(check_)) {                       \
        Q_onAssert(this_module, __LINE__); \
    } else (void)0

void Q_onAssert(char const *module, int loc);

extern Active *AO_BlinkyButton;

#endif //__BOARD_MODULES_H__