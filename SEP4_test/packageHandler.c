/*
 * PackageHandler.c
 *
 *  Github: https://github.com/Remote-Greenhouse-Monitoring-System/IoT
 *  Author: Christopher, Himal, Juraj
 */

#include "packageHandler.h"

static int16_t temperaturePercent = 0;
static uint16_t humidityPercent = 0;
static uint16_t CO2_PPM = 0;
static float lux = 0;
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

void set_light_lux(float lux_measurement){
	lux = lux_measurement;
}

void set_status(uint8_t stat){
	status = stat;
}

lora_driver_payload_t get_lora_package(uint8_t port){
	
	union float_bytes{
		float temp;
		uint8_t bytes[sizeof(float)];
		} holder;
		
		holder.temp = lux;
		
	
	lora_driver_payload_t payload;
	payload.portNo = port;
	payload.len = PAYLOAD_SIZE;
	payload.bytes[0] = temperaturePercent >> 8;
	payload.bytes[1] = temperaturePercent;
	payload.bytes[2] = humidityPercent >> 8;
	payload.bytes[3] = humidityPercent;
	payload.bytes[4] = CO2_PPM >> 8;
	payload.bytes[5] = CO2_PPM;
	payload.bytes[6] = holder.bytes[0];
	payload.bytes[7] = holder.bytes[1];
	payload.bytes[8] = holder.bytes[2];
	payload.bytes[9] = holder.bytes[3];
	payload.bytes[10] = status;
	
	return payload;
}