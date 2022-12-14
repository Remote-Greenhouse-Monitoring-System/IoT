/*
 * lightSensor.h
 *
 * Created: 12/12/2022 17.57.47
 *  Author: jurin
 */ 

#pragma once

#include "../Testing/FreeRTOS.h"
#include <stdio.h>
#include <stdint.h>
#include "../TestFiles/tsl2591.h"
#include "../Testing/task.h"
#include "../Testing/event_groups.h"
#include "initialize.h"

void tsl2591Callback(tsl2591_returnCode_t returnCode);
void initialize_light_sensor();
void create_light_sensor_task(UBaseType_t priority);
void measure_light_task_inline();
float light_sensor_get_lux();