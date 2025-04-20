#include "delay.h"

static TIM_HandleTypeDef *delay_timer;

void delay_init(TIM_HandleTypeDef *htim) {
    delay_timer = htim;

    HAL_TIM_Base_Start(htim);
}

void delay_us(uint16_t us) {
    __HAL_TIM_SET_COUNTER(delay_timer, 0);  // Reset timer counter
    while (__HAL_TIM_GET_COUNTER(delay_timer) < us);
}
