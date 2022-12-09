/*
 * FanController.h
 *
 * Created: 06/12/2022 22.55.32
 *  Author: jurin, Christopher
 */ 

#pragma once


#include <stdint.h>
#include <ATMEGA_FreeRTOS.h>
#include <avr/io.h>
#include "../Sensors/TempHumSensor.h"
#include "Application.h"
#include "Configuration.h"
#include "FanController.h"

void fanController_create(UBaseType_t priority);



