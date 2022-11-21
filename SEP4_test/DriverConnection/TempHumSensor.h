/*
 * TempHumSensor.h
 *
 * Created: 11/20/2022 3:18:53 PM
 *  Author: himal
 */ 
#pragma once
#include "ATMEGA_FreeRTOS.h"
#include <stdio.h>

#include <stdint.h>
#include <hih8120.h>
#include <task.h>



void create_TempHumSensorTask();
uint16_t TempHumSensor_getTemp();
uint16_t TempHumSensor_getHum();
void Temp_Hum_Main_Task();
