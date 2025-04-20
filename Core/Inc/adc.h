#ifndef __ADC_H__
#define __ADC_H__

#include "stm32f4xx_hal.h"

extern ADC_HandleTypeDef hadc1;

void MX_ADC1_Init(void);
void Error_Handler(void);

#endif
