#ifndef __DELAY_H__
#define __DELAY_H__

#include "stm32f4xx_hal.h"

void delay_init(TIM_HandleTypeDef *htim);
void delay_us(uint16_t us);

#endif
