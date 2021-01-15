#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "config.h"

struct unit_config {
    uint32_t pins_to_configure;
    uint32_t config_value;
};


void sysctl_clock_init(int xtal_mode);

void gpio_den_dir_set(GPIOA_AHB_Type* gpio,struct unit_config* unit_config);

#endif //KERNEL_H