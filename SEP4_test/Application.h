#pragma once

#include "DriverConnection/CO2Sensor.h"
#include "DriverConnection/TempHumSensor.h"
#include "event_groups.h"
#include "ATMEGA_FreeRTOS.h"



#define CO2_MEASSURE_BIT (1<<0)
#define CO2_READY_BIT (1<<1)
#define TEMP_HUM_MEASSURE_BIT (1<<2)
#define TEMP_HUM_READY_BIT (1<<3)

#define ALL_READY_BITS( CO2_READY_BIT | TEMP_HUM_READY_BIT);
#define ALL_MEASSURE_BITS( TEMP_HUM_MEASSURE_BIT |  CO2_MEASSURE_BIT );

extern EventGroupHandle_t meassureEventGroup;
extern EventGroupHandle_t dataReadyEventGroup;


//typedef struct application* application_t;

void run_all_Task();
void initialize_everything();

void start_application();

