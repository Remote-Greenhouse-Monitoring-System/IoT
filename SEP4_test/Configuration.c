/*
 * ConfigurationImpl.c
 *
 * Created: 06/12/2022 18.45.41
 *  Author: jurin, Christopher
 */ 


#include "Configuration.h"

static int16_t max_temperature = 0;
static int16_t min_temperature = 0;
static uint16_t max_humidity = 0;
static uint16_t min_humidity = 0;

int16_t configuration_getMaxTemperature(){
	return max_temperature;
}

uint16_t configuration_getMaxHumidity(){
	return max_humidity;
}

void configuration_setMaxTemperature(int16_t maxTemp){
	max_temperature = maxTemp;
}
void configuration_setMaxHumidity(uint16_t maxHum){
	max_humidity = maxHum;
}


void configuration_setConfiguration(lora_driver_payload_t payload){
	int16_t newMaxTemp = 0;
	uint16_t newMaxHum = 0;
	newMaxTemp = (payload.bytes[0] << 8 | payload.bytes[1]);
	newMaxHum = (payload.bytes[2] << 8 | payload.bytes[3]);
	configuration_setMaxTemperature(newMaxTemp);
	configuration_setMaxHumidity(newMaxHum);
	printf("--->New config, max temp: %d, max hum: %d\n<---", newMaxTemp, newMaxHum);
}