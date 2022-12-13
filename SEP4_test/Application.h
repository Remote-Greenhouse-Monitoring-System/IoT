#pragma once

#include <ATMEGA_FreeRTOS.h>
#include <stdio.h>
#include <event_groups.h>
#include <task.h>
#include <message_buffer.h>
#include <lora_driver.h>

#include "Sensors/co2Sensor.h"
#include "Sensors/tempHumSensor.h"
#include "Sensors/lightSensor.h"
#include "packageHandler.h"
#include "initialize.h"
#include "configuration.h"


void create_main_application_task(UBaseType_t priority);

