#pragma once

#include <stdint.h>
#include <stdio.h>

#include <../Testing/FreeRTOS.h>
#include <../Testing/event_groups.h>
#include "../Testing/task.h"

#include "mh_z19.h"

#include "Initialize.h"

void createCO2SensorTask();
void CO2_measure();
void CO2_createSensor();
void MeasureCo2Task(void* pvpParameter);
uint16_t CO2_getPPM();
void myCo2CallBack(uint16_t ppm_parameter);