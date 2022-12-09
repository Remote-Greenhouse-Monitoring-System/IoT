/*
* tempHumSensor.h
*  Git: https://github.com/Remote-Greenhouse-Monitoring-System/IoT
*  Authors: Christopher, Himal, Jurin
*/
#pragma once

void tempHumSensor_create(UBaseType_t priority);
int16_t tempHumSensor_getTemp();
uint16_t tempHumSensor_getHum();
void tempHumSensor_measure();


