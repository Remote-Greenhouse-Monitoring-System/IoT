/*
 * SystemSetup.h
 *
 *  Github: https://github.com/Remote-Greenhouse-Monitoring-System/IoT
 *  Author: Christopher, Himal, Juraj
 */

#pragma once


#include <lora_driver.h>
#include <ATMEGA_FreeRTOS.h>
#include <event_groups.h>
#include <message_buffer.h>
#include <semphr.h>
#include <stdio.h>

#define CO2_MEASURE_BIT (1<<0)
#define CO2_READY_BIT (1<<1)
#define TEMP_HUM_MEASURE_BIT (1<<2)
#define TEMP_HUM_READY_BIT (1<<3)
#define LIGHT_MEASURE_BIT (1<<4)
#define LIGHT_READY_BIT (1<<5)

#define ALL_READY_BITS (CO2_READY_BIT | TEMP_HUM_READY_BIT | LIGHT_READY_BIT)
#define ALL_MEASURE_BITS ( CO2_MEASURE_BIT | TEMP_HUM_MEASURE_BIT | LIGHT_MEASURE_BIT)

extern EventGroupHandle_t measureEventGroup;
extern EventGroupHandle_t dataReadyEventGroup;
extern MessageBufferHandle_t uplinkMessageBufferHandle;
extern MessageBufferHandle_t downlinkMessageBufferHandle;
extern SemaphoreHandle_t configSemaphore;

void initialize_event_groups();
void initialize_message_buffers();
void initialize_semaphore();


