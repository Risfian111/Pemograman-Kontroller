// heater.h
#ifndef HEATER_H
#define HEATER_H

#include "stm32f4xx_hal.h"

typedef struct {
    GPIO_TypeDef *port;
    uint16_t pin;
    uint8_t state; // 0 = OFF, 1 = ON
} heater_t;

void Heater_Init(heater_t *heater, GPIO_TypeDef *port, uint16_t pin);
void Heater_On(heater_t *heater);
void Heater_Off(heater_t *heater);
void Heater_Toggle(heater_t *heater);

#endif
