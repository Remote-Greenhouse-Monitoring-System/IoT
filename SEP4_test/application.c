/*
 * Application.c
 *
 *  Github: https://github.com/Remote-Greenhouse-Monitoring-System/IoT
 *  Author: Christopher, Himal, Juraj
 */

#include "application.h"




void main_application_task(void *pvParameters);

void create_main_application_task(UBaseType_t priority){
		
	xTaskCreate(
	main_application_task
	,  "MainApplication"  
	,  configMINIMAL_STACK_SIZE  
	,  NULL
	,  tskIDLE_PRIORITY + priority 
	,  NULL );
	
}



void main_application_task(void *pvParameters) {
	
	uint8_t xBytesSent = 0;
	//5 minute timer
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = pdMS_TO_TICKS(300000UL); // Upload message every 5 minutes (300000 ms)
	xLastWakeTime = xTaskGetTickCount();
	
	for (;;)
	{
		//Run every 5 minutes 
		xTaskDelayUntil( &xLastWakeTime, xFrequency );
		
		//First trying to measure everything
		xEventGroupSetBits(measureEventGroup, ALL_MEASURE_BITS);
		
		//Wait for measurements to be done 		
		EventBits_t uxBits = xEventGroupWaitBits(dataReadyEventGroup,ALL_READY_BITS,pdTRUE,pdTRUE,portMAX_DELAY);
		
		//If everything is done now we need to set the measurement and it's done
		
		if (uxBits&(ALL_READY_BITS))
		{
			set_temperature_percent(TempHumSensor_getTemp());
			set_humidity_percent(TempHumSensor_getHum());
			set_CO2_ppm(CO2_getPPM());
			set_light_lux(light_sensor_get_lux());
			
			if(xSemaphoreTake(configSemaphore, (TickType_t) 10 ) == pdTRUE){
				set_status(get_system_status());
				xSemaphoreGive(configSemaphore);
			}
			
			lora_driver_payload_t payload = get_lora_package(2);
			
			xBytesSent = xMessageBufferSend(uplinkMessageBufferHandle,
			&payload,
			sizeof(payload),
			portMAX_DELAY);
			if(xBytesSent != sizeof(payload)){
				printf("Timed out.\n");
			}
			else{
			//	printf("Bytes put in buffer: %d\n", xBytesSent);
			}
		}	
	}
}