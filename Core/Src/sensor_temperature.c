#include "sensor_temperature.h"
#include "onewire.h"

OneWire_t ow;

void DS18B20_Init(void) {
    OneWire_Init(&ow, GPIOB, GPIO_PIN_6); // Ganti pin dan port sesuai konfigurasi kamu
}

float DS18B20_ReadTemperature(void) {
    uint8_t temp_lsb, temp_msb;
    int16_t temp_raw;

    OneWire_Reset(&ow);
    OneWire_WriteByte(&ow, 0xCC);
    OneWire_WriteByte(&ow, 0x44);

    HAL_Delay(750);

    OneWire_Reset(&ow);
    OneWire_WriteByte(&ow, 0xCC);
    OneWire_WriteByte(&ow, 0xBE);

    temp_lsb = OneWire_ReadByte(&ow);
    temp_msb = OneWire_ReadByte(&ow);
    temp_raw = (temp_msb << 8) | temp_lsb;

    return (float)temp_raw / 16.0f;
}
