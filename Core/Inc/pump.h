#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "stm32f4xx_hal.h"

// Definisi arah motor
#define MOTOR_FORWARD   0
#define MOTOR_BACKWARD  1

void Pump_On(void);
void Pump_Off(void);

// Struktur untuk motor
typedef struct {
    TIM_HandleTypeDef *htim;
    uint32_t channel;
    int direction;
    int speed;
} motor_t;

// Deklarasi fungsi
void Motor_Init(motor_t *motor, TIM_HandleTypeDef *htim, uint32_t channel);
void Motor_SetSpeed(motor_t *motor, int speed, int direction);

// Deklarasi fungsi tes
void test_Motor_Init();
void test_Motor_SetSpeed();

#endif // MOTOR_CONTROL_H
