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


void initialize_light_sensor();
void create_light_sensor_task(UBaseType_t priority);
float light_sensor_get_lux();