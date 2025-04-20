// valve.h
#ifndef VALVE_H
#define VALVE_H

#include "stm32f4xx_hal.h"

typedef struct {
    GPIO_TypeDef *port;
    uint16_t pin;
    uint8_t is_open; // 0 = tertutup, 1 = terbuka
} valve_t;

void Valve_Init(valve_t *valve, GPIO_TypeDef *port, uint16_t pin);
void Valve_Open(valve_t *valve);
void Valve_Close(valve_t *valve);
void Valve_Toggle(valve_t *valve);

#endif
