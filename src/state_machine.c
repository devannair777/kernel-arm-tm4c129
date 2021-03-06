#include "rom_modules/board_modules.h"
#include "board_util.h"

#define T_ON          1000U
#define T_OFF         2000U

/* 
    *******************  Actor Model Test  **************************
 */

static char const this_module[] = "state_machine"; /* this module name for Q_ASSERT() */

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
         LED2_Off();
         TimeEvent_arm(&me->te, me->blink_time * 3U, 0U);
         me->state = OFF_STATE;
    }

    switch (me->state) {
        case OFF_STATE: {
            switch (e->sig) {
                case TIMEOUT_SIG: {
                    //BSP_ledGreenOn();
                    LED1_On();
                    TimeEvent_arm(&me->te, me->blink_time, 0U);
                    me->state = ON_STATE;
                    break;
                }
                case BUTTON_PRESSED_SIG: {
                    //INT8U err; /* uC/OS-II error status */

                    //BSP_ledBlueOn();
                    LED2_On();

                    me->blink_time >>= 1; /* shorten the blink time by factor of 2 */
                    if (me->blink_time == 0U) {
                        me->blink_time = INITIAL_BLINK_TIME;
                    }
                    break;
                }
                case BUTTON_RELEASED_SIG: {
                    //BSP_ledBlueOff();
                    LED2_Off();
                    break;
                }
            }
            break;
        }
        case ON_STATE: {
            switch (e->sig) {
                case TIMEOUT_SIG: {
                   // BSP_ledGreenOff();
                    LED1_Off();
                    TimeEvent_arm(&me->te, me->blink_time * 3U, 0U);
                    me->state = OFF_STATE;
                    break;
                }
                case BUTTON_PRESSED_SIG: {
                    //INT8U err; /* uC/OS-II error status */

                    //BSP_ledBlueOn();
                    LED2_On();
                    me->blink_time >>= 1; /* shorten the blink time by factor of 2 */
                    if (me->blink_time == 0U) {
                        me->blink_time = INITIAL_BLINK_TIME;
                    }
                    break;
                }
                case BUTTON_RELEASED_SIG: {
                   // BSP_ledBlueOff();
                    LED2_Off();
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

    //INT8U err;

        BoardUtil_Init();       /* initialize the BSP */
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

        BoardUtil_Start(); /* configure and start the interrupts */
        OSStart(); /* start the uC/OS-II scheduler... */

}
/* 
********************  Actor Model Test **********************************
 */

void state_machine_exec()
{
    clk_init();
    led_init();

    while(1)
    {
        static enum{
            INITIAL,ON_STATE,OFF_STATE,
        }state = INITIAL;
        static uint32_t start_time;

        switch (state)
        {
            case INITIAL:
                state = OFF_STATE;
                start_time = get_tick_val_safe();
                break;
            
            case ON_STATE:
                
                if((get_tick_val_safe() - start_time) > T_ON)
                {
                    led_off('3');
                    state = OFF_STATE;
                    start_time = get_tick_val_safe();
                }
                               
                break;
            
            case OFF_STATE:
                if((get_tick_val_safe() - start_time) > T_OFF)
                {
                    led_on('3');
                    state = ON_STATE;
                    start_time = get_tick_val_safe();
                }
               
                break;

            default:
                //error
                break;
        }

    }

}