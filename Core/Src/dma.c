#include "dma.h"
#include "stm32f4xx_hal.h"

// Inisialisasi handler DMA
DMA_HandleTypeDef hdma_i2c1_rx;
DMA_HandleTypeDef hdma_tim2_ch1;
DMA_HandleTypeDef hdma_adc1;

void MX_DMA_Init(void)
{
    // Aktifkan clock untuk DMA controller
    __HAL_RCC_DMA1_CLK_ENABLE();
    __HAL_RCC_DMA2_CLK_ENABLE();

    // Konfigurasi prioritas interrupt DMA (jika dibutuhkan)
    HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);

    HAL_NVIC_SetPriority(DMA1_Stream1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream1_IRQn);

    HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

    // NOTE:
    // Konfigurasi detail untuk masing-masing DMA (source, dest, direction, dll)
    // biasanya dilakukan di inisialisasi peripheral masing-masing
    // seperti di MX_I2C1_Init(), MX_ADC1_Init(), atau MX_TIM2_Init()
}
