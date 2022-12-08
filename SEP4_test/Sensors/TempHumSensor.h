/*
 * TempHumSensor.h
 *
 * Created: 11/20/2022 3:18:53 PM
 *  Author: himal
 */ 
#pragma once
#include "../../GreenHouse_FreeRTOS_Test/FreeRTOS/FreeRTOS.h"
#include <stdio.h>

#include <stdint.h>
#include <../drivers/hih8120.h>
#include <../../GreenHouse_FreeRTOS_Test/FreeRTOS/task.h>



void create_TempHumSensorTask();
int16_t TempHumSensor_getTemp();
uint16_t TempHumSensor_getHum();
void Temp_Hum_Main_Task();
