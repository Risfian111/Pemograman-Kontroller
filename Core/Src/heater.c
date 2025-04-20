// heater.c
#include "heater.h"

void Heater_Init(heater_t *heater, GPIO_TypeDef *port, uint16_t pin) {
    heater->port = port;
    heater->pin = pin;
    heater->state = 0;

    HAL_GPIO_WritePin(heater->port, heater->pin, GPIO_PIN_RESET); // default OFF
}

void Heater_On(heater_t *heater) {
    HAL_GPIO_WritePin(heater->port, heater->pin, GPIO_PIN_SET);
    heater->state = 1;
}

void Heater_Off(heater_t *heater) {
    HAL_GPIO_WritePin(heater->port, heater->pin, GPIO_PIN_RESET);
    heater->state = 0;
}

void Heater_Toggle(heater_t *heater) {
    if (heater->state)
        Heater_Off(heater);
    else
        Heater_On(heater);
}
