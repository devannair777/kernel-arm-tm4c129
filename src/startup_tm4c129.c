///GNU GPL v2 License

/* 
#######################################################################################

        Startup file for TM4C1294NCPDT with vector table configuration and 
                            Reset and Fault Handlers. 

#######################################################################################
 */ 
#include <stdint.h>

extern int main(void);

extern uintptr_t __stack_top;

extern uint32_t __etext;
extern uint32_t __exidx_end;
extern uint32_t __data_start__;
extern uint32_t __data_end__;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;

void SystemInit()                                                ;

void assert_failed(char const *module, int loc)                  ;
__attribute__ ((noreturn)) /* QP assertion handler */
void Q_onAssert(char const *module, int loc)                     ; 


void Reset_Handler(void)                                         ;
void Processor_Fault_Handler(void)                               ;
void System_Handler(void)                   __attribute__((weak));
void Interrupt_Service_Routine(void)        __attribute__((weak));

/*####################################################

            Cortex M4 Processor Fault Handlers

######################################################*/

void HardFault_Handler(void)                 __attribute__((weak,alias("Processor_Fault_Handler")));
void MemManage_Handler(void)                 __attribute__((weak,alias("Processor_Fault_Handler")));    
void BusFault_Handler(void)                  __attribute__((weak,alias("Processor_Fault_Handler")));
void UsageFault_Handler(void)                __attribute__((weak,alias("Processor_Fault_Handler")));

/*####################################################

        Cortex M4 Processor Non-Fault Handlers

######################################################*/

void NMI_Handler(void)                      __attribute__((weak,alias("System_Handler")));
void SVC_Handler(void)                      __attribute__((weak,alias("System_Handler")));
void DebugMon_Handler(void)                 __attribute__((weak,alias("System_Handler")));
void PendSV_Handler(void)                   __attribute__((weak,alias("System_Handler")));
void SysTick_Handler(void)                  __attribute__((weak,alias("System_Handler")));


/*
 * ===========================================================================
 * ---------- Interrupt Handler Prototypes -----------------------------------
 * ===========================================================================
 */

void GPIOPortA_IRQHandler(void)             __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortB_IRQHandler(void)             __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortC_IRQHandler(void)             __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortD_IRQHandler(void)             __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortE_IRQHandler(void)             __attribute__((weak,alias("Interrupt_Service_Routine")));
void UART0_IRQHandler(void)                 __attribute__((weak,alias("Interrupt_Service_Routine")));
void UART1_IRQHandler(void)                 __attribute__((weak,alias("Interrupt_Service_Routine")));
void SSI0_IRQHandler(void)                  __attribute__((weak,alias("Interrupt_Service_Routine")));
void I2C0_IRQHandler(void)                  __attribute__((weak,alias("Interrupt_Service_Routine")));
void PWMFault_IRQHandler(void)              __attribute__((weak,alias("Interrupt_Service_Routine")));
void PWMGen0_IRQHandler(void)               __attribute__((weak,alias("Interrupt_Service_Routine")));
void PWMGen1_IRQHandler(void)               __attribute__((weak,alias("Interrupt_Service_Routine")));
void PWMGen2_IRQHandler(void)               __attribute__((weak,alias("Interrupt_Service_Routine")));
void QEI0_IRQHandler(void)                  __attribute__((weak,alias("Interrupt_Service_Routine")));
void ADCSeq0_IRQHandler(void)               __attribute__((weak,alias("Interrupt_Service_Routine")));
void ADCSeq1_IRQHandler(void)               __attribute__((weak,alias("Interrupt_Service_Routine")));
void ADCSeq2_IRQHandler(void)               __attribute__((weak,alias("Interrupt_Service_Routine")));
void ADCSeq3_IRQHandler(void)               __attribute__((weak,alias("Interrupt_Service_Routine")));
void Watchdog_IRQHandler(void)              __attribute__((weak,alias("Interrupt_Service_Routine")));
void Timer0A_IRQHandler(void)               __attribute__((weak,alias("Interrupt_Service_Routine")));
void Timer0B_IRQHandler(void)               __attribute__((weak,alias("Interrupt_Service_Routine")));
void Timer1A_IRQHandler(void)               __attribute__((weak,alias("Interrupt_Service_Routine")));
void Timer1B_IRQHandler(void)               __attribute__((weak,alias("Interrupt_Service_Routine")));
void Timer2A_IRQHandler(void)               __attribute__((weak,alias("Interrupt_Service_Routine")));
void Timer2B_IRQHandler(void)               __attribute__((weak,alias("Interrupt_Service_Routine")));
void Comp0_IRQHandler(void)                 __attribute__((weak,alias("Interrupt_Service_Routine")));
void Comp1_IRQHandler(void)                 __attribute__((weak,alias("Interrupt_Service_Routine")));
void Comp2_IRQHandler(void)                 __attribute__((weak,alias("Interrupt_Service_Routine")));
void SysCtrl_IRQHandler(void)               __attribute__((weak,alias("Interrupt_Service_Routine")));
void FlashCtrl_IRQHandler(void)             __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortF_IRQHandler(void)             __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortG_IRQHandler(void)             __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortH_IRQHandler(void)             __attribute__((weak,alias("Interrupt_Service_Routine")));
void UART2_IRQHandler(void)                 __attribute__((weak,alias("Interrupt_Service_Routine")));
void SSI1_IRQHandler(void)                  __attribute__((weak,alias("Interrupt_Service_Routine")));
void Timer3A_IRQHandler(void)               __attribute__((weak,alias("Interrupt_Service_Routine")));
void Timer3B_IRQHandler(void)               __attribute__((weak,alias("Interrupt_Service_Routine")));
void I2C1_IRQHandler(void)                  __attribute__((weak,alias("Interrupt_Service_Routine")));
void CAN0_IRQHandler(void)                  __attribute__((weak,alias("Interrupt_Service_Routine")));
void CAN1_IRQHandler(void)                  __attribute__((weak,alias("Interrupt_Service_Routine")));
void ETH_IRQHandler(void)                   __attribute__((weak,alias("Interrupt_Service_Routine")));
void Hibernate_IRQHandler(void)             __attribute__((weak,alias("Interrupt_Service_Routine")));
void USB0_IRQHandler(void)                  __attribute__((weak,alias("Interrupt_Service_Routine")));
void PWMGen3_IRQHandler(void)               __attribute__((weak,alias("Interrupt_Service_Routine")));
void uDMAST_IRQHandler(void)                __attribute__((weak,alias("Interrupt_Service_Routine")));
void uDMAError_IRQHandler(void)             __attribute__((weak,alias("Interrupt_Service_Routine")));
void ADC1Seq0_IRQHandler(void)              __attribute__((weak,alias("Interrupt_Service_Routine")));
void ADC1Seq1_IRQHandler(void)              __attribute__((weak,alias("Interrupt_Service_Routine")));
void ADC1Seq2_IRQHandler(void)              __attribute__((weak,alias("Interrupt_Service_Routine")));
void ADC1Seq3_IRQHandler(void)              __attribute__((weak,alias("Interrupt_Service_Routine")));
void EBI0_IRQHandler(void)                  __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortJ_IRQHandler(void)             __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortK_IRQHandler(void)             __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortL_IRQHandler(void)             __attribute__((weak,alias("Interrupt_Service_Routine")));
void SSI2_IRQHandler(void)                  __attribute__((weak,alias("Interrupt_Service_Routine")));
void SSI3_IRQHandler(void)                  __attribute__((weak,alias("Interrupt_Service_Routine")));
void UART3_IRQHandler(void)                 __attribute__((weak,alias("Interrupt_Service_Routine")));
void UART4_IRQHandler(void)                 __attribute__((weak,alias("Interrupt_Service_Routine")));
void UART5_IRQHandler(void)                 __attribute__((weak,alias("Interrupt_Service_Routine")));
void UART6_IRQHandler(void)                 __attribute__((weak,alias("Interrupt_Service_Routine")));
void UART7_IRQHandler(void)                 __attribute__((weak,alias("Interrupt_Service_Routine")));
void I2C2_IRQHandler(void)                  __attribute__((weak,alias("Interrupt_Service_Routine")));
void I2C3_IRQHandler(void)                  __attribute__((weak,alias("Interrupt_Service_Routine")));
void Timer4A_IRQHandler(void)               __attribute__((weak,alias("Interrupt_Service_Routine")));
void Timer4B_IRQHandler(void)               __attribute__((weak,alias("Interrupt_Service_Routine")));
void Timer5A_IRQHandler(void)               __attribute__((weak,alias("Interrupt_Service_Routine")));
void Timer5B_IRQHandler(void)               __attribute__((weak,alias("Interrupt_Service_Routine")));
void Timer6A_IRQHandler(void)               __attribute__((weak,alias("Interrupt_Service_Routine")));
void Timer6B_IRQHandler(void)               __attribute__((weak,alias("Interrupt_Service_Routine")));
void Timer7A_IRQHandler(void)               __attribute__((weak,alias("Interrupt_Service_Routine")));
void Timer7B_IRQHandler(void)               __attribute__((weak,alias("Interrupt_Service_Routine")));
void FPU_IRQHandler(void)                   __attribute__((weak,alias("Interrupt_Service_Routine")));
void I2C4_IRQHandler(void)                  __attribute__((weak,alias("Interrupt_Service_Routine")));
void I2C5_IRQHandler(void)                  __attribute__((weak,alias("Interrupt_Service_Routine")));
void I2C6_IRQHandler(void)                  __attribute__((weak,alias("Interrupt_Service_Routine")));
void I2C7_IRQHandler(void)                  __attribute__((weak,alias("Interrupt_Service_Routine")));
void I2C8_IRQHandler(void)                  __attribute__((weak,alias("Interrupt_Service_Routine")));
void I2C9_IRQHandler(void)                  __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortM_IRQHandler(void)             __attribute__((weak,alias("Interrupt_Service_Routine")));
void HibernateTamper_IRQHandler(void)       __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortN_IRQHandler(void)             __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortP0_IRQHandler(void)            __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortP1_IRQHandler(void)            __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortP2_IRQHandler(void)            __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortP3_IRQHandler(void)            __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortP4_IRQHandler(void)            __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortP5_IRQHandler(void)            __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortP6_IRQHandler(void)            __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortP7_IRQHandler(void)            __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortQ0_IRQHandler(void)            __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortQ1_IRQHandler(void)            __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortQ2_IRQHandler(void)            __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortQ3_IRQHandler(void)            __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortQ4_IRQHandler(void)            __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortQ5_IRQHandler(void)            __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortQ6_IRQHandler(void)            __attribute__((weak,alias("Interrupt_Service_Routine")));
void GPIOPortQ7_IRQHandler(void)            __attribute__((weak,alias("Interrupt_Service_Routine")));

