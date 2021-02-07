#include "lib/prompt.h"
#include "board_test.h"

#define T_ON          1000U
#define T_OFF         2000U

void state_machine_exec()
{
    serial_init();
    board_led_init();

    while(1)
    {
        static enum{
            INITIAL,ON_STATE,OFF_STATE,
        }state = INITIAL;
        static uint32_t start_time;

        switch (state)
        {
            case INITIAL:
                printk("Initializing state machine ...\r\n");
                state = OFF_STATE;
                start_time = get_tick_val_safe();
                break;
            
            case ON_STATE:
                
                if((get_tick_val_safe() - start_time) > T_ON)
                {
                    board_led_off('3');
                    state = OFF_STATE;
                    start_time = get_tick_val_safe();
                }
                               
                break;
            
            case OFF_STATE:
                if((get_tick_val_safe() - start_time) > T_OFF)
                {
                    board_led_on('3');
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