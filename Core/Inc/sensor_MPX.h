#ifndef __SENSOR_PRESSURE_H__
#define __SENSOR_PRESSURE_H__

#include "stm32f4xx_hal.h"

void MPX5700AP_Init(ADC_HandleTypeDef *hadc);
float MPX5700AP_ReadPressure(void);

#endif
