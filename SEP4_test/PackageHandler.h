/*
 * PackageHandler.h
 *
 * Created: 16/11/2022 09.48.46
 *  Author: jurin
 */ 

#include "lora_driver.h"

#define PAYLOAD_SIZE 7

#ifndef PACKAGEHANDLER_H_
#define PACKAGEHANDLER_H_

void set_temperature_percent(int16_t temperature);
void set_humidity_percent(uint16_t humidity);
void set_CO2_ppm(uint16_t co2ppm);
lora_driver_payload_t get_lora_package(uint8_t port);


#endif /* PACKAGEHANDLER_H_ */