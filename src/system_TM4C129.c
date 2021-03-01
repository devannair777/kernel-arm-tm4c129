#include "cmsis/tm4c_cmsis.h"

uint32_t SystemCoreClock = 25000000UL;

void SystemCoreClockUpdate()
{
    uint32_t rsClkCfg = SYSCTL->RSCLKCFG;
    uint8_t usepll = rsClkCfg >> 28;
    uint8_t oscsrc = (rsClkCfg >> 20)&0x0f;
    uint16_t osysdiv = (rsClkCfg >> 10)&0x3ff;
    uint16_t psysdiv = (rsClkCfg)&0x3ff;

    switch(oscsrc)
    {
        case 0x3:
            SystemCoreClock = 25000000UL;       /* XTAL 25 MHz */
            break;
        case 0x0:
            SystemCoreClock = 16000000UL;       /* PIOSC 16 MHz */
            break;
    }
    if(usepll)
    {
        SystemCoreClock = SystemCoreClock / (psysdiv + 1);
    }
    else
    {
        SystemCoreClock = SystemCoreClock / (osysdiv + 1);
    }
    
}

/* Has to be Called in Startup right before transferring BSS and .data sectors */

void SystemInit()
{
    
    SYSCTL->MOSCCTL  &= ~(0x08 | 0x04);     /* ~(SYSCTL_MOSCCTL_PWRDN |SYSCTL_MOSCCTL_NOXTAL )	 */
    SYSCTL->RSCLKCFG |=  0x00300000;        /* SYSCTL_RSCLKCFG_OSCSRC_MOSC */
}

