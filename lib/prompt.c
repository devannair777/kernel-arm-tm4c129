#include "lib/prompt.h"

void serial_init(void)
{
	SYSCTL->RCGCUART |= (1<<0);                     //Run Mode UART0 Enable
	SYSCTL->RCGCGPIO |= (1<<0);
	GPIOA_AHB->DIR |= 0x02;							//PA0->RX,PA1->TX
	GPIOA_AHB->LOCK = 0x4c4f434b;					
	GPIOA_AHB->DEN |= 0x3;							//PA0,PA1 Digital Enable
	GPIOA_AHB->AFSEL = 0x03;                        //Alternate Function Select
	GPIOA_AHB->PCTL |= (1<<4*1)|(1<<4*0);           //PMC n Bitfield Encoding = 0x1 for PA0 and PA1
	
	
/* 	BRD = 25,000,000 / (16 * 9600) = 162.76041666666666666666666666667
    UARTFBRD[DIVFRAC] = integer(0.76041667 * 64 + 0.5) = 49 */
	
	UART0->CTL &= ~(1<<0);                          //1. Disable the UART by clearing the UARTEN bit in the UARTCTL register.
	UART0->IBRD = 162;                              //2. Write the integer portion of the BRD to the UARTIBRD register.
	UART0->FBRD = 49;                               //3. Write the fractional portion of the BRD to the UARTFBRD register.
	UART0->LCRH = 0x60;                             //4. Write the desired serial parameters to the UARTLCRH register (in this case, a value of 0x0000.0060).
	UART0->CC = 0x00;                               //5. Configure the UART clock source by writing to the UARTCC register (in this case RunMode Clock Source) .
	UART0->CTL |= (1<<0)|(1<<8)|(1<<9);             //7. Enable the UART by setting the UARTEN bit in the UARTCTL register.	
		
}

static void serial_print(char c)
{
	while((UART0->FR & (1<<5)) != 0);
    UART0->DR = c;
}

void _putchar(char c)
{
  //lib/printf.c over UART0
	serial_print(c);
    
}

