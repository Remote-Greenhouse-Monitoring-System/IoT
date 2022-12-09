/*
 * Configuration.h
 *
 * Created: 06/12/2022 18.42.11
 *  Author: jurin, Christopher
 */ 

#pragma once


#include <stdint.h>
#include <lora_driver.h>
#include <semphr.h>

int16_t configuration_getMaxTemperature();
uint16_t configuration_getMaxHumidity();
void configuration_setMaxTemperature(int16_t maxTemp);
void configuration_setMaxHumidity(uint16_t maxHum);
void configuration_setConfiguration(lora_driver_payload_t payload);



