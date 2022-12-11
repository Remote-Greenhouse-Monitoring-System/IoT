#pragma once

#include <ATMEGA_FreeRTOS.h>
#include <stdio.h>
#include <event_groups.h>
#include <task.h>
#include <message_buffer.h>
#include <lora_driver.h>

#include "Sensors/CO2Sensor.h"
#include "Sensors/TempHumSensor.h"
#include "PackageHandler.h"
#include "Initialize.h"
#include "Configuration.h"


void create_main_application_task(UBaseType_t priority);

