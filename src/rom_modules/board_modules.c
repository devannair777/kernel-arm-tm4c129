#include "rom_modules/board_modules.h"
/* 
    ROM based Module Setup Tests
 */

/* 
    UART Configuration
 */

void ConfigureUART(uint32_t sys_clk)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIOA_AHB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, UART_BDR, sys_clk);
}

void uart_init(uint32_t sys_clk)
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
                            sys_clk,
                            UART_BDR,
                            UART_CONFIG_WLEN_8 |  UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE
    );                                                   //5. Configure the UART clock source frequency of 25MHz
	ROM_UARTEnable(UART0_BASE);                          //7. Enable the UART.	
		
}
/* 
    MOSC Configuration
 */

uint32_t clk_init()
{
    uint32_t sys_clk = ROM_SysCtlClockFreqSet(
                            SYSCTL_USE_OSC,              // Use External MOSC Crystal (25 MHz on board) 
                            F_CPU);                      //for 25 MHz System Clock

    
/*  ROM_SysTickIntEnable();
    ROM_SysTickPeriodSet(F_CPU/1000);                   //There shoud be F_CPU/1000 clock ticks between interrupts
    ROM_SysTickEnable(); */                             // if the interrupts are to be trigerred every 1 ms.

    SysTick->LOAD = F_CPU/1000;                         //Since SysTick Interrupt should be called every millisecond
                                                        // or 1000 times per seccond.
    SysTick->VAL  = 0U;
    SysTick->CTRL = (1U << 2) | (1U << 1) | 1U;
    
    return sys_clk;
    
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

/* uCOS-II application hooks ===============================================*/



void App_TaskCreateHook (OS_TCB *ptcb) { (void)ptcb; }
void App_TaskDelHook    (OS_TCB *ptcb) { (void)ptcb; }
void App_TaskIdleHook(void) { }
void App_TaskReturnHook(OS_TCB  *ptcb){(void)ptcb;}
void App_TaskStatHook(void){}
void App_TaskSwHook(void){}
void App_TCBInitHook(OS_TCB *ptcb){(void)ptcb;}
void App_TimeTickHook(void)
{
    TimeEvent_tick();
}


/*..........................................................................*/


/* 
    Board LED //Ends
 */
/* 
    Ends // ROM based Module Setup Tests
 */