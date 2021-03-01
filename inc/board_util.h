#ifndef __BOARDUTIL_H__
#define __BOARDUTIL_H__

#include "config.h"                                  

void BoardLED_Init();

void board_led_on(char color);

void board_led_off(char color);

uint32_t get_tick_val_safe();

void BoardUtil_Init(void);

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