/*
 * TempHumSensor.h
 *
 * Created: 11/20/2022 3:18:53 PM
 *  Author: himal
 */ 
#pragma once

#include <stdint.h>
#include <stdio.h>

#include <../Testing/FreeRTOS.h>
#include <../Testing/event_groups.h>
#include "../Testing/task.h"

#include "hih8120.h"

#include "Initialize.h"

void create_TempHum_sensor_task(UBaseType_t priority);
int16_t TempHumSensor_getTemp();
uint16_t TempHumSensor_getHum();
void Temp_Hum_Main_Task();
void measure_Temp_Hum();
void initialise_TempHumSensor();
int16_t TempHumSensor_getTemp();
uint16_t TempHumSensor_getHum();