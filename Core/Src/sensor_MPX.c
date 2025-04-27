#include "sensor_MPX.h"

// Variabel global ADC
static ADC_HandleTypeDef *pressure_adc;

// Dummy HAL Function Simulasi
uint32_t mock_adc_value = 2048; 

#ifdef SIMULATION
void HAL_ADC_Start(ADC_HandleTypeDef *hadc) {
   
}

void HAL_ADC_PollForConversion(ADC_HandleTypeDef *hadc, int timeout) {
   
}

uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef *hadc) {
    return mock_adc_value;
}

void HAL_ADC_Stop(ADC_HandleTypeDef *hadc) {
    
}
#else
#include "stm32f4xx_hal_adc.h"
#endif

// Inisialisasi sensor tekanan
void MPX5700AP_Init(ADC_HandleTypeDef *hadc) {
    pressure_adc = hadc;
}

// Fungsi membaca tekanan dengan batas 1–15 kPa
float MPX5700AP_ReadPressure(void) {
    HAL_ADC_Start(pressure_adc);
    HAL_ADC_PollForConversion(pressure_adc, 1000);
    uint32_t adc_val = HAL_ADC_GetValue(pressure_adc);
    HAL_ADC_Stop(pressure_adc);

    // Konversi ke voltase (ADC 12-bit, 3.3V)
    float voltage = (adc_val * 3.3f) / 4095.0f;

    // Konversi ke tekanan: (0.2V - 4.7V) ? (0 - 700 kPa)
    float pressure_kPa = ((voltage - 0.2f) * (700.0f / (4.7f - 0.2f)));

    // Batasi tekanan ke rentang 1–15 kPa
    if (pressure_kPa < 1.0f) pressure_kPa = 1.0f;
    if (pressure_kPa > 15.0f) pressure_kPa = 15.0f;

    return pressure_kPa;
}
