/* Linker script to configure memory regions. */
__flash_start = 0x00000000;
__flash_length = 0x00100000;
__rom_start = 0x02000000;
__rom_length = 0x000F0000;
__sram_start = 0x20000000;
__sram_length = 0x00040000;

MEMORY
{
  FLASH (rx) : ORIGIN = __flash_start, LENGTH = __flash_length   /* 1024k */
  ROM (rwx) : ORIGIN = __rom_start, LENGTH = __rom_length   /* 960k */ 
  RAM (rwx)  : ORIGIN = __sram_start, LENGTH = __sram_length   /*  256k */
  
}

SEARCH_DIR(/usr/lib/arm-none-eabi/newlib/thumb/v7e-m+fp/softfp)
SEARCH_DIR(/usr/lib/gcc/arm-none-eabi/9.2.1)

/* Library configurations */
GROUP(libc_nano.a libm.a libnosys.a libgcc.a)

/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions FLASH and RAM.
 * It references following symbols, which must be defined in code:
 *   Reset_Handler : Entry of reset handler
 *
 * It defines following symbols, which code can use without definition:
 *   __exidx_start
 *   __exidx_end
 *   __etext
 *   __data_start__
 *   __preinit_array_start
 *   __preinit_array_end
 *   __init_array_start
 *   __init_array_end
 *   __fini_array_start
 *   __fini_array_end
 *   __data_end__
 *   __bss_start__
 *   __bss_end__
 *   __end__
 *   end
 *   __HeapLimit
 *   __StackLimit
 *   __StackTop
 *   __stack
 */
ENTRY(Reset_Handler)
__stack_size = 1024;
__heap_size = 256;
SECTIONS
{

    .isr_vector : {        /* the vector table goes FIRST into ROM */
        KEEP(*(.isr_vector)) /* vector table */
        . = ALIGN(4);
    } >FLASH

	.text :
	{
		*(.text)
        *(.text.*)

		KEEP(*(.init))
		KEEP(*(.fini))

		/* .ctors */
		*crtbegin.o(.ctors)
		*crtbegin?.o(.ctors)
		*(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
		*(SORT(.ctors.*))
		*(.ctors)

		/* .dtors */
 		*crtbegin.o(.dtors)
 		*crtbegin?.o(.dtors)
 		*(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
 		*(SORT(.dtors.*))
 		*(.dtors)

		*(.rodata*)
		. = ALIGN(4);
		KEEP(*(.eh_frame*))
	} > FLASH
	
		__etext = .;

	.ARM.extab :
	{
		*(.ARM.extab* .gnu.linkonce.armextab.*)
	} > FLASH

	__exidx_start = .;
	.ARM.exidx :
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
	} > FLASH
	__exidx_end = .;

	

	.stack : 
	{
		. = ALIGN(4);
		__stack_start__ = .;
		. = . + __stack_size;
		. = ALIGN(4);
		__stack_end__ = .;
		__stack_top = __stack_end__;
		PROVIDE(__stack = __stack_top);

	} > RAM


	.data : AT (__exidx_end)
	{
		. = ALIGN(4);
		__data_load = LOADADDR (.data);
		__data_start__ = .;
		*(vtable)
		*(.data)
		*(.data*)

		. = ALIGN(4);
		/* preinit data */
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP(*(.preinit_array))
		PROVIDE_HIDDEN (__preinit_array_end = .);

		. = ALIGN(4);
		/* init data */
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP(*(SORT(.init_array.*)))
		KEEP(*(.init_array))
		PROVIDE_HIDDEN (__init_array_end = .);


		. = ALIGN(4);
		/* finit data */
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP(*(SORT(.fini_array.*)))
		KEEP(*(.fini_array))
		PROVIDE_HIDDEN (__fini_array_end = .);

		KEEP(*(.jcr*))
		. = ALIGN(4);
		/* All data end */
		__data_end__ = .;

	} > RAM

	
	.bss :
	{
		. = ALIGN(4);
		__bss_start__ = .;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end__ = .;
	} > RAM

	.heap :
	{
		. = ALIGN(4);
		__heap_start__ = .;
		. = . + __heap_size;
		. = ALIGN(4);
		__end__ = .;
		__HeapLimit = __end__;
		end = __end__;
		*(.heap*)
		
	} > RAM

	/* Remove information from the standard libraries */
    /DISCARD/ : {
        libc.a ( * )
        libm.a ( * )
        libgcc.a ( * )
    }

	/* .stack_dummy section doesn't contains any symbols. It is only
	 * used for linker to calculate size of stack sections, and assign
	 * values to stack symbols later */
	/*.stack_dummy (COPY):
	 {
		*(.stack*)
	} > RAM
 */
	/* Set stack top to end of RAM, and stack limit move down by
	 * size of stack_dummy section */
	/* __stack_top = ORIGIN(RAM) + LENGTH(RAM); */
	/* __StackLimit = __StackTop - SIZEOF(.stack_dummy); */
	/* __stack_limit = __stack_top - __stack_size;
	PROVIDE(__stack = __stack_top); */

	/* Check if data + heap + stack exceeds RAM limit */
	/* ASSERT(__stack_limit >= __HeapLimit, "region RAM overflowed with stack") */
}

/* 
.text program code;
.rodata read-only data;
.data read-write initialized data;
.bss read-write zero initialized data.
 */