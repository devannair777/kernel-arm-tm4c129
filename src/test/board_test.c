#include "board_test.h"

static uint32_t volatile tick_ctr;

void SysTick_Handler()
{
    tick_ctr ++;
}

void board_led_init()
{
    SYSCTL->RCGCGPIO |= 0x20;        //Enable Port f for LED
    
    GPIOF_AHB->DIR |= 0x11;          //Port f0 and Port f4 for LED's
    GPIOF_AHB->LOCK = 0x4c4f434b;
    GPIOF_AHB->DEN |= 0x11;          //Enable DEN for f0 and f4

    __enable_irq();
}

void board_led_on(char index)
{
    switch(index)
    {
        case '4':
            GPIOF_AHB->DATA |= 0x01;
        break;
        case '3':
            GPIOF_AHB->DATA |= 0x10;
        break;
        default:
            GPIOF_AHB->DATA |= 0x01;
    }
}

void board_led_off(char color)
{
    switch(color)
    {
        case '4':
            GPIOF_AHB->DATA &= ~(0x01);
        break;
        case '3':
            GPIOF_AHB->DATA &= ~(0x10);
        break;
        default:
            GPIOF_AHB->DATA &= ~(0x01);
    }
}

uint32_t get_tick_val_safe()
{
    uint32_t curr_tick;

    __disable_irq();
    curr_tick = tick_ctr;
    __enable_irq();

    return curr_tick;
}

void delay_ms(uint32_t delay)
{
    uint32_t start = get_tick_val_safe();
    while((get_tick_val_safe() - start) < delay);
}


