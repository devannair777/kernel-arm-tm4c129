#include "rom_modules/board_modules.h"
/* 
    ROM based Module Setup Tests
 */

/* 
    MOSC Configuration
 */

void clk_init()
{
    ROM_SysCtlClockFreqSet(SYSCTL_USE_OSC,25000000UL);  // Use External MOSC Crystal (25 MHz on board) 
                                                        //for 25 MHz System Clock
}
/* 
    MOSC Configuration Ends
 */
/* 
    Board LED
 */
void led_init()
{
    ROM_SysCtlPeripheralEnable(GPIOF_AHB_BASE);
    ROM_SysCtlPeripheralEnable(GPION_BASE);
    ROM_GPIODirModeSet(GPIOF_AHB_BASE,
                        GPIO_PIN_0 | GPIO_PIN_4,
                        GPIO_DIR_MODE_OUT);             //Port f0 and Port f4 for LED's
    ROM_GPIODirModeSet(GPION_BASE,
                        GPIO_PIN_0 | GPIO_PIN_1,
                        GPIO_DIR_MODE_OUT);             //Port n0 and Port n1 for LED's
    __enable_irq();
}

void led_on(char index)
{
    switch(index)
    {
        case '4':
           ROM_GPIOPinWrite(GPIOF_AHB_BASE,
                            GPIO_PIN_0,
                            0x1);
        break;
        case '3':
            ROM_GPIOPinWrite(GPIOF_AHB_BASE,
                            GPIO_PIN_4,
                            0x1);
        break;
        case '2':
            ROM_GPIOPinWrite(GPION_BASE,
                            GPIO_PIN_0,
                            0x1);
        break;
        case '1':
            ROM_GPIOPinWrite(GPION_BASE,
                            GPIO_PIN_1,
                            0x1);
        break;
        default:
            ROM_GPIOPinWrite(GPIOF_AHB_BASE,
                            GPIO_PIN_0,
                            0x1);
    }
}

void led_off(char index)
{
    switch(index)
    {
        case '4':
           ROM_GPIOPinWrite(GPIOF_AHB_BASE,
                            GPIO_PIN_0,
                            0x0);
        break;
        case '3':
            ROM_GPIOPinWrite(GPIOF_AHB_BASE,
                            GPIO_PIN_4,
                            0x0);
        break;
        case '2':
            ROM_GPIOPinWrite(GPION_BASE,
                            GPIO_PIN_0,
                            0x0);
        break;
        case '1':
            ROM_GPIOPinWrite(GPION_BASE,
                            GPIO_PIN_1,
                            0x0);
        break;
        default:
            ROM_GPIOPinWrite(GPIOF_AHB_BASE,
                            GPIO_PIN_0,
                            0x0);
    }
}
/* 
    Board LED //Ends
 */
/* 
    Ends // ROM based Module Setup Tests
 */