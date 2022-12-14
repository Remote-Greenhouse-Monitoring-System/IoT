/*
 * FanController.h
 *
 * Created: 06/12/2022 22.55.32
 *  Author: jurin 
 
 */ 

#pragma once


#include <stdint.h>
#include <ATMEGA_FreeRTOS.h>
#include <avr/io.h>
#include <event_groups.h>
#include "Sensors/tempHumSensor.h"
#include "Sensors/lightSensor.h"
#include "Sensors/co2Sensor.h"
#include "application.h"
#include "configuration.h"
#include "servoController.h"

void create_actions_controller_task(UBaseType_t priority);



