#ifndef __CONFIG_H__
#define __CONFIG_H__
#include "tm4c1294ncpdt.h"
#include "cmsis/tm4c_cmsis.h"
#include <stdint.h>
#include <uc_ao.h>
#define F_CPU   25000000UL
#define UART_BDR    9600
#define PART_TM4C1294NCPDT // defined in makedefs
                           // as PART=TM4C1294NCPDT
#include "driverlib/pin_map.h"
#define LED1    (1<<1)          /* PN1 */
#define LED2    (1<<0)          /* PN0 */
#define LED3    (1<<4)          /* PF4 */
#define LED4    (1<<0)          /* PF0 */

#define SW1     (1<<0)          /* PJ0 */
#define SW2     (1<<1)          /* PJ1 */

#endif //CONFIG_H