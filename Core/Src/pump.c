#include "stm32f4xx_hal.h" // Include STM32 HAL for timer functions

// Motor direction constants
#define MOTOR_FORWARD   0
#define MOTOR_BACKWARD  1

void Pump_On(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);  // Ganti port/pin sesuai kebutuhan
}

void Pump_Off(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
}

typedef struct {
    TIM_HandleTypeDef *htim; // Pointer to the timer handle
    uint32_t channel;        // PWM channel
    int direction;           // Direction of the motor
    int speed;               // Speed of the motor (0-999)
} motor_t;

// Function prototypes
void Motor_Init(motor_t *motor, TIM_HandleTypeDef *htim, uint32_t channel);
void Motor_SetSpeed(motor_t *motor, int speed, int direction);

// Motor_Init function to initialize the motor
void Motor_Init(motor_t *motor, TIM_HandleTypeDef *htim, uint32_t channel) {
    motor->htim = htim;
    motor->channel = channel;
    motor->direction = MOTOR_FORWARD; // Default direction
    motor->speed = 0; // Default speed

    // Start PWM on the given channel
    HAL_TIM_PWM_Start(motor->htim, motor->channel);
}

// Motor_SetSpeed function to set motor speed and direction
void Motor_SetSpeed(motor_t *motor, int speed, int direction) {
    if (speed < 0) speed = 0;
    if (speed > 999) speed = 999;

    motor->speed = speed;
    motor->direction = direction;

    // Set PWM compare value to control motor speed
    __HAL_TIM_SET_COMPARE(motor->htim, motor->channel, speed);
}
