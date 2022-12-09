/*
 * PackageHandler.h
 *
 * Created: 16/11/2022 09.48.46
 *  Author: jurin, Christopher
 */ 


#pragma once


#include "lora_driver.h"

#define PAYLOAD_SIZE 7

void packageHandler_setTemperaturePercent(int16_t temperature);
void packageHandler_setHumidityPercent(uint16_t humidity);
void packageHandler_setCO2ppm(uint16_t co2ppm);
lora_driver_payload_t packageHandler_getLoraPackage(uint8_t port);


