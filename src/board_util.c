#include "board_util.h"

static uint32_t volatile tick_ctr;

void BoardUtil_Init()
{
    SystemCoreClockUpdate(); 

    BoardLED_Init();

} 

void BoardUtil_Start()
{
    SysTick_Config(SystemCoreClock / OS_TICKS_PER_SEC);
}

void BoardLED_Init()
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

void LED1_On()
{
    GPION->DATA_BITS_R[LED1] = LED1;    //Atomic Write
}


void LED2_On()
{
    GPION->DATA_BITS_R[LED2] = LED2;    //Atomic Write
}


void LED3_On()
{
    GPIOF_AHB->DATA_BITS_R[LED3] = LED3;    //Atomic Write
}


void LED4_On()
{
    GPIOF_AHB->DATA_BITS_R[LED4] = LED4;    //Atomic Write
}

void LED1_Off()
{
    GPION->DATA_BITS_R[LED1] = 0;    //Atomic Write
}


void LED2_Off()
{
    GPION->DATA_BITS_R[LED2] = 0;    //Atomic Write
}


void LED3_Off()
{
    GPIOF_AHB->DATA_BITS_R[LED3] = 0;    //Atomic Write
}


void LED4_Off()
{
    GPIOF_AHB->DATA_BITS_R[LED4] = 0;    //Atomic Write
}

void board_led_on(char index)
{
    switch(index)
    {
        case '4':
//            GPIOF_AHB->DATA |= 0x01;
            GPIOF_AHB->DATA_BITS_R[LED4] = LED4;    //Atomic Write
        break;
        case '3':
 //           GPIOF_AHB->DATA |= 0x10;
            GPIOF_AHB->DATA_BITS_R[LED3] = LED3;    //Atomic Write
        break;
        case '2':
//            GPION->DATA |= 0x01;
            GPION->DATA_BITS_R[LED2] = LED2;        //Atomic Write
        break;
        case '1':
//            GPION->DATA |= 0x02;
            GPION->DATA_BITS_R[LED1] = LED1;        //Atomic Write
        break;
        default:
            GPIOF_AHB->DATA_BITS_R[LED4] = LED4;    //Atomic Write
    }
}

void board_led_off(char color)
{
    switch(color)
    {
        case '4':
//            GPIOF_AHB->DATA &= ~(0x01);
            GPIOF_AHB->DATA_BITS_R[LED4] = 0;    //Atomic Write
        break;
        case '3':
//            GPIOF_AHB->DATA &= ~(0x10);
            GPIOF_AHB->DATA_BITS_R[LED3] = 0;    //Atomic Write
        break;
        case '2':
 //           GPION->DATA &= ~(0x01);
            GPION->DATA_BITS_R[LED2] = 0;        //Atomic Write
        break;
        case '1':
//            GPION->DATA &= ~(0x02);
            GPION->DATA_BITS_R[LED1] = 0;        //Atomic Write
        break;
        default:
//            GPIOF_AHB->DATA &= ~(0x01);
            GPIOF_AHB->DATA_BITS_R[LED4] = 0;    //Atomic Write
    }
}

void Timer0A_IRQHandler()
{
    tick_ctr ++;
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

/*..........................................................................*/
/* error-handling function called by exception handlers in the startup code */
void Q_onAssert(char const *module, int loc) {
    /* TBD: damage control */
    (void)module; /* avoid the "unused parameter" compiler warning */
    (void)loc;    /* avoid the "unused parameter" compiler warning */
    GPIOF_AHB->DATA_BITS_R[LED4 | LED3] = 0xFFU; /* all ON */
    GPION->DATA_BITS_R[LED2 | LED1] = 0xFFU; /* all ON */

    NVIC_SystemReset(); /* reset the CPU */
}


