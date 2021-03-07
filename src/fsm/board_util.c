#include "board_util.h"
#include "utils/uartstdio.h"

static uint32_t volatile tick_ctr;
extern uint32_t SystemCoreClock;

void BoardUtil_Init()
{
    SystemCoreClockUpdate(); 

    BoardLED_Init();

    BoardSW_Init();

    BoardUart_Init();

} 

void BoardUtil_Start()
{
    SysTick_Config(SystemCoreClock / OS_TICKS_PER_SEC);
}

void BoardUart_Init()
{
    UARTStdioConfig(0, UART_BDR, SystemCoreClock);

    #ifdef REMOTE_BOOT
          	/* UART7 or SSI? for CC3100 */
    #endif
}

void BoardLED_Init()
{
    __DSB();

    SYSCTL->RCGCGPIO |= 0x20 | (1<<12);        //Enable Port F and Port N for LED

    __DSB();
    
    GPIOF_AHB->DIR |= 0x11;          //Port F0 and Port F4 for LED's
    GPIOF_AHB->LOCK = 0x4c4f434b;
    GPIOF_AHB->DEN |= 0x11;          //Enable DEN for F0 and F4

    GPION->DIR |= 0x03;              //Port N0 and Port N1 for LED's
    GPION->LOCK = 0x4c4f434b;
    GPION->DEN |= 0x03;              //Enable DEN for N0 and N1


    __enable_irq();
}

void BoardSW_Init()
{
    __DSB();

    SYSCTL->RCGCGPIO |= (1<<8);        //Enable Port J for SW

    __DSB();

    GPIOJ_AHB->DIR &= ~(0x03);
    GPIOJ_AHB->LOCK = 0x4c4f434b;
    GPIOJ_AHB->DEN = 0x03;
    GPIOJ_AHB->PUR = 0x03;
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

/* uCOS-II application hooks ===============================================*/

void App_TaskCreateHook (OS_TCB *ptcb) { (void)ptcb; }
void App_TaskDelHook    (OS_TCB *ptcb) { (void)ptcb; }
void App_TaskIdleHook(void) { }
void App_TaskReturnHook(OS_TCB  *ptcb){(void)ptcb;}
void App_TaskStatHook(void){}
void App_TaskSwHook(void){}
void App_TCBInitHook(OS_TCB *ptcb){(void)ptcb;}
void App_TimeTickHook(void)
{
    
    #ifdef MODULES
        tick_ctr ++;          
    #else
        TimeEvent_tick();
        static struct ButtonsDebouncing {
        uint32_t depressed;
        uint32_t previous;
        } buttons = { 0U, 0U };
        uint32_t current;
        uint32_t tmp;

        current = ~GPIOJ_AHB->DATA_BITS_R[SW1]; /* read SW1 */
        tmp = buttons.depressed; /* save the debounced depressed buttons */
        buttons.depressed |= (buttons.previous & current); /* set depressed */
        buttons.depressed &= (buttons.previous | current); /* clear released */
        buttons.previous   = current; /* update the history */
        tmp ^= buttons.depressed;     /* changed debounced depressed */
        if ((tmp & SW1) != 0U) {  /* debounced SW1 state changed? */
            if ((buttons.depressed & SW1) != 0U) { /* is SW1 depressed? */
                /* post the "button-pressed" event from ISR */
                static Event const buttonPressedEvt = {BUTTON_PRESSED_SIG};
                Active_post(AO_BlinkyButton, &buttonPressedEvt);
            }
            else { /* the button is released */
                /* post the "button-released" event from ISR */
                static Event const buttonReleasedEvt = {BUTTON_RELEASED_SIG};
                Active_post(AO_BlinkyButton, &buttonReleasedEvt);
            }
        }
    #endif
}

/* =========================================================================*/
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


