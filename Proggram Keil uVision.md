
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

```

## katup Pemanas 

Proggram Library Katup pemanas

```bash
#ifndef VALVE_H
#define VALVE_H

#include "stm32f4xx_hal.h" // Pastikan untuk menyertakan HAL jika diperlukan

// Definisi pin untuk katup pemanas
#define VALVE_PIN GPIO_PIN_1 // Ganti dengan pin yang sesuai
#define VALVE_PORT GPIOB     // Ganti dengan port yang sesuai

// Fungsi untuk menginisialisasi katup pemanas
void Valve_Init(void);

// Fungsi untuk membuka katup pemanas
void Valve_Open(void);

// Fungsi untuk menutup katup pemanas
void Valve_Close(void);

// Fungsi untuk memeriksa status katup pemanas
uint8_t Valve_GetStatus(void);

#endif // VALVE_H
```

## Pump

Proggram Library Pump

```bash
#ifndef PUMP_H
#define PUMP_H

#include "stm32f4xx_hal.h" // Pastikan untuk menyertakan HAL jika diperlukan

// Definisi pin untuk pompa
#define PUMP_PIN GPIO_PIN_0 // Ganti dengan pin yang sesuai
#define PUMP_PORT GPIOA     // Ganti dengan port yang sesuai

// Fungsi untuk menginisialisasi pompa
void Pump_Init(void);

// Fungsi untuk menghidupkan pompa
void Pump_On(void);

// Fungsi untuk mematikan pompa
void Pump_Off(void);

// Fungsi untuk memeriksa status pompa
uint8_t Pump_GetStatus(void);

#endif // PUMP_H
```

## Main Proggram

Main Proggram

```bash
#include "stm32f4xx_hal.h"
#include "ds18b20.h"
#include "mpx5700ap.h"
#include "yf_s201.h"
#include "hcsr04.h"
#include "pump.h"  // Header file untuk pompa
#include "valve.h" // Header file untuk katup pemanas

// Deklarasi fungsi untuk menginisialisasi UART
void UART_Init(void);
void UART_SendString(char* str);

int main(void) {
    // Inisialisasi HAL
    HAL_Init();

    // Inisialisasi sistem clock
    SystemClock_Config();

    // Inisialisasi UART
    UART_Init();

    // Inisialisasi sensor
    DS18B20_Init();
    MPX5700AP_Init();
    YF_S201_Init();
    HCSR04_Init();

    // Inisialisasi pompa dan katup pemanas
    Pump_Init();
    Valve_Init();

    // Buka katup pemanas dan hidupkan pompa
    Valve_Open();
    Pump_On();

    while (1) {
        // Membaca suhu dari DS18B20
        float temperature = DS18B20_ReadTemperature();
        char buffer[50];
        snprintf(buffer, sizeof(buffer), "Temperature: %.2f C\r\n", temperature);
        UART_SendString(buffer);

        // Membaca tekanan dari MPX5700AP
        float pressure = MPX5700AP_ReadPressure();
        snprintf(buffer, sizeof(buffer), "Pressure: %.2f kPa\r\n", pressure);
        UART_SendString(buffer);

        // Membaca aliran dari YF-S201
        float flow = YF_S201_ReadFlow();
        snprintf(buffer, sizeof(buffer), "Flow: %.2f L/min\r\n", flow);
        UART_SendString(buffer);

        // Membaca jarak dari HC-SR04
        float distance = HCSR04_ReadDistance();
        snprintf(buffer, sizeof(buffer), "Distance: %.2f cm\r\n", distance);
        UART_SendString(buffer);

        // Delay sebelum pembacaan berikutnya
        HAL_Delay(1000); // Delay 1 detik
    }
}

void UART_Init(void) {
    // Inisialisasi UART (misalnya USART2)
    // Ganti dengan konfigurasi UART yang sesuai
    __HAL_RCC_USART2_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Inisialisasi GPIO untuk TX
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct.Pin = GPIO_PIN_2; // TX pin
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Inisialisasi UART
    UART_HandleTypeDef huart2;
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 9600;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&huart2);
}

void UART_SendString(char* str) {
    // Mengirim string melalui UART
    HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
}

```

