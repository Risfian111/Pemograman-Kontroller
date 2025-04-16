
# Pemograman Kontroller Kelompok 8

Tugas Pemograman Kontroller Kelas B 


## Sensor Ultrasonik

Proggram Library sensor Ultrasonik

```bash
#ifndef HCSR04_H
#define HCSR04_H

#include "stm32f4xx_hal.h" // Ganti dengan header HAL yang sesuai dengan STM32 Anda

// Definisikan pin untuk HC-SR04
#define HCSR04_TRIGGER_PIN GPIO_PIN_0 // Ganti dengan pin yang sesuai
#define HCSR04_TRIGGER_PORT GPIOA      // Ganti dengan port yang sesuai
#define HCSR04_ECHO_PIN GPIO_PIN_1     // Ganti dengan pin yang sesuai
#define HCSR04_ECHO_PORT GPIOA          // Ganti dengan port yang sesuai

// Fungsi untuk menginisialisasi HC-SR04
void HCSR04_Init(void);

// Fungsi untuk mengukur jarak
float HCSR04_ReadDistance(void);

// Fungsi untuk menunggu hingga sinyal echo diterima
void HCSR04_WaitForEcho(uint32_t timeout);

#endif // HCSR04_H
```
    

## Sensor Temperatur

Proggram Library Sensor Temperatur

```bash
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
```


## Sensor YF

Proggram Library Sensor YF

```bash
#ifndef YF_S201_H
#define YF_S201_H

#include "stm32f4xx_hal.h" // Ganti dengan header HAL yang sesuai dengan STM32 Anda

// Definisikan pin dan port untuk YF-S201
#define YF_S201_PIN GPIO_PIN_1 // Ganti dengan pin yang sesuai
#define YF_S201_PORT GPIOA      // Ganti dengan port yang sesuai

// Fungsi untuk menginisialisasi YF-S201
void YF_S201_Init(void);

// Fungsi untuk membaca aliran dari YF-S201
float YF_S201_ReadFlow(void);

// Fungsi untuk menghitung aliran berdasarkan jumlah pulsa
void YF_S201_PulseHandler(void);

// Variabel untuk menyimpan jumlah pulsa
extern volatile uint32_t pulseCount;

#endif // YF_S201_H

```

## Sensor MPX

Proggram Library Sensor MPX

```bash
#ifndef MPX5700AP_H
#define MPX5700AP_H

#include "stm32f4xx_hal.h" // Ganti dengan header HAL yang sesuai dengan STM32 Anda

// Fungsi untuk menginisialisasi ADC
void MPX5700AP_Init(void);

// Fungsi untuk membaca nilai tekanan dari MPX5700AP
float MPX5700AP_ReadPressure(void);

// Fungsi untuk mengkonversi nilai ADC ke tekanan (dalam kPa)
float MPX5700AP_ADCToPressure(uint32_t adcValue);

#endif // MPX5700AP_H
