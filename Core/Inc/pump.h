// pump.h
#ifndef PUMP_H
#define PUMP_H

#include "stm32f4xx_hal.h"

#define PUMP_FORWARD   0
#define PUMP_BACKWARD  1

typedef struct {
    TIM_HandleTypeDef *htim;
    uint32_t channel;
    int direction;
    int speed;
} pump_t;

void Pump_Init(pump_t *pump, TIM_HandleTypeDef *htim, uint32_t channel);
void Pump_SetSpeed(pump_t *pump, int speed, int direction);

#endif
