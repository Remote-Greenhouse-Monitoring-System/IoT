/*
* co2Sensor.h
*  Git: https://github.com/Remote-Greenhouse-Monitoring-System/IoT
*  Authors: Christopher, Himal, Jurin
*/

#pragma once
#include <stdint.h>

void co2Sensor_create(UBaseType_t priority);
uint16_t co2Sensor_getPPM();
