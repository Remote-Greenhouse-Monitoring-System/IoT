/*
* fanController.c
*  Git: https://github.com/Remote-Greenhouse-Monitoring-System/IoT
*  Authors: Christopher, Himal, Jurin
*/

#include <stdint.h>
#include <ATMEGA_FreeRTOS.h>
#include <avr/io.h>
#include <stdio.h>

#include "../Sensors/tempHumSensor.h"
#include "application.h"
#include "configuration.h"
#include "servoController.h"
#include "windowController.h"

void windowController_task(void *pvParameters);
void windowController_createTask(UBaseType_t priority);

void windowController_create(UBaseType_t priority)
{
	windowController_createTask(priority);
	DDRA = 0xFF;
	PORTA = 0xFF;
}

void windowController_createTask(UBaseType_t priority){
	xTaskCreate(
	windowController_task
	,  "windowController"
	,  configMINIMAL_STACK_SIZE
	,  NULL
	,  tskIDLE_PRIORITY + priority
	,  NULL );
}

void windowController_task(void *pvParameters) {
	
	int16_t currentTemperature = 0;
	uint16_t currentHumidity = 0;
	int16_t thresholdTemperature = 0;
	uint16_t thresholdHumidity = 0;
	
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = pdMS_TO_TICKS(5000);
	xLastWakeTime = xTaskGetTickCount();
	
	for(;;)
	{
		xTaskDelayUntil( &xLastWakeTime, xFrequency );
		thresholdTemperature = configuration_getMaxTemperature();
		thresholdHumidity = configuration_getMaxHumidity();
		
		tempHumSensor_measure();
		currentTemperature = tempHumSensor_getTemp();
		currentHumidity = tempHumSensor_getHum();
		
		printf("windowController.c ---> Checked temp: %d threshold: %d \n", currentTemperature/10, thresholdTemperature);
		printf("windowController.c ---> Checked hum: %d threshold: %d \n", currentHumidity/10, thresholdHumidity);
	if(currentTemperature/10 > thresholdTemperature){
		// 			PORTA = 0x00;
		servoController_setPosition(0, 100);
	}
	else{
		// 			PORTA = 0xFF;
		servoController_setPosition(0, -100);
	}
	}
}