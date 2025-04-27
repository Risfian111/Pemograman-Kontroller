#include "sensor_Ultrasonic.h"
#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htim2; // pastikan htim2 dideklarasi di main.c

static GPIO_TypeDef *trig_port;
static uint16_t trig_pin;
static GPIO_TypeDef *echo_port;
static uint16_t echo_pin;

void HCSR04_Init(TIM_HandleTypeDef *htim, GPIO_TypeDef *t_port, uint16_t t_pin, GPIO_TypeDef *e_port, uint16_t e_pin) {
    trig_port = t_port;
    trig_pin = t_pin;
    echo_port = e_port;
    echo_pin = e_pin;
    
    HAL_TIM_IC_Start(htim, TIM_CHANNEL_1); // start input capture
}

void HCSR04_Trigger(void) {
    HAL_GPIO_WritePin(trig_port, trig_pin, GPIO_PIN_SET);
    HAL_Delay(10); // 10 microsecond pulse
    HAL_GPIO_WritePin(trig_port, trig_pin, GPIO_PIN_RESET);
}

int32_t Read_Echo_Time(void) {
    uint32_t timeout = 30000; // Timeout untuk hindari infinite loop

    // Tunggu Echo naik HIGH
    while(HAL_GPIO_ReadPin(echo_port, echo_pin) == GPIO_PIN_RESET) {
        if (--timeout == 0) return -1;
    }
    uint32_t start = __HAL_TIM_GET_COUNTER(&htim2);

    timeout = 30000;
    // Tunggu Echo turun LOW
    while(HAL_GPIO_ReadPin(echo_port, echo_pin) == GPIO_PIN_SET) {
        if (--timeout == 0) return -1;
    }
    uint32_t end = __HAL_TIM_GET_COUNTER(&htim2);

    // Hitung durasi dalam mikrodetik
    if (end >= start)
        return end - start;
    else
        return (0xFFFF - start + end); // kalau counter overflow
}

float HCSR04_ReadDistance(int32_t echo_time_us) {
    if (echo_time_us <= 0) return -1.0f;
    return echo_time_us * 0.0343f / 2.0f; // Rumus jarak = (waktu * kecepatan suara)/2
}
