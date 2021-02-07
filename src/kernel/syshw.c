#include "syshw.h"

/*       _____________________           _______________________
        |                     |         |                       |
        |       Module        |-------> |         Units         |
        |_____________________|         |_______________________|
*/      
/* 
    Default clock of 25 MHz
 */
__attribute__((constructor))
void default_clock_init()
{
    SYSCTL->MOSCCTL  &= ~(SYSCTL_MOSCCTL_PWRDN |SYSCTL_MOSCCTL_NOXTAL );	
    SYSCTL->RSCLKCFG |= SYSCTL_RSCLKCFG_OSCSRC_MOSC; 
} 

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

