#include "lib/prompt.h"

void module_t()
{
    serial_init();
    printk("Initializing Module Test Routine ...\r\n");
    while(1);
    
}