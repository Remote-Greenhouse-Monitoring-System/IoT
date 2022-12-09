/*
 * ConfigurationImpl.c
 *
 * Created: 06/12/2022 18.45.41
 *  Author: jurin
 */ 


#include "Configuration.h"

static int16_t max_temperature = 23;
static int16_t min_temperature = 0;
static uint16_t max_humidity = 0;
static uint16_t min_humidity = 0;

int16_t get_max_temperature(){
	return max_temperature;
}

uint16_t get_max_humidity(){
	return max_humidity;
}

void set_max_temperature(int16_t maxTemp){
	max_temperature = maxTemp;
}
void set_max_humidity(uint16_t maxHum){
	max_humidity = maxHum;
}


void setConfiguration(lora_driver_payload_t payload){
	int16_t newMaxTemp = 0;
	uint16_t newMaxHum = 0;
	newMaxTemp = (payload.bytes[0] << 8 | payload.bytes[1]);
	newMaxHum = (payload.bytes[2] << 8 | payload.bytes[3]);
	set_max_temperature(newMaxTemp);
	set_max_humidity(newMaxHum);
	printf("New config, max temp: %d, max hum: %d\n", newMaxTemp, newMaxHum);
}