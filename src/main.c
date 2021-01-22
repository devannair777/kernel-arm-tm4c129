#include "kernel.h"
#include <stdio.h>
#include <sys/stat.h>
/* #include "lib/printf.h" */

uint32_t config_dir_value = 0x02;
uint32_t config_den_value = 0xff;
uint32_t uart0_test;

void _putchar(char c)
{
  //Do nothing checking lib/printf.c
}

/* 
    Lower level implementation of _(fcn_names) for stdlib functions
    like printf, scanf etc...
 */
int _fstat(int file, struct stat *st) {
  st->st_mode = S_IFCHR;
  return 0;
}

int _lseek(int file, int offset, int whence) {
  return 0;
}

int _close(int fd) {
  return -1;
}

int _write (int fd, char *buf, int count) {
  
  return 2;
}

/*
    Linker description file doesnt have heap allocated
    So change it first before debuggig on target hardware
 */

void *_sbrk(int incr) {
  static unsigned char *heap = (unsigned char *) 0x5000;
  unsigned char *prev_heap = heap;
  heap += incr;
  return prev_heap;
}
/* 
    End of lower level implementations
    required for stdlib
 */


int main()
{
    sysctl_clock_init(XTAL_25MHZ);
    struct unit_config config;
    struct unit_config* ptr_config = &config;
    ptr_config->config_value = config_dir_value; //DIR Value
    ptr_config->pins_to_configure = config_den_value; //DEN Value
    gpio_den_dir_set(GPIOA_AHB,ptr_config);
    UART0->RSR.RSR =  uart0_test + 0x03;
    printf("Kernel Init ...\n");

    while(1);
    return 0;
}

