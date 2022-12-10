/*
* packageHandler.c
*  Git: https://github.com/Remote-Greenhouse-Monitoring-System/IoT
*  Authors: Christopher, Himal, Jurin
*/

#include <lora_driver.h>

#include "packageHandler.h"

static int16_t temperaturePercent;
static uint16_t humidityPercent;
static uint16_t CO2_PPM;
static uint8_t status = 0x10;

void packageHandler_setTemperaturePercent(int16_t temperature){
	temperaturePercent = temperature;
}

void packageHandler_setHumidityPercent(uint16_t humidity){
	humidityPercent = humidity;
}

void packageHandler_setCO2ppm(uint16_t co2ppm){
	CO2_PPM = co2ppm;
}

lora_driver_payload_t packageHandler_getLoraPackage(uint8_t port){
	lora_driver_payload_t payload;
	payload.portNo = port;
	payload.len = PAYLOAD_SIZE;
	payload.bytes[0] = temperaturePercent >> 8;
	payload.bytes[1] = temperaturePercent;
	payload.bytes[2] = humidityPercent >> 8;
	payload.bytes[3] = humidityPercent;
	payload.bytes[4] = CO2_PPM >> 8;
	payload.bytes[5] = CO2_PPM;
	payload.bytes[6] = status;
	
	return payload;
}