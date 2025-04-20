// sensor_YF.h
#ifndef SENSOR_YF_H
#define SENSOR_YF_H

#include "stm32f4xx_hal.h"

void YF_S201_Init(TIM_HandleTypeDef *htim);
void YF_S201_IncrementPulse(void);
float YF_S201_ReadFlow(void);

#endif
