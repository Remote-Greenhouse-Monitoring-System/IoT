#pragma once

#include "../Testing/FreeRTOS.h"
#include <stdio.h>
#include "../Testing/event_groups.h"
#include "../Testing/task.h"
#include "../Testing/message_buffer.h"
#include "../TestFiles/lora_driver.h"

#include "../TestFiles/CO2Sensor.h"
#include "../TestFiles/lightSensor.h"

#include "../TestFiles/TempHumSensor.h"
#include "../TestFiles/packageHandler.h"
#include "../TestFiles/initialize.h"
#include "../TestFiles/configuration.h"


void create_main_application_task(UBaseType_t priority);
void main_application_task_init();
void main_application_task_run();