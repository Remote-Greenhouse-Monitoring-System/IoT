#pragma once

#include "../Testing/FreeRTOS.h"
#include <stdio.h>
#include <stdint.h>
#include "hih8120.h"
#include "../Testing/task.h"
#include "../Testing/event_groups.h"
#include <string.h>
#include "initialize.h"

void create_TempHum_sensor_task(UBaseType_t priority);
int16_t TempHumSensor_getTemp();
uint16_t TempHumSensor_getHum();
void measure_Temp_Hum();
void initialise_TempHumSensor();
void Temp_Hum_Main_Task();