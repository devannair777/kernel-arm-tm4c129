#include "lib/prompt.h"
#include "board_util.h"
#include <math.h>
#include "rom_modules/board_modules.h"

void def_led_test();
void def_serial_test();
void def_math_test();

void module_t()
{
    //Call one of 
    //the test functions from below  
    def_math_test();
}


void def_math_test()
{
    // Check CC31xxxx/cc3100/platform/ek-tm4c1294xl/board.c 
    // for reason why fpuenable and fpulazystacking is called before clock
    // FPUEnable();
    // FPULazyStackingEnable();
    // default_clock_init();
    BoardUtil_Init();
    UARTprintf("Testing Math module\r\n");
    int cnt = 0;
    while(cnt < 3)
    {
        uint32_t sys_val = get_tick_val_safe();
        int mod90 = sys_val % 90;
        float res = sinf(sys_val%90);
        UARTprintf("Current sysval is = %lu::Calc sin( %d ): %f \r\n",sys_val,mod90,res);
        delay_ms(523);
        cnt ++;
    }
    
    while(1);
}

void def_led_test()
{
    BoardUtil_Init();
    while(1)
    {
        LED3_On();
        delay_ms(1000);
        LED3_Off();;
        delay_ms(1000);
    }
}

void def_serial_test()
{
    //default_clock_init();
    BoardUtil_Init();
    UARTprintf("Initializing Module Test Routine ...\r\n");
    while(1);
}