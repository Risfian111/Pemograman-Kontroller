#ifndef DS18B20_H
#define DS18B20_H

#include "stm32f4xx_hal.h" // Ganti dengan header HAL yang sesuai dengan STM32 Anda

// Pin yang digunakan untuk DS18B20
#define DS18B20_PIN GPIO_PIN_0 // Ganti dengan pin yang sesuai
#define DS18B20_PORT GPIOA      // Ganti dengan port yang sesuai

// Fungsi untuk menginisialisasi DS18B20
void DS18B20_Init(void);

// Fungsi untuk membaca suhu dari DS18B20
float DS18B20_ReadTemperature(void);

// Fungsi untuk mengatur pin sebagai input
void DS18B20_SetPinInput(void);

// Fungsi untuk mengatur pin sebagai output
void DS18B20_SetPinOutput(void);

// Fungsi untuk menulis logika tinggi atau rendah ke pin
void DS18B20_WritePin(GPIO_PinState state);

// Fungsi untuk membaca status pin
GPIO_PinState DS18B20_ReadPin(void);

// Fungsi untuk menunggu selama beberapa mikrodetik
void DS18B20_DelayMicroseconds(uint16_t us);

#endif // DS18B20_H