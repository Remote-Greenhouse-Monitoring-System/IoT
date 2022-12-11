/*
 * FanController.c
 *
 * Created: 06/12/2022 21.18.14
 *  Author: jurin
 */ 

#include "FanController.h"



void fan_controller_task(void *pvParameters);

void create_fan_controller_task(UBaseType_t priority){
	
	DDRA = 0xFF;
	PORTA = 0xFF;
	
	xTaskCreate(
	fan_controller_task
	,  "FanController"
	,  configMINIMAL_STACK_SIZE
	,  NULL
	,  tskIDLE_PRIORITY + priority
	,  NULL );
}

void fan_controller_task(void *pvParameters) {
	
	int16_t currentTemperature = 0;
	int16_t thresholdTemperature = 0;
	
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = pdMS_TO_TICKS(120000); 
	xLastWakeTime = xTaskGetTickCount();
	
	for(;;)
	{
		xTaskDelayUntil( &xLastWakeTime, xFrequency );
		

		if(xSemaphoreTake(configSemaphore, (TickType_t) 10 ) == pdTRUE){
			thresholdTemperature = get_max_temperature();
			xSemaphoreGive(configSemaphore);
			}
			
		measure_Temp_Hum();
		currentTemperature = TempHumSensor_getTemp();
		
		printf("Current temp: %d\n", currentTemperature/10);
		printf("Threshold temp: %d\n", thresholdTemperature);
		if(currentTemperature/10 > thresholdTemperature){
			servo_set_position(0, 100);
			if(xSemaphoreTake(configSemaphore, (TickType_t) 10 ) == pdTRUE){
				set_system_status(TEMPERATURE_ACTION_ON);
				xSemaphoreGive(configSemaphore);
			}
		}
		else{
			servo_set_position(0, -100);
			if(xSemaphoreTake(configSemaphore, (TickType_t) 10 ) == pdTRUE){
				set_system_status(TEMPERATURE_ACTION_OFF);
				xSemaphoreGive(configSemaphore);
			}
		}
	}
}