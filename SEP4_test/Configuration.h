/*
 * Configuration.h
 *
 * Created: 06/12/2022 18.42.11
 *  Author: jurin
 */ 

#pragma once


#include <stdint.h>
#include <lora_driver.h>
#include <semphr.h>

int16_t get_max_temperature();
uint16_t get_max_humidity();
void set_max_temperature(int16_t maxTemp);
void set_max_humidity(uint16_t maxHum);
void setConfiguration(lora_driver_payload_t payload);



