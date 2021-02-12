#include "lib/prompt.h"
#include "board_test.h"
#include "rom_modules/board_modules.h"

void def_led_test();
void def_serial_test();
void rom_led_test();
void rom_serial_test();

void module_t()
{
    //Call one of 
    //the test functions from below  
    rom_led_test();
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
    clk_init();
    uart_init();
    printk("Initializing Module Test Routine ...\r\n");
    while(1);

}

