/*
 * actionsController.h
 *  Github: https://github.com/Remote-Greenhouse-Monitoring-System/IoT
 *  Author: Christopher, Himal, Juraj
 */

#pragma once


#include <stdint.h>
#include <ATMEGA_FreeRTOS.h>
#include <avr/io.h>
#include <event_groups.h>
#include "Sensors/tempHumSensor.h"
#include "Sensors/lightSensor.h"
#include "Sensors/co2Sensor.h"
#include "configuration.h"
#include "servoController.h"

void create_actions_controller_task(UBaseType_t priority);



