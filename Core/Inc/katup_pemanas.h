
#ifndef VALVE_H
#define VALVE_H

#include <stdint.h>
#include "stm32f446xx.h"
#include "stm32f4xx.h"

// Makro untuk status GPIO
#define GPIO_PIN_RESET 0
#define GPIO_PIN_SET   1

void Valve_Open(void);
void Valve_Close(void);

// Struktur untuk Valve
typedef struct {
    GPIO_TypeDef *port;
    uint16_t pin;
    uint8_t is_open;
    uint8_t set_value;
} valve_t;

// Fungsi untuk menginisialisasi valve
void Valve_Init(valve_t *valve, GPIO_TypeDef *port, uint16_t pin);

// Fungsi untuk menerapkan nilai set_value pada valve
void Valve_ApplySetValue(valve_t *valve);

// Fungsi untuk mensimulasikan penulisan pin GPIOvoid HAL_GPIO_WritePin(GPIO_TypeDef *port, uint16_t pin, int state);

#endif // VALVE_H
