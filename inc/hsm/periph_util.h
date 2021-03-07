#ifndef __PERIPH_UTIL_H__
#define __PERIPH_UTIL_H__

#include "hsm/hsm.h"
#define BSP_ASSERT(check_)                 \
    if (!(check_)) {                       \
        Q_onAssert(this_module, __LINE__); \
    } else (void)0

void BoardLED_Init();

void BoardSW_Init();

void BoardUart_Init();

extern QActive * const BlinkyButtonAO ;

void BoardUtil_Init(void);

void BoardUtil_Start();

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