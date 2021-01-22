#include "kernel.h"

//       _____________________           _______________________
//      |                     |         |                       |
//      |       Module        |-------> |         Units         |
//      |_____________________|         |_______________________|
//      
// 
// 
// 
// 

void sysctl_clock_init(int xtal_mode)
{
    switch(xtal_mode)
    {
        case XTAL_25MHZ:
            SYSCTL->MOSCCTL  &= ~(SYSCTL_MOSCCTL_PWRDN |SYSCTL_MOSCCTL_NOXTAL );	
            SYSCTL->RSCLKCFG |= SYSCTL_RSCLKCFG_OSCSRC_MOSC; 
            break; 
    }	
	
}

void gpio_den_dir_set(GPIOA_AHB_Type* gpio,struct unit_config* unit_config)
{
    gpio->DIR = unit_config->config_value;
    gpio->LOCK = 0x4c4f434b;
    gpio->DEN = unit_config->pins_to_configure;

}