/*####################################################

      Vector Table at Start of ROM (0x0000.0000)

######################################################*/

__attribute__((section(".isr_vector")))
const uintptr_t __vector_table[]  = {
/*  Check
uint32_t max (4294967295U)
uintptr_t max (4294967295U)  //So they are of same size, so it could be legally 
casted from a pointer with the value given by the arg
 */
/*########################################

            System Exceptions

##########################################*/
                                                //Stack grows from higher address to lower address in SRAM in TM4C129x
    (uintptr_t ) &(__stack_top),                //Stack Top address at the first entry of vector Table
    (uintptr_t ) &Reset_Handler,                //Address of Reset Handler                   
    (uintptr_t ) &NMI_Handler,                  //NMI Handler                                
    (uintptr_t ) &HardFault_Handler,            //Hard Fault Handler                        *** Processor Fault 
    (uintptr_t ) &MemManage_Handler,            //Memory Management Fault Handler           *** Processor Fault 
    (uintptr_t ) &BusFault_Handler,             //Bus Fault Handler                         *** Processor Fault 
    (uintptr_t ) &UsageFault_Handler,           //Usage Fault Handler                       *** Processor Fault 
                0,
                0,
                0,
                0,
    (uintptr_t ) &SVC_Handler,                  //Supervisor Call Handler trigerred by SVC Instruction
    (uintptr_t ) &DebugMon_Handler,             //Debug monitor Handler                 
                0,
    (uintptr_t ) &PendSV_Handler,               //Handler for interrupt-driven request for system-level service
    (uintptr_t ) &SysTick_Handler,              //SysTick Count->0 Interrupt handler

/*########################################

        Interrupt Service Routines

##########################################*/ 
    (uintptr_t ) &GPIOPortA_IRQHandler,
    (uintptr_t ) &GPIOPortB_IRQHandler,
    (uintptr_t ) &GPIOPortC_IRQHandler,
    (uintptr_t ) &GPIOPortD_IRQHandler,
    (uintptr_t ) &GPIOPortE_IRQHandler,         
    (uintptr_t ) &UART0_IRQHandler,             
    (uintptr_t ) &UART1_IRQHandler,
    (uintptr_t ) &SSI0_IRQHandler,
    (uintptr_t ) &I2C0_IRQHandler,
    (uintptr_t ) &PWMFault_IRQHandler,
    (uintptr_t ) &PWMGen0_IRQHandler,
    (uintptr_t ) &PWMGen1_IRQHandler,
    (uintptr_t ) &PWMGen2_IRQHandler,
    (uintptr_t ) &QEI0_IRQHandler,
    (uintptr_t ) &ADCSeq0_IRQHandler,
    (uintptr_t ) &ADCSeq1_IRQHandler,
    (uintptr_t ) &ADCSeq2_IRQHandler,
    (uintptr_t ) &ADCSeq3_IRQHandler,
    (uintptr_t ) &Watchdog_IRQHandler,
    (uintptr_t ) &Timer0A_IRQHandler,
    (uintptr_t ) &Timer0B_IRQHandler,
    (uintptr_t ) &Timer1A_IRQHandler,
    (uintptr_t ) &Timer1B_IRQHandler,           
    (uintptr_t ) &Timer2A_IRQHandler,
    (uintptr_t ) &Timer2B_IRQHandler,
    (uintptr_t ) &Comp0_IRQHandler,
    (uintptr_t ) &Comp1_IRQHandler,
    (uintptr_t ) &Comp2_IRQHandler,
    (uintptr_t ) &SysCtrl_IRQHandler,
    (uintptr_t ) &FlashCtrl_IRQHandler,
    (uintptr_t ) &GPIOPortF_IRQHandler,
    (uintptr_t ) &GPIOPortG_IRQHandler,
    (uintptr_t ) &GPIOPortH_IRQHandler,
    (uintptr_t ) &UART2_IRQHandler,             
    (uintptr_t ) &SSI1_IRQHandler,
    (uintptr_t ) &Timer3A_IRQHandler,
    (uintptr_t ) &Timer3B_IRQHandler,
    (uintptr_t ) &I2C1_IRQHandler,
    (uintptr_t ) &CAN0_IRQHandler,
    (uintptr_t ) &CAN1_IRQHandler,
    (uintptr_t ) &ETH_IRQHandler,               //Ethernet Interrupt
    (uintptr_t ) &Hibernate_IRQHandler,
    (uintptr_t ) &USB0_IRQHandler,
    (uintptr_t ) &PWMGen3_IRQHandler,
    (uintptr_t ) &uDMAST_IRQHandler,
    (uintptr_t ) &uDMAError_IRQHandler,         
    (uintptr_t ) &ADC1Seq0_IRQHandler,
    (uintptr_t ) &ADC1Seq1_IRQHandler,
    (uintptr_t ) &ADC1Seq2_IRQHandler,
    (uintptr_t ) &ADC1Seq3_IRQHandler,
    (uintptr_t ) &EBI0_IRQHandler,              //Peripheral Bus Interrupt
    (uintptr_t ) &GPIOPortJ_IRQHandler,
    (uintptr_t ) &GPIOPortK_IRQHandler,
    (uintptr_t ) &GPIOPortL_IRQHandler,
    (uintptr_t ) &SSI2_IRQHandler,
    (uintptr_t ) &SSI3_IRQHandler,
    (uintptr_t ) &UART3_IRQHandler,
    (uintptr_t ) &UART4_IRQHandler,
    (uintptr_t ) &UART5_IRQHandler,
    (uintptr_t ) &UART6_IRQHandler,
    (uintptr_t ) &UART7_IRQHandler,
    (uintptr_t ) &I2C2_IRQHandler,
    (uintptr_t ) &I2C3_IRQHandler,
    (uintptr_t ) &Timer4A_IRQHandler,           
    (uintptr_t ) &Timer4B_IRQHandler,
    (uintptr_t ) &Timer5A_IRQHandler,
    (uintptr_t ) &Timer5B_IRQHandler,
    (uintptr_t ) &FPU_IRQHandler,
                0,
                0,
    (uintptr_t ) &I2C4_IRQHandler,
    (uintptr_t ) &I2C5_IRQHandler,
    (uintptr_t ) &GPIOPortM_IRQHandler,
    (uintptr_t ) &GPIOPortN_IRQHandler,
                0,
    (uintptr_t ) &HibernateTamper_IRQHandler,   //Hibernate Tamper event Handler
    (uintptr_t ) &GPIOPortP0_IRQHandler,
    (uintptr_t ) &GPIOPortP1_IRQHandler,
    (uintptr_t ) &GPIOPortP2_IRQHandler,
    (uintptr_t ) &GPIOPortP3_IRQHandler,
    (uintptr_t ) &GPIOPortP4_IRQHandler,
    (uintptr_t ) &GPIOPortP5_IRQHandler,
    (uintptr_t ) &GPIOPortP6_IRQHandler,
    (uintptr_t ) &GPIOPortP7_IRQHandler,
    (uintptr_t ) &GPIOPortQ0_IRQHandler,
    (uintptr_t ) &GPIOPortQ1_IRQHandler,
    (uintptr_t ) &GPIOPortQ2_IRQHandler,
    (uintptr_t ) &GPIOPortQ3_IRQHandler,
    (uintptr_t ) &GPIOPortQ4_IRQHandler,
    (uintptr_t ) &GPIOPortQ5_IRQHandler,
    (uintptr_t ) &GPIOPortQ6_IRQHandler,
    (uintptr_t ) &GPIOPortQ7_IRQHandler,
                0,
                0,
                0,
                0,
                0,
                0,
    (uintptr_t ) &Timer6A_IRQHandler,
    (uintptr_t ) &Timer6B_IRQHandler,
    (uintptr_t ) &Timer7A_IRQHandler,
    (uintptr_t ) &Timer7B_IRQHandler,
    (uintptr_t ) &I2C6_IRQHandler,
    (uintptr_t ) &I2C7_IRQHandler,
                0,
                0,
                0,
                0,
                0,
    (uintptr_t ) &I2C8_IRQHandler,
    (uintptr_t ) &I2C9_IRQHandler,
                0,
                0,
                0    
};

