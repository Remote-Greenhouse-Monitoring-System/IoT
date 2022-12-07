/*
 * Application.c
 *
 * Created: 11/20/2022 2:27:49 PM
 *  Author: himal
 
 */ 
#include <stdio.h>
#include <avr/io.h>

#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <message_buffer.h>
#include <stream_buffer.h>
#include <stdio_driver.h>
#include <serial.h>
#include <string.h>

#include <lora_driver.h>
#include <status_leds.h>

#include "Application.h"
#include "LoraUtils.h"
#include "PackageHandler.h"
#include "Configuration.h"
#include "FanController.h"


EventGroupHandle_t measureEventGroup;
EventGroupHandle_t dataReadyEventGroup;

MessageBufferHandle_t uplinkBufferHandle;

void main_application_task(void *pvParameters);

void initialize_application(){
	initialize_event_groups();
	create_sensor_tasks();
	initialize_fan_controller();
	uplinkBufferHandle = xMessageBufferCreate(100);
	setUplinkMessageBufferHandle(uplinkBufferHandle);
	
	xTaskCreate(
	main_application_task
	,  "MainApplication"  
	,  configMINIMAL_STACK_SIZE  
	,  NULL
	,  3  
	,  NULL );
	
}

void create_sensor_tasks() {
	createCO2SensorTask();
	create_TempHumSensorTask();
}

void initialize_event_groups() {
	dataReadyEventGroup = xEventGroupCreate();
	measureEventGroup = xEventGroupCreate();
}


// Main task For application to get result when every measurnment is done

void main_application_task(void *pvParameters) {
	
	uint8_t xBytesSent = 0;
	const TickType_t x100ms = pdMS_TO_TICKS(100);
	//5 minute timer
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = pdMS_TO_TICKS(300000UL); // Upload message every 5 minutes (300000 ms)
	xLastWakeTime = xTaskGetTickCount();
	
	for (;;)
	{
		xTaskDelayUntil( &xLastWakeTime, xFrequency );
		
		//First trying to measure everything
		xEventGroupSetBits(measureEventGroup, ALL_MEASURE_BITS);
		
		//printf("Measuring from sensor is done now ready bit are done ");
		
		EventBits_t uxBits = xEventGroupWaitBits(dataReadyEventGroup,ALL_READY_BITS,pdTRUE,pdTRUE,portMAX_DELAY);
		
		//If everything is done now we need to set the measurement and it's done
		
		if (uxBits&(ALL_READY_BITS))
		{
			set_temperature_percent(TempHumSensor_getTemp());
			set_humidity_percent(TempHumSensor_getHum());
			set_CO2_ppm(CO2_getPPM());
			lora_driver_payload_t payload = get_lora_package(2);
			
			xBytesSent = xMessageBufferSend(uplinkBufferHandle,
			&payload,
			sizeof(payload),
			x100ms);
			if(xBytesSent != sizeof(payload)){
				printf("Timed out.\n");
			}
			else{
				
				// 			printf("Bytes sent: %d\n", xBytesSent);
				// 			printf("Temp sent: %d\n", tem);
				// 			printf("Humidity sent: %d\n", hum);
				// 			printf("Size of payload: %d\n", sizeof(payload));
				//			receivePayload();
				printf("Bytes put in buffer: %d\n", xBytesSent);
				
			}
		}	
	}
}