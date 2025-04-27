#include "onewire.h"

void OneWire_Init(OneWire_t *ow, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
    ow->GPIOx = GPIOx;
    ow->GPIO_Pin = GPIO_Pin;

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
}

uint8_t OneWire_Reset(OneWire_t *ow) {
    uint8_t presence;

    HAL_GPIO_WritePin(ow->GPIOx, ow->GPIO_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(ow->GPIOx, ow->GPIO_Pin, GPIO_PIN_SET);
    HAL_Delay(1);

    presence = HAL_GPIO_ReadPin(ow->GPIOx, ow->GPIO_Pin);
    HAL_Delay(1);

    return (presence == GPIO_PIN_RESET);
}

void OneWire_WriteBit(OneWire_t *ow, uint8_t bit) {
    HAL_GPIO_WritePin(ow->GPIOx, ow->GPIO_Pin, GPIO_PIN_RESET);
    if (bit) HAL_GPIO_WritePin(ow->GPIOx, ow->GPIO_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(ow->GPIOx, ow->GPIO_Pin, GPIO_PIN_SET);
}

uint8_t OneWire_ReadBit(OneWire_t *ow) {
    uint8_t bit = 0;

    HAL_GPIO_WritePin(ow->GPIOx, ow->GPIO_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(ow->GPIOx, ow->GPIO_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    bit = HAL_GPIO_ReadPin(ow->GPIOx, ow->GPIO_Pin);

    return bit;
}

void OneWire_WriteByte(OneWire_t *ow, uint8_t byte) {
    for (uint8_t i = 0; i < 8; i++) {
        OneWire_WriteBit(ow, byte & (1 << i));
    }
}

uint8_t OneWire_ReadByte(OneWire_t *ow) {
    uint8_t byte = 0;
    for (uint8_t i = 0; i < 8; i++) {
        byte |= (OneWire_ReadBit(ow) << i);
    }
    return byte;
}
