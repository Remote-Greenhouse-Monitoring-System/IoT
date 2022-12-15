/*
 * TempHumSensor.h
 *
 *  Github: https://github.com/Remote-Greenhouse-Monitoring-System/IoT
 *  Author: Christopher, Himal, Juraj
 */
#pragma once

#include <ATMEGA_FreeRTOS.h>
#include <stdio.h>
#include <stdint.h>
#include <hih8120.h>
#include <task.h>
#include <event_groups.h>
#include <string.h>
#include "../initialize.h"


void create_TempHum_sensor_task(UBaseType_t priority);
int16_t TempHumSensor_getTemp();
uint16_t TempHumSensor_getHum();
void measure_Temp_Hum();


