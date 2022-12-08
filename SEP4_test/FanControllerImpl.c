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
	uint16_t currentHumidity = 0;
	int16_t thresholdTemperature = 0;
	uint16_t thresholdHumidity = 0;
	
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = pdMS_TO_TICKS(120000); 
	xLastWakeTime = xTaskGetTickCount();
	
	for(;;)
	{
		xTaskDelayUntil( &xLastWakeTime, xFrequency );
		thresholdTemperature = get_max_temperature();
		
		measure_Temp_Hum();
		currentTemperature = TempHumSensor_getTemp();
		currentHumidity = TempHumSensor_getHum();
		
		printf("Current temp: %d\n", currentTemperature/10);
		printf("Threshold temp: %d\n", thresholdTemperature);
		if(currentTemperature/10 > thresholdTemperature){
			PORTA = 0x00;
		}
		else{
			PORTA = 0xFF;
		}
	}
}