#ifndef __SENSOR_TEMPERATURE_H
#define __SENSOR_TEMPERATURE_H

#include "onewire.h"   // <- ini wajib! supaya kenal OneWire_t

void OneWire_Init(OneWire_t *ow, GPIO_TypeDef *port, uint16_t pin);
uint8_t OneWire_Reset(OneWire_t *ow);
void OneWire_WriteByte(OneWire_t *ow, uint8_t data);
uint8_t OneWire_ReadByte(OneWire_t *ow);

float DS18B20_ReadTemperature(void);

#endif /* __SENSOR_TEMPERATURE_H */
