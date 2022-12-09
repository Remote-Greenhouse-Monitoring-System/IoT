/*
 * FanController.c
 *
 * Created: 06/12/2022 21.18.14
 *  Author: jurin, Christopher
 */ 

#include "FanController.h"

void fanController_create(UBaseType_t priority)
{
	fanController_createTask(priority);
		DDRA = 0xFF;
		PORTA = 0xFF;
}

void fanController_createTask(UBaseType_t priority){
	xTaskCreate(
	fanController_task()
	,  "FanController"
	,  configMINIMAL_STACK_SIZE
	,  NULL
	,  tskIDLE_PRIORITY + priority
	,  NULL );
}

void fanController_task(void *pvParameters) {
	
	int16_t currentTemperature = 0;
	uint16_t currentHumidity = 0;
	int16_t thresholdTemperature = 0;
	uint16_t thresholdHumidity = 0;
	
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = pdMS_TO_TICKS(120000); 
	xLastWakeTime = xTaskGetTickCount();
	
	for(;;)
	{
		xTaskDelayUntil( &xLastWakeTime, xFrequency );
		thresholdTemperature = configuration_getMaxTemperature();
		thresholdHumidity = configuration_getMaxHumidity();
		
		tempHumSensor_measure();
		currentTemperature = tempHumSensor_getTemp();
		currentHumidity = tempHumSensor_getHum;
		
		printf("--->Fan Controller checked temp: %d threshold: %d<---\n", currentTemperature/10, thresholdTemperature);
		printf("--->Fan Controller checked hum: %d threshold: %d<---\n", currentTemperature/10, thresholdHumidity);
		if(currentTemperature/10 > thresholdTemperature){
			PORTA = 0x00;
		}
		else{
			PORTA = 0xFF;
		}
	}
}