/*
 * ConfigurationImpl.c
 *
 * Created: 06/12/2022 18.45.41
 *  Author: jurin
 */ 


#include "Configuration.h"

static int16_t max_temperature = 0;
static int16_t min_temperature = 0;
static uint16_t max_humidity = 0;
static uint16_t min_humidity = 0;
static uint16_t max_co2 = 0;
static uint16_t min_co2 = 0;
static uint8_t system_status = 0;


void setConfiguration(lora_driver_payload_t payload){
	int16_t newMaxTemp = 0;
	int16_t newMinTemp = 0;
	uint16_t newMaxHum = 0;
	uint16_t newMinHum = 0;
	uint16_t newMaxCO2 = 0;
	uint16_t newMinCO2 = 0;
	
	newMaxTemp = (payload.bytes[0] << 8 | payload.bytes[1]);
	newMinTemp = (payload.bytes[2] << 8 | payload.bytes[3]);
	newMaxHum = (payload.bytes[4] << 8 | payload.bytes[5]);
	newMinHum = (payload.bytes[6] << 8 | payload.bytes[7]);
	newMaxCO2 = (payload.bytes[8] << 8 | payload.bytes[9]);
	newMinCO2 =(payload.bytes[10] << 8 | payload.bytes[11]);
	
	set_max_temperature(newMaxTemp/10);
	set_min_temperature(newMinTemp/10);
	set_max_humidity(newMaxHum/10);
	set_min_humidity(newMinHum/10);
	set_max_co2(newMaxCO2);
	set_min_co2(newMinCO2);
	
	printf("CONF MIN/MAX, tmp: %d/%d, hum: %d/%d, co2: %d/%d\n", newMaxTemp/10, newMinTemp/10, newMaxHum/10, newMinHum/10, newMaxCO2, newMinCO2);
}

void set_system_status(system_status_code_t statusCode){
	if (statusCode >= 0xF7){
		system_status &= statusCode;
	}
	else{
		system_status |= statusCode;
	}
}

uint8_t get_system_status(){
	return system_status;
}


int16_t get_max_temperature(){
	return max_temperature;
}

void set_max_temperature(int16_t maxTemp){
	max_temperature = maxTemp;
}

void set_min_temperature(int16_t minTemp){
	min_temperature = minTemp;
}

uint16_t get_max_humidity(){
	return max_humidity;
}

void set_max_humidity(uint16_t maxHum){
	max_humidity = maxHum;
}

void set_min_humidity(uint16_t minHum){
	min_humidity = minHum;
}

uint16_t get_max_co2(){
	return max_co2;
}

void set_max_co2(uint16_t maxCO2){
	max_co2 = maxCO2;
}

void set_min_co2(uint16_t minCO2){
	min_co2 = minCO2;
}