#ifndef __BOARDUTIL_H__
#define __BOARDUTIL_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "TM4C123GH6PM.h"
#include "uart_irqs.h"
#include "pc_buffer.h"
#include "gpio_port.h"


void serialDebugInit(void);
void DisableInterrupts(void);
void EnableInterrupts(void);

#endif
