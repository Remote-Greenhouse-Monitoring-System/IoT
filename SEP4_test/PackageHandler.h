/*
 * PackageHandler.h
 *
 * Created: 16/11/2022 09.48.46
 *  Author: jurin
 */ 

#include "lora_driver.h"

#define PAYLOAD_SIZE 4

#ifndef PACKAGEHANDLER_H_
#define PACKAGEHANDLER_H_

void setTemperaturePercent(int16_t temperature);
void setHumidityPercent(int16_t humidity);
lora_driver_payload_t getLoraPackage(uint8_t port);


#endif /* PACKAGEHANDLER_H_ */