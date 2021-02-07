#ifndef __BOARDTEST_H__
#define __BOARDTEST_H__

#include "cmsis/tm4c_cmsis.h"

void board_led_init();
void board_led_on(char color);
void board_led_off(char color);
uint32_t get_tick_val_safe();

void delay_ms(uint32_t delay);

#endif //__BOARDTEST_H__