#include "board_test.h"

static uint32_t volatile tick_ctr;

void default_clock_init()
{
    SYSCTL->MOSCCTL  &= ~(0x08 | 0x04); // ~(SYSCTL_MOSCCTL_PWRDN |SYSCTL_MOSCCTL_NOXTAL );	
    SYSCTL->RSCLKCFG |=  0x00300000;    //SYSCTL_RSCLKCFG_OSCSRC_MOSC; 

    SysTick->LOAD = F_CPU/1000;         //Since SysTick Interrupt should be called every millisecond
                                        // or 1000 times per seccond.
    SysTick->VAL  = 0U;
    SysTick->CTRL = (1U << 2) | (1U << 1) | 1U;
} 



void Timer0A_IRQHandler()
{
    tick_ctr ++;
}

void board_led_init()
{
    SYSCTL->RCGCGPIO |= 0x20 | (1<<12);        //Enable Port f and Port N for LED
    
    GPIOF_AHB->DIR |= 0x11;          //Port f0 and Port f4 for LED's
    GPIOF_AHB->LOCK = 0x4c4f434b;
    GPIOF_AHB->DEN |= 0x11;          //Enable DEN for f0 and f4

    GPION->DIR |= 0x03;              //Port N0 and Port N1 for LED's
    GPION->LOCK = 0x4c4f434b;
    GPION->DEN |= 0x03;              //Enable DEN for N0 and N1


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
        case '2':
            GPION->DATA |= 0x01;
        break;
        case '1':
            GPION->DATA |= 0x02;
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
        case '2':
            GPION->DATA &= ~(0x01);
        break;
        case '1':
            GPION->DATA &= ~(0x02);
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


