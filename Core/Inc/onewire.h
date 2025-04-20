#ifndef __ONEWIRE_H__
#define __ONEWIRE_H__

#include "stm32f4xx_hal.h"

typedef struct {
    GPIO_TypeDef *GPIOx;
    uint16_t GPIO_Pin;
} OneWire_t;

void OneWire_Init(OneWire_t *ow, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint8_t OneWire_Reset(OneWire_t *ow);
void OneWire_WriteBit(OneWire_t *ow, uint8_t bit);
uint8_t OneWire_ReadBit(OneWire_t *ow);
void OneWire_WriteByte(OneWire_t *ow, uint8_t byte);
uint8_t OneWire_ReadByte(OneWire_t *ow);

#endif
