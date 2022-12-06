/*
 * ConfigurationImpl.c
 *
 * Created: 06/12/2022 18.45.41
 *  Author: jurin
 */ 


#include "Configuration.h"
#include <stdint.h>

static int16_t max_temperature = 25;
static int16_t min_temperature;
static uint16_t max_humidity;
static uint16_t min_humidity;

int16_t get_max_temperature(){
	return max_temperature;
}
int16_t get_min_temperature(){
	return min_temperature;
}
uint16_t get_max_humidity(){
	return max_humidity;
}
uint16_t get_min_humidity(){
	return min_humidity;
}