/*
* application.c
*  Git: https://github.com/Remote-Greenhouse-Monitoring-System/IoT
*  Authors: Christopher, Himal, Jurin
*/

#include "ATMEGA_FreeRTOS.h"
#include "stdio.h"
#include "event_groups.h"
#include "task.h"
#include "message_buffer.h"
#include "lora_driver.h"

#include "Sensors/co2Sensor.h"
#include "Sensors/tempHumSensor.h"
#include "packageHandler.h"
#include "initialize.h"

#include "application.h"

void application_task(void *pvParameters);

void application_create(UBaseType_t priority)
{
	application_craeteTask(priority);
}

void application_craeteTask(UBaseType_t priority){
	xTaskCreate(
	application_task
	,  "MainApplication"
	,  configMINIMAL_STACK_SIZE
	,  NULL
	,  tskIDLE_PRIORITY + priority
	,  NULL );
}

// Main task For application to get result when every measurement is done
void application_task(void *pvParameters) {
	
	uint8_t xBytesSent = 0;
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
			packageHandler_setTemperaturePercent(tempHumSensor_getTemp());
			packageHandler_setHumidityPercent(tempHumSensor_getHum());
			packageHandler_setCO2ppm(co2Sensor_getPPM());
			lora_driver_payload_t payload = packageHandler_getLoraPackage(2);
			
			xBytesSent = xMessageBufferSend(uplinkMessageBufferHandle,
			&payload,
			sizeof(payload),
			portMAX_DELAY);
			if(xBytesSent != sizeof(payload)){
				printf("application.c ---> Timed out.\n");
			}
			else{
				
				// 			printf("Bytes sent: %d\n", xBytesSent);
				// 			printf("Temp sent: %d\n", tem);
				// 			printf("Humidity sent: %d\n", hum);
				// 			printf("Size of payload: %d\n", sizeof(payload));
				//			receivePayload();
				printf("application.c ---> Bytes put in buffer: %d\n", xBytesSent);
				
			}
		}
	}
}

