#include "kernel.h"
#include "lib/prompt.h"

uint32_t config_dir_value = 0x02;
uint32_t config_den_value = 0xff;
uint32_t uart0_test;


int main()
{
    sysctl_clock_init(XTAL_25MHZ);
    struct unit_config config;
    struct unit_config* ptr_config = &config;
    ptr_config->config_value = config_dir_value; //DIR Value
    ptr_config->pins_to_configure = config_den_value; //DEN Value
    gpio_den_dir_set(GPIOA_AHB,ptr_config);
    UART0->RSR.RSR =  uart0_test + 0x03;
    printk("Kernel Init ...\n");

    while(1);
    return 0;
}

