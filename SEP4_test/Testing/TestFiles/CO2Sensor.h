#pragma once

#include <stdint.h>
#include <stdio.h>

#include <../Testing/FreeRTOS.h>
#include <../Testing/event_groups.h>

#include "Initialize.h"

uint16_t CO2_getPPM();
void MeasureCo2Task();
void createCO2SensorTask();