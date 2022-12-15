/*
 * UplinkHandler.h
 *  Github: https://github.com/Remote-Greenhouse-Monitoring-System/IoT
 *  Author: Christopher, Himal, Juraj
 */

#pragma once


#include <stddef.h>
#include <stdio.h>
#include <ATMEGA_FreeRTOS.h>
#include <lora_driver.h>
#include <status_leds.h>
#include "initialize.h"

#define LORA_appEUI "9276B3CF3B069355"
#define LORA_appKEY "84860CBA5C5116F9EC56E1B4346CA899"

void create_lora_uplink_handler_task(UBaseType_t priority);








