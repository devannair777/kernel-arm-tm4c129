#include "rom_modules/board_modules.h"
/* 
    ROM based Module Setup Tests
 */

void _putchar(char c)
{
    
}

/* 
    UART Configuration
 */
void uart_init(void)
{
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);        //Run Mode UART0 Enable
	ROM_SysCtlPeripheralEnable(GPIOA_AHB_BASE);
    ROM_GPIODirModeSet(GPIOA_AHB_BASE,
                        GPIO_PIN_1,
                        GPIO_DIR_MODE_OUT);
    ROM_GPIODirModeSet(GPIOA_AHB_BASE,
                        GPIO_PIN_0,
                        GPIO_DIR_MODE_IN);                 //PA0->RX,PA1->TX
	
	ROM_GPIOPinTypeUART(GPIOA_AHB_BASE
                        ,GPIO_PIN_0 | GPIO_PIN_1);         //Alternate Function Select
	ROM_GPIOPinConfigure(GPIO_PA1_U0TX);                   //PMC n Bitfield Encoding = 0x1 for PA0 and PA1
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
	
	
/* 	BRD = 25,000,000 / (16 * 9600) = 162.76041666666666666666666666667
    UARTFBRD[DIVFRAC] = integer(0.76041667 * 64 + 0.5) = 49 */
	
	ROM_UARTDisable(UART0_BASE);                          //1. Disable the UART.
	ROM_UARTConfigSetExpClk(UART0_BASE,
                            F_CPU,
                            UART_BDR,
                            UART_CONFIG_WLEN_8 |  UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE
    );                                                   //5. Configure the UART clock source frequency of 25MHz
	ROM_UARTEnable(UART0_BASE);                          //7. Enable the UART.	
		
}
/* 
    MOSC Configuration
 */

void clk_init()
{
    ROM_SysCtlClockFreqSet(SYSCTL_USE_OSC,F_CPU);       // Use External MOSC Crystal (25 MHz on board) 
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