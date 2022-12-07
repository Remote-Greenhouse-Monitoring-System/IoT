#pragma once

#include <../Testing/FreeRTOS.h>
#include <../Testing/event_groups.h>

#define CO2_MEASURE_BIT (1<<0)
#define CO2_READY_BIT (1<<1)
#define TEMP_HUM_MEASURE_BIT (1<<2)
#define TEMP_HUM_READY_BIT (1<<3)
#define ALL_READY_BITS (CO2_READY_BIT | TEMP_HUM_READY_BIT)
#define ALL_MEASURE_BITS ( CO2_MEASURE_BIT | TEMP_HUM_MEASURE_BIT  )

extern  EventGroupHandle_t measureEventGroup;
extern EventGroupHandle_t dataReadyEventGroup;

void initialize_event_groups();