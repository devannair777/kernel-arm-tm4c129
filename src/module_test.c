#include "lib/prompt.h"
#include "board_test.h"
#include <math.h>
#include "rom_modules/board_modules.h"

void def_led_test();
void def_serial_test();
void rom_led_test();
void rom_serial_test();
void def_math_test();
void def_aoModelTest();

static char const this_module[] = "module_test"; /* this module name for Q_ASSERT() */



void module_t()
{
    //Call one of 
    //the test functions from below  
    //rom_led_test();
    def_aoModelTest();
}

/* 
    *******************  Actor Model Test  **************************
 */

enum { INITIAL_BLINK_TIME = (OS_TICKS_PER_SEC / 4) };

typedef struct {
    Active super; /* inherit Active base class */
    /* add private data for the AO... */
    enum {
        OFF_STATE,
        ON_STATE
    } state; /* the "state variable" */
    
    TimeEvent te;
    uint32_t blink_time;
} BlinkyButton;

static void BlinkyButton_dispatch(BlinkyButton * const me, Event const * const e) {
    if (e->sig == INIT_SIG) {
         //BSP_ledBlueOff();
         TimeEvent_arm(&me->te, me->blink_time * 3U, 0U);
         me->state = OFF_STATE;
    }

    switch (me->state) {
        case OFF_STATE: {
            switch (e->sig) {
                case TIMEOUT_SIG: {
                    //BSP_ledGreenOn();
                    TimeEvent_arm(&me->te, me->blink_time, 0U);
                    me->state = ON_STATE;
                    break;
                }
                case BUTTON_PRESSED_SIG: {
                    INT8U err; /* uC/OS-II error status */

                    //BSP_ledBlueOn();

                    me->blink_time >>= 1; /* shorten the blink time by factor of 2 */
                    if (me->blink_time == 0U) {
                        me->blink_time = INITIAL_BLINK_TIME;
                    }
                    break;
                }
                case BUTTON_RELEASED_SIG: {
                    //BSP_ledBlueOff();
                    break;
                }
            }
            break;
        }
        case ON_STATE: {
            switch (e->sig) {
                case TIMEOUT_SIG: {
                   // BSP_ledGreenOff();
                    TimeEvent_arm(&me->te, me->blink_time * 3U, 0U);
                    me->state = OFF_STATE;
                    break;
                }
                case BUTTON_PRESSED_SIG: {
                    INT8U err; /* uC/OS-II error status */

                    //BSP_ledBlueOn();

                    me->blink_time >>= 1; /* shorten the blink time by factor of 2 */
                    if (me->blink_time == 0U) {
                        me->blink_time = INITIAL_BLINK_TIME;
                    }
                    break;
                }
                case BUTTON_RELEASED_SIG: {
                   // BSP_ledBlueOff();
                    break;
                }
            }
            break;
        }
        default: {
            Q_ASSERT(0); /* invalid state! */
            break;
        }
    }
}

void BlinkyButton_ctor(BlinkyButton * const me) {
    Active_ctor(&me->super, (DispatchHandler)&BlinkyButton_dispatch);
    TimeEvent_ctor(&me->te, TIMEOUT_SIG, &me->super);
    me->blink_time = INITIAL_BLINK_TIME;
}

void def_aoModelTest()
{

OS_STK stack_blinkyButton[100]; /* task stack */
static Event *blinkyButton_queue[10];
static BlinkyButton blinkyButton;
Active *AO_BlinkyButton = &blinkyButton.super;

INT8U err;

    default_clock_init();
    board_led_init();       /* initialize the BSP */
    OSInit();               /* initialize uC/OS-II */

    /* create AO and start it */
    BlinkyButton_ctor(&blinkyButton);
    Active_start(AO_BlinkyButton,
                 2U,
                 blinkyButton_queue,
                 sizeof(blinkyButton_queue)/sizeof(blinkyButton_queue[0]),
                 stack_blinkyButton,
                 sizeof(stack_blinkyButton),
                 0U);

    //BSP_start(); /* configure and start the interrupts */

    OSStart(); /* start the uC/OS-II scheduler... */

}
/* 
********************  Actor Model Test **********************************
 */
void def_math_test()
{
    // Check CC31xxxx/cc3100/platform/ek-tm4c1294xl/board.c 
    // for reason why fpuenable and fpulazystacking is called before clock
    FPUEnable();
    FPULazyStackingEnable();
    default_clock_init();
    serial_init();
    printk("Testing Math module\r\n");
    int cnt = 0;
    while(cnt < 3)
    {
        uint32_t sys_val = get_tick_val_safe();
        int mod90 = sys_val % 90;
        float res = sinf(sys_val%90);
        printk("Current sysval is = %lu::Calc sin( %d ): %f \r\n",sys_val,mod90,res);
        delay_ms(523);
        cnt ++;
    }
    
    while(1);
}

void def_led_test()
{
    default_clock_init();
    board_led_init();
    while(1)
    {
        board_led_on('3');
        delay_ms(1000);
        board_led_off('3');
        delay_ms(1000);
    }
}

void def_serial_test()
{
    default_clock_init();
    serial_init();
    printk("Initializing Module Test Routine ...\r\n");
    while(1);
}

void rom_led_test()
{
    clk_init();
    led_init();
    while(1)
    {
        led_on('3');
        delay_ms(1000);
        led_off('3');
        delay_ms(1000);
    }
}

void rom_serial_test()
{
    uint32_t sys_clk = clk_init();
    uart_init(sys_clk);
    printk("Initializing Module Test Routine ...\r\n");
    while(1);

}

