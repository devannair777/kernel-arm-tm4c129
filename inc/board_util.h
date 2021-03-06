#ifndef __BOARDUTIL_H__
#define __BOARDUTIL_H__

#include "config.h" 

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


extern Active *AO_BlinkyButton;

void BoardLED_Init();

void BoardSW_Init();

void BoardUart_Init();

/* Polling delay */
uint32_t get_tick_val_safe();

void BoardUtil_Init(void);

void BoardUtil_Start();

void delay_ms(uint32_t delay);

void LED1_On();

void LED2_On();

void LED3_On();

void LED4_On();

void LED1_Off();

void LED2_Off();

void LED3_Off();

void LED4_Off();

void Q_onAssert(char const *module, int loc);

#endif //__BOARDUTIL_H__