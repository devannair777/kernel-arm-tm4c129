/* 
    Dummy file to check the build procedure
 */


int add(int x, int y)
{
    return x+y;
}

/* 

/*
    Lower level implementation of _(fcn_names) for stdlib functions
    like printf, scanf etc...
 */

/*  int _fstat(int file, struct stat *st) {
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
*/
/*
    Linker description file doesnt have heap allocated
    So change it first before debuggig on target hardware
 */
/*  
void *_sbrk(int incr) {
  static unsigned char *heap = (unsigned char *) 0x5000;
  unsigned char *prev_heap = heap;
  heap += incr;
  return prev_heap;
}  */
/*  
    End of lower level implementations
    required for stdlib
 */


 */