#ifndef	BSP_H_
#define BSP_H_

#include "stm32g0xx.h"
#include "ADC.h"
#include "display.h"


void BSP_system_init();


void init_timer1();
void init_timer3();
void BSP_button_init();


#endif
