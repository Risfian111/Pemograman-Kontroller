#include <stdio.h>
#include "katup_pemanas.h"
#include "stm32f4xx.h"

#define VALVE_GPIO_PORT GPIOA
#define VALVE_PIN GPIO_PIN_5

// Fungsi bantu untuk mendapatkan nama port (hanya untuk debugging)
const char* GPIO_PortName(GPIO_TypeDef *port) {
    if (port == GPIOA) return "GPIOA";
    else if (port == GPIOB) return "GPIOB";
    else if (port == GPIOC) return "GPIOC";
    else if (port == GPIOD) return "GPIOD";
    else if (port == GPIOE) return "GPIOE";
    else return "UNKNOWN";
}
void Valve_Open(void) {
    HAL_GPIO_WritePin(VALVE_GPIO_PORT, VALVE_PIN, GPIO_PIN_SET);
}

void Valve_Close(void) {
    HAL_GPIO_WritePin(VALVE_GPIO_PORT, VALVE_PIN, GPIO_PIN_RESET);
}

// Inisialisasi valve
void Valve_Init(valve_t *valve, GPIO_TypeDef *port, uint16_t pin) {
    valve->port = port;
    valve->pin = pin;
    valve->is_open = 0;
    valve->set_value = 0;

    // Set awal tertutup
    HAL_GPIO_WritePin(valve->port, valve->pin, GPIO_PIN_RESET);
}

// Apply nilai set_value ke valve
void Valve_ApplySetValue(valve_t *valve) {
    if (valve->set_value > 0) {
        HAL_GPIO_WritePin(valve->port, valve->pin, GPIO_PIN_SET);
        valve->is_open = 1;
    } else {
        HAL_GPIO_WritePin(valve->port, valve->pin, GPIO_PIN_RESET);
        valve->is_open = 0;
    }
}
