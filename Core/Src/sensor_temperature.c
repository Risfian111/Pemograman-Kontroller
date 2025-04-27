#include "onewire.h"
#include "sensor_temperature.h"

OneWire_t ow = {
    .GPIOx = GPIOB,
    .GPIO_Pin = GPIO_PIN_9
};

float DS18B20_ReadTemperature(void)
{
    uint8_t temp_lsb, temp_msb;
    int16_t temp;

    OneWire_Reset(&ow);
    OneWire_WriteByte(&ow, 0xCC); 
    OneWire_WriteByte(&ow, 0x44);
    HAL_Delay(750);

    OneWire_Reset(&ow);
    OneWire_WriteByte(&ow, 0xCC); 
    OneWire_WriteByte(&ow, 0xBE); 

    temp_lsb = OneWire_ReadByte(&ow);
    temp_msb = OneWire_ReadByte(&ow);

    temp = (temp_msb << 8) | temp_lsb;
    return temp / 16.0;
}
