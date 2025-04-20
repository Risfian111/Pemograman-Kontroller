// valve.c
#include "katup pemanas.h"

void Valve_Init(valve_t *valve, GPIO_TypeDef *port, uint16_t pin) {
    valve->port = port;
    valve->pin = pin;
    valve->is_open = 0;

    HAL_GPIO_WritePin(valve->port, valve->pin, GPIO_PIN_RESET); // tertutup
}

void Valve_Open(valve_t *valve) {
    HAL_GPIO_WritePin(valve->port, valve->pin, GPIO_PIN_SET);
    valve->is_open = 1;
}

void Valve_Close(valve_t *valve) {
    HAL_GPIO_WritePin(valve->port, valve->pin, GPIO_PIN_RESET);
    valve->is_open = 0;
}

void Valve_Toggle(valve_t *valve) {
    if (valve->is_open)
        Valve_Close(valve);
    else
        Valve_Open(valve);
}
