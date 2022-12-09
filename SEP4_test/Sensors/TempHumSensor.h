/*
 * TempHumSensor.h
 *
 * Created: 11/20/2022 3:18:53 PM
 *  Author: himal, Christopher
 */ 
#pragma once

#include <ATMEGA_FreeRTOS.h>
#include <stdio.h>
#include <stdint.h>
#include <hih8120.h>
#include <task.h>
#include <event_groups.h>
#include <string.h>
#include "../Initialize.h"


void tempHumSensor_create(UBaseType_t priority);
int16_t tempHumSensor_getTemp();
uint16_t tempHumSensor_getHum();
void tempHumSensor_measure();


