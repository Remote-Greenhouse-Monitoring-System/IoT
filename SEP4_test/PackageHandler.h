/*
 * PackageHandler.h
 *
 * Created: 16/11/2022 09.48.46
 *  Author: jurin
 */ 


#pragma once


#include <lora_driver.h>

#define PAYLOAD_SIZE 7

void set_temperature_percent(int16_t temperature);
void set_humidity_percent(uint16_t humidity);
void set_CO2_ppm(uint16_t co2ppm);
void set_status(uint8_t stat);
lora_driver_payload_t get_lora_package(uint8_t port);


