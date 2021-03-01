#include "config.h"

#ifdef MODULES
#include "module_test.h"
#else
#include "state_machine.h"
#endif

int main(void)
{    
    #ifdef MODULES
    module_t();
    #else
    def_aoModelTest();
    #endif

    return 0;
}