/*
 * DownlinkHandler.h
 *
 * Created: 07/12/2022 22.34.23
 *  Author: jurin, Christopher
 */ 

#pragma once
#include <ATMEGA_FreeRTOS.h>
#include <lora_driver.h>
#include <stdio.h>
#include <stdint.h>
#include <message_buffer.h>
#include <task.h>
#include "Initialize.h"
#include "Configuration.h"

void downlinkHandler_create(UBaseType_t priority);


