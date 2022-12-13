#pragma once


#include <stdint.h>
#include "../Testing/FreeRTOS.h"
//#include <avr/io.h>
#include "../TestFiles/TempHumSensor.h"
#include "application.h"
#include "configuration.h"
#include "servoController.h"

void create_fan_controller_task(UBaseType_t priority);
void fan_controller_task_run();
void fan_controller_task_init();


