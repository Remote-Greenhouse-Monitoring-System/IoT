/*
 * DownlinkHandler.h
 *
 *  Github: https://github.com/Remote-Greenhouse-Monitoring-System/IoT
 *  Author: Christopher, Himal, Juraj
 */

#pragma once
#include <ATMEGA_FreeRTOS.h>
#include <lora_driver.h>
#include <stdio.h>
#include <stdint.h>
#include <message_buffer.h>
#include <task.h>
#include "initialize.h"
#include "configuration.h"

void create_lora_downlink_handler_task(UBaseType_t priority);


