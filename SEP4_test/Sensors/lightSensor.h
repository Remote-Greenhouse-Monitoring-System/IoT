/*
 * lightSensor.h
 *
 *  Github: https://github.com/Remote-Greenhouse-Monitoring-System/IoT
 *  Author: Christopher, Himal, Juraj
 */

#pragma once

#include <ATMEGA_FreeRTOS.h>
#include <stdio.h>
#include <stdint.h>
#include <tsl2591.h>
#include <task.h>
#include <event_groups.h>
#include "../initialize.h"

void create_light_sensor_task(UBaseType_t priority);
float light_sensor_get_lux();