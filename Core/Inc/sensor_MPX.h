// mpx5700ap.h
#ifndef MPX5700AP_H
#define MPX5700AP_H

#include <stdint.h>
#include "stm32f4xx.h"

// Fungsi inisialisasi sensor tekanan
void MPX5700AP_Init(ADC_HandleTypeDef *hadc);

// Fungsi membaca tekanan (rentang 1-15 kPa)
float MPX5700AP_ReadPressure(void);

#endif // MPX5700AP_H
