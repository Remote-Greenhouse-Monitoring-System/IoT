/*
 * PackageHandler.c
 *
 * Created: 16/11/2022 09.49.13
 *  Author: jurin
 */ 

#include "PackageHandler.h"
#include "lora_driver.h"

static int16_t temperaturePercent;
static int16_t humidityPercent;

void setTemperaturePercent(int16_t temperature){
	temperaturePercent = temperature;
}

void setHumidityPercent(int16_t humidity){
	humidityPercent = humidity;
}

lora_driver_payload_t getLoraPackage(uint8_t port){
	lora_driver_payload_t payload;
	payload.portNo = port;
	payload.len = PAYLOAD_SIZE;
	payload.bytes[0] = temperaturePercent >> 8;
	payload.bytes[1] = temperaturePercent;
	payload.bytes[2] = humidityPercent >> 8;
	payload.bytes[3] = humidityPercent;
	
	return payload;
}