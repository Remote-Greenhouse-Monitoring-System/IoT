/*
 * CO2Sensor.h
 *
 * Created: 11/20/2022 2:39:35 PM
 *  Author: himal
 */ 

#pragma once

#include <ATMEGA_FreeRTOS.h>
#include <stdio.h>
#include <stdint.h>
#include <task.h>
#include <mh_z19.h>
#include <event_groups.h>
#include "../Application.h"
#include "../Initialize.h"

void create_CO2_sensor_task(UBaseType_t priority);
void CO2_measure();
uint16_t CO2_getPPM();
void myCo2CallBack(uint16_t ppm_parameter);
