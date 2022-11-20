/*
 * CO2Sensor.h
 *
 * Created: 11/20/2022 2:39:35 PM
 *  Author: himal
 */ 

#pragma once

#include<stdint.h>
#include <task.h>
#include <mh_z19.h>


void createCO2SensorTask();
void CO2_measure();

uint16_t CO2_getPPM();
