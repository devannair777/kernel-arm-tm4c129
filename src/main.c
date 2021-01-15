#include "kernel.h"


void GPIOAHandler()
{
    //some code
    int x = 99;
}


int main()
{
    sysctl_clock_init(XTAL_25MHZ);
    struct unit_config config;
    struct unit_config* ptr_config = &config;
    ptr_config->config_value = 0x02; //DIR Value
    ptr_config->pins_to_configure = 0xff; //DEN Value
    gpio_den_dir_set(GPIOA_AHB,ptr_config);
    
    while(1);
    return 0;
}

