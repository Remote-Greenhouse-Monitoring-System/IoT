/*
 * DownlinkHandler.h
 *
 * Created: 07/12/2022 22.34.23
 *  Author: jurin
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

void create_lora_downlink_handler_task(UBaseType_t priority);