static void* startup_memcpy(void * dst,const void * src, uint32_t sz)
{
    char* d = dst;
    const char* s = src;
    while(sz --)
    {
        *d++ = *s++;
    }
    return dst;
}

static void* startup_memset(void *dst,int c, uint32_t sz)
{
    char* d = dst;
    while(sz --)
    {
        *d++ = c;
    }
    return dst;
}
void _init(void);
void _init(void)
{
    //Init
}
void Reset_Handler(void)
{
    //extern int __libc_init_array(void); Need to check if safe for C to call static constructors
    //Reset Entry code
    //extern unsigned const __data_load;

    SystemInit();

    uint32_t initialized_data_size = (uintptr_t)&(__data_end__) - (uintptr_t)&(__data_start__);
    //Copy all initialized variables from .text section to .data section in SRAM
    //uint32_t* exidx_end = 
    startup_memcpy(&__data_start__,& __exidx_end,initialized_data_size);
    //uint32_t* sbss = exidx_end + initialized_data_size; // Go to beginning of .bss sector
    //Set all uninitialized variables to zero in .bss section
    uint32_t uninitialized_data_size = (uintptr_t)&(__bss_end__) - (uintptr_t)&(__bss_start__);
    startup_memset(&__bss_start__,0,uninitialized_data_size);    

    //Initialize all the static constructors
    // __libc_init_array();
    //Main starts here
    main();
}

void System_Handler(void)
{
    //Default Exception Handler Code
     __asm volatile (
        "    ldr r0,=str_sys\n\t"
        "    mov r1,#1\n\t"
        "    b assert_failed\n\t"
        "str_sys: .asciz \"System Fault\"\n\t"
        "  .align 2\n\t"
    );
}

void Interrupt_Service_Routine(void)
{
    //Default ISR
    //Do nothing
}
__attribute__((naked)) 
void Processor_Fault_Handler(void)
{
    // Processor Fault code
        __asm volatile (
        "    ldr r0,=str_hrd\n\t"
        "    mov r1,#1\n\t"
        "    b assert_failed\n\t"
        "str_hrd: .asciz \"Processor Fault\"\n\t"
        "  .align 2\n\t"
    );
}

__attribute__ ((naked, noreturn))
void assert_failed(char const *module, int loc) {
    /* re-set the SP in case of stack overflow */
    __asm volatile (
        "  MOV sp,%0\n\t"
        : : "r" (&__stack_top));

    Q_onAssert(module, loc); /* call the application-specific QP handler */

    for (;;) { /* should not be reached, but just in case loop forever... */
    }
}
/*

        "    b assert_failed\n\t"
*/