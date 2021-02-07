#include "syshw.h"

#ifdef MODULES
#include "module_test.h"
#else
#include "state_machine.h"
#endif


int main(void)
{
    default_clock_init();
    
    #ifdef MODULES
    module_t();
    #else
    state_machine_exec();
    #endif

    return 0;
}

