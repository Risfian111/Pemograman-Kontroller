// yf_s201.c
#include "sensor_YF.h"

// Variabel global
static volatile uint32_t pulse_count = 0;
static float conversion_factor = 7.5f; 
static TIM_HandleTypeDef *timer;

// Fungsi untuk inisialisasi sensor
void YF_S201_Init(TIM_HandleTypeDef *htim) {
    pulse_count = 0;
    timer = htim;
}

// Fungsi untuk set nilai konversi
void YF_S201_SetConversionFactor(float factor) {
    if (factor > 0)
        conversion_factor = factor;
}

// Fungsi untuk menambah pulsa
void YF_S201_IncrementPulse(void) {
    pulse_count++;
}

// Fungsi untuk membaca laju aliran air (L/m) dengan batas bawah dan atas
float YF_S201_ReadFlow(void) {
    float flow_rate = (pulse_count / conversion_factor); 

    // Reset pulse setelah membaca
    pulse_count = 0;

    if (flow_rate < 1.0f)
        flow_rate = 1.0f;
    else if (flow_rate > 30.0f)
        flow_rate = 30.0f;

    return flow_rate;
}
