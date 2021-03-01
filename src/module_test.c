#include "lib/prompt.h"
#include "board_util.h"
#include <math.h>
#include "rom_modules/board_modules.h"

void def_led_test();
void def_serial_test();
void rom_led_test();
void rom_serial_test();
void def_math_test();

void module_t()
{
    //Call one of 
    //the test functions from below  
    rom_led_test();
}


void def_math_test()
{
    // Check CC31xxxx/cc3100/platform/ek-tm4c1294xl/board.c 
    // for reason why fpuenable and fpulazystacking is called before clock
    FPUEnable();
    FPULazyStackingEnable();
    //default_clock_init();
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
    //default_clock_init();
    BoardUtil_Init();
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
    //default_clock_init();
    serial_init();
    printk("Initializing Module Test Routine ...\r\n");
    while(1);
}

void rom_led_test()
{
    //clk_init();
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

