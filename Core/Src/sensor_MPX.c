#include "sensor_MPX.h"

static ADC_HandleTypeDef *pressure_adc;

void MPX5700AP_Init(ADC_HandleTypeDef *hadc) {
    pressure_adc = hadc;
}

float MPX5700AP_ReadPressure(void) {
    HAL_ADC_Start(pressure_adc);
    HAL_ADC_PollForConversion(pressure_adc, HAL_MAX_DELAY);
    uint32_t adc_val = HAL_ADC_GetValue(pressure_adc);
    HAL_ADC_Stop(pressure_adc);

    // ADC to Voltage
    float voltage = (adc_val * 3.3f) / 4095.0f;

    // Voltage to Pressure (0.2V - 4.7V => 0 - 700 kPa)
    float pressure_kPa = ((voltage - 0.2f) * (700.0f / (4.7f - 0.2f)));
    return pressure_kPa;
}
