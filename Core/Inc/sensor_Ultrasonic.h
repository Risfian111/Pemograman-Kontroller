#ifndef __SENSOR_ULTRASONIC_H__
#define __SENSOR_ULTRASONIC_H__

#include "stm32f4xx_hal.h"

void HCSR04_Init(TIM_HandleTypeDef *htim, GPIO_TypeDef *trigPort, uint16_t trigPin, GPIO_TypeDef *echoPort, uint16_t echoPin);
float HCSR04_ReadDistance(void);

#endif
