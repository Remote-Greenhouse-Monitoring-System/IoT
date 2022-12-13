#pragma once
#include "../Testing/FreeRTOS.h"
#include "lora_driver.h"
#include <stdio.h>
#include <stdint.h>
#include "../Testing/message_buffer.h"
#include "../Testing/task.h"
#include "initialize.h"
#include "configuration.h"

void create_lora_downlink_handler_task(UBaseType_t priority);
void lora_downlink_handler_task_run();