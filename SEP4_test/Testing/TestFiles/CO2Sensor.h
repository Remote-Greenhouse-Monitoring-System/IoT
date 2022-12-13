#pragma once

#include "../Testing/FreeRTOS.h"
#include <stdio.h>
#include <stdint.h>
#include "../Testing/task.h"
#include "mh_z19.h"
#include "../Testing/event_groups.h"
#include "application.h"
#include "initialize.h"

void create_CO2_sensor_task(UBaseType_t priority);
void CO2_measure();
uint16_t CO2_getPPM();
void myCo2CallBack(uint16_t ppm_parameter);
void CO2_createSensor();
void MeasureCo2Task();