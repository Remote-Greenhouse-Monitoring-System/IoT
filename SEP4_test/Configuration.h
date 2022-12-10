/*
* configuration.h
*  Git: https://github.com/Remote-Greenhouse-Monitoring-System/IoT
*  Authors: Christopher, Himal, Jurin
*/
#pragma once
#include <stdint.h>
#include <lora_driver.h>

int16_t configuration_getMaxTemperature();
uint16_t configuration_getMaxHumidity();
void configuration_setMaxTemperature(int16_t maxTemp);
void configuration_setMaxHumidity(uint16_t maxHum);
void configuration_setConfiguration(lora_driver_payload_t payload);



