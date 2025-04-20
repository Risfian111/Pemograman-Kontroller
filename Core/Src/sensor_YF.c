// sensor_YF.c
#include "sensor_YF.h"

volatile uint32_t pulseCount = 0;

void YF_S201_Init(TIM_HandleTypeDef *htim) {
    HAL_TIM_IC_Start_IT(htim, TIM_CHANNEL_1);
}

void YF_S201_IncrementPulse(void) {
    pulseCount++;
}

float YF_S201_ReadFlow(void) {
    float flowRate = (pulseCount / 7.5); // 7.5 pulse/Liter as example
    pulseCount = 0;
    return flowRate;
}
