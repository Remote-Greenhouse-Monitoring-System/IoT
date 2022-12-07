
#include <stdio.h>
#include <avr/io.h>

#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <message_buffer.h>
#include "PackageHandler.h"
#include "Application.h"

#include <stdio_driver.h>
#include <serial.h>
#include <string.h>

 // Needed for LoRaWAN
#include <lora_driver.h>
#include <status_leds.h>





// Prototype for LoRaWAN handler
void lora_handler_initialise(UBaseType_t lora_handler_task_priority);


/*-----------------------------------------------------------*/
void initializeSystem()
{
	// Set output ports for leds used in the example
	DDRA |= _BV(DDA0) | _BV(DDA7);

	// Make it possible to use stdio on COM port 0 (USB) on Arduino board - Setting 57600,8,N,1
	stdio_initialise(ser_USART0);


	// vvvvvvvvvvvvvvvvv BELOW IS LoRaWAN initialisation vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
	// Status Leds driver
	status_leds_initialise(5); // Priority 5 for internal task
	// Initialise the LoRaWAN driver without down-link buffer
	lora_driver_initialise(1, NULL);
	// Create LoRaWAN task and start it up with priority 3
	lora_handler_initialise(3);
	
	initialize_application();
		
}

/*-----------------------------------------------------------*/
int main(void)
{
	initializeSystem(); // Must be done as the very first thing!!
	printf("Program Started!!\n");
	vTaskStartScheduler(); // Initialise and run the freeRTOS scheduler. Execution should never return from here.

	/* Replace with your application code */
	while (1)
	{
	}
}



/*-----------------------------------------------------------*/

// void create_tasks_and_semaphores(void)
// {
// 
// 	
// 
// 	xTaskCreate(
// 	temp_sensor_task
// 	,  "HIH8120_task"  // A name just for humans
// 	,  configMINIMAL_STACK_SIZE  // This stack size can be checked & adjusted by reading the Stack Highwater
// 	,  NULL
// 	,  3  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
// 	,  NULL );
// }

// void temp_sensor_task( void *pvParameters )
// {
// 	TickType_t xLastWakeTime;
// 	const TickType_t xFrequency = 5000/portTICK_PERIOD_MS;
//
// 	// Initialise the xLastWakeTime variable with the current time.
// 	xLastWakeTime = xTaskGetTickCount();
//
//
// 	size_t xBytesSent = 0;
// 	const TickType_t x100ms = pdMS_TO_TICKS(100);
// 	int16_t tem;
// 	int16_t hum;
//
// 	for(;;)
// 	{
// 		if ( HIH8120_OK != hih8120_wakeup() )
// 		{
// 			// Something went wrong
// 			// Investigate the return code further
// 			printf("Temperature and humidity sensor HIH8120 wakeup error.\n");
// 		}
//
// 		vTaskDelay(100);
//
// 		if ( HIH8120_OK !=  hih8120_measure() )
// 		{
// 			// Something went wrong
// 			// Investigate the return code further
// 			printf("Temperature and humidity sensor HIH8120 measure error.\n");
// 		}
// 		vTaskDelay(100);
//
// 		tem = hih8120_getTemperature_x10();
// 		setTemperaturePercent(tem);
// 		hum = hih8120_getHumidityPercent_x10();
// 		setHumidityPercent(hum);
//
// 		lora_driver_payload_t payload = getLoraPackage(2);
//
// 		xBytesSent = xMessageBufferSend(xMessageBufferHandle,
// 										&payload,
// 										sizeof(payload),
// 										x100ms);
// 		if(xBytesSent != sizeof(payload)){
// 			printf("Timed out.\n");
// 		}
// 		else{
//
// 			printf("Bytes sent: %d\n", xBytesSent);
// 			printf("Temp sent: %d\n", tem);
// 			printf("Humidity sent: %d\n", hum);
// // 			printf("Size of payload: %d\n", sizeof(payload));
// 			receivePayload();
//
// 		}
// 		vTaskDelay(xFrequency);
//
// 	}
// }

/*-----------------------------------------------------------*/
// void task2( void *pvParameters )
// {
// 	TickType_t xLastWakeTime;
// 	const TickType_t xFrequency = 1000/portTICK_PERIOD_MS; // 10000 ms
// 	xLastWakeTime = xTaskGetTickCount();
// 	lora_driver_payload_t payload;
// 	int16_t tem;
// 	int16_t hum;
//
// 	size_t xReceivedBytes;
// 	const TickType_t xWaitingTime = portMAX_DELAY;
//
// 	for(;;)
// 	{
// 		xReceivedBytes = xMessageBufferReceive (xMessageBufferHandle,
// 												&payload,
// 												sizeof(payload),
// 												xWaitingTime);
//
// 		if(xReceivedBytes > 0){
// 				printf("Number of bytes read from the message buffer: %d\n", xReceivedBytes);
// 				tem = (payload.bytes[0] << 8) | (payload.bytes[1]);
// 				hum = (payload.bytes[2] << 8) | (payload.bytes[3]);
// 				printf("Temperature read from the message buffer: %d\n", tem);
// 				printf("Humidity read from the message buffer: %d\n", hum);
// 		}
//
//
// 		vTaskDelay(1000);
// 	}
// }

// 
// 
// void receivePayload(){
// 	
// 	lora_driver_payload_t payload;
// 	int16_t tem;
// 	int16_t hum;
// 	
// 	size_t xReceivedBytes;
// 	const TickType_t xWaitingTime = portMAX_DELAY;
// 	const TickType_t x100ms = pdMS_TO_TICKS(100);
// 	xReceivedBytes = xMessageBufferReceive (xMessageBufferHandle,
// 	&payload,
// 	sizeof(payload),
// 	x100ms);
// 	
// 	if(xReceivedBytes > 0){
// 		printf("Bytes received: %d\n", xReceivedBytes);
// 		tem = (payload.bytes[0] << 8) | (payload.bytes[1]);
// 		hum = (payload.bytes[2] << 8) | (payload.bytes[3]);
// 		printf("Temperature received: %d\n", tem);
// 		printf("Humidity received: %d\n", hum);
// 	}
// }