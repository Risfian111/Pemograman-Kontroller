// pump.c
#include "pump.h"

void Pump_Init(pump_t *pump, TIM_HandleTypeDef *htim, uint32_t channel) {
    pump->htim = htim;
    pump->channel = channel;
    pump->direction = PUMP_FORWARD;
    pump->speed = 0;

    HAL_TIM_PWM_Start(pump->htim, pump->channel);
}

void Pump_SetSpeed(pump_t *pump, int speed, int direction) {
    if (speed < 0) speed = 0;
    if (speed > 999) speed = 999;

    if (direction == PUMP_BACKWARD) {
        pump->direction = PUMP_BACKWARD;
    } else {
        pump->direction = PUMP_FORWARD;
    }

    pump->speed = speed;

    __HAL_TIM_SET_COMPARE(pump->htim, pump->channel, speed);
}
