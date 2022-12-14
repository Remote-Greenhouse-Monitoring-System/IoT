#pragma once

#include "lora_driver.h"

#define PAYLOAD_SIZE 7

void set_temperature_percent(int16_t temperature);
void set_humidity_percent(uint16_t humidity);
void set_CO2_ppm(uint16_t co2ppm);
void set_status(uint8_t stat);
void set_light_lux(float lux_measurement);

lora_driver_payload_t get_lora_package(uint8_t port);