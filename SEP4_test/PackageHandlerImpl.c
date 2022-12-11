/*
 * PackageHandler.c
 *
 * Created: 16/11/2022 09.49.13
 *  Author: jurin
 */ 

#include "PackageHandler.h"

static int16_t temperaturePercent = 0;
static uint16_t humidityPercent = 0;
static uint16_t CO2_PPM = 0;
static uint8_t status = 0;

void set_temperature_percent(int16_t temperature){
	temperaturePercent = temperature;
}

void set_humidity_percent(uint16_t humidity){
	humidityPercent = humidity;
}

void set_CO2_ppm(uint16_t co2ppm){
	CO2_PPM = co2ppm;
}

void set_status(uint8_t stat){
	status = stat;
}

lora_driver_payload_t get_lora_package(uint8_t port){
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