// heater.c
#include <stdio.h>
#include "heater.h"
#include "stm32f446xx.h"
#include "stm32f4xx.h"


// Implementasi fungsi untuk menginisialisasi heater
void Heater_Init(heater_t *heater, GPIO_TypeDef *port, uint16_t pin) {
    heater->port = port;
    heater->pin = pin;
    heater->state = 0;
    HAL_GPIO_WritePin(heater->port, heater->pin, GPIO_PIN_RESET);
}

// Implementasi fungsi untuk menyalakan heater
void Heater_On(heater_t *heater) {
    HAL_GPIO_WritePin(heater->port, heater->pin, GPIO_PIN_SET);
    heater->state = 1;
}

// Implementasi fungsi untuk mematikan heater
void Heater_Off(heater_t *heater) {
    HAL_GPIO_WritePin(heater->port, heater->pin, GPIO_PIN_RESET);
    heater->state = 0;
}

// Implementasi fungsi untuk toggle heater
void Heater_Toggle(heater_t *heater) {
    if (heater->state)
        Heater_Off(heater);
    else
        Heater_On(heater);
}
