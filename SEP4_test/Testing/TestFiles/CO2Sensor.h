#pragma once

#include <stdint.h>
#include <stdio.h>

#include <../Testing/FreeRTOS.h>
#include <../Testing/event_groups.h>
#include "../Testing/task.h"

#include "mh_z19.h"

#include "Initialize.h"

void CO2_createSensor();
void myCo2CallBack(uint16_t ppm_parameter);
void CO2_measure();
void create_CO2_sensor_task(UBaseType_t priority);
void MeasureCo2Task();
uint16_t CO2_getPPM();
void RunMeasureCo2Task();