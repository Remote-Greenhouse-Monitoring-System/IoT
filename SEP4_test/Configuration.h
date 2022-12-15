/*
 * Configuration.h
 *  Github: https://github.com/Remote-Greenhouse-Monitoring-System/IoT
 *  Author: Christopher, Himal, Juraj
 */

#pragma once


#include <stdint.h>
#include <lora_driver.h>
#include <semphr.h>
#include <stdio.h>

typedef enum system_status_codes{
	TEMPERATURE_ACTION_ON = 0x01,
	TEMPERATURE_ACTION_OFF = 0xFE,
	HUMIDITY_ACTION_ON = 0x02,
	HUMIDITY_ACTION_OFF = 0xFD,
	CO2_ACTION_ON = 0x04,
	CO2_ACTION_OFF = 0xFB
} system_status_code_t;


void set_max_temperature(int16_t maxTemp);
void set_min_temperature(int16_t minTemp);
int16_t get_max_temperature();
void set_max_humidity(uint16_t maxHum);
void set_min_humidity(uint16_t minHum);
uint16_t get_max_humidity();
void set_max_co2(uint16_t maxCO2);
void set_min_co2(uint16_t minCO2);
uint16_t get_max_co2();

void set_system_status(system_status_code_t statusCode);
uint8_t get_system_status();
void setConfiguration(lora_driver_payload_t payload);



