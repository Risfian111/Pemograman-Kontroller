// yf_s201.h
#ifndef YF_S201_H
#define YF_S201_H

#include <stdint.h>
#include "stm32f4xx.h"

// Fungsi untuk inisialisasi sensor
void YF_S201_Init(TIM_HandleTypeDef *htim);

// Fungsi untuk mengubah nilai konversi (pulsa per liter/menit)
void YF_S201_SetConversionFactor(float factor);

// Fungsi untuk menambah jumlah pulsa
void YF_S201_IncrementPulse(void);

// Fungsi untuk membaca laju aliran air (L/m) dengan batas bawah dan atas
float YF_S201_ReadFlow(void);

#endif // YF_S201_H
