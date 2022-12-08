/*
 * CO2Sensor.h
 *
 * Created: 11/20/2022 2:39:35 PM
 *  Author: himal
 */ 

#pragma once

#include <stdio.h>
#include <stdint.h>


void CO2_createSensor();
void createCO2SensorTask();
void CO2_measure();

void MeasureCo2Task(void* pvpParameter);
uint16_t CO2_getPPM();
void myCo2CallBack(uint16_t ppm_parameter);
