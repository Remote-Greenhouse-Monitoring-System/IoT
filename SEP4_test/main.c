/*
* main.c
* Author : IHA
*
* Example main file including LoRaWAN setup
* Just for inspiration :)
*/

#include <stdio.h>
#include <avr/io.h>

#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <message_buffer.h>
#include "PackageHandler.h"

#include <stdio_driver.h>
#include <serial.h>
#include <string.h>

 // Needed for LoRaWAN
#include <lora_driver.h>
#include <status_leds.h>

// sensors
#include "hih8120.h"

// define two Tasks
// void task1( void *pvParameters );
//void task2( void *pvParameters );

void receivePayload();

// define hih8120 task

void temp_sensor_task( void *pvParameters );

// define semaphore handle
SemaphoreHandle_t xTestSemaphore;

//define message buffer handle 
MessageBufferHandle_t xMessageBufferHandle; 

// Prototype for LoRaWAN handler
void lora_handler_initialise(UBaseType_t lora_handler_task_priority);



/*-----------------------------------------------------------*/
void create_tasks_and_semaphores(void)
{
	// Semaphores are useful to stop a Task proceeding, where it should be paused to wait,
	// because it is sharing a resource, such as the Serial port.
	// Semaphores should only be used whilst the scheduler is running, but we can set it up here.
	if ( xTestSemaphore == NULL )  // Check to confirm that the Semaphore has not already been created.
	{
		xTestSemaphore = xSemaphoreCreateMutex();  // Create a mutex semaphore.
		if ( ( xTestSemaphore ) != NULL )
		{
			xSemaphoreGive( ( xTestSemaphore ) );  // Make the mutex available for use, by initially "Giving" the Semaphore.
		}
	}
	
	xMessageBufferHandle = xMessageBufferCreate(100);

// 	xTaskCreate(
// 	task1
// 	,  "Task1"  // A name just for humans
// 	,  configMINIMAL_STACK_SIZE  // This stack size can be checked & adjusted by reading the Stack Highwater
// 	,  NULL
// 	,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
// 	,  NULL );

// 	xTaskCreate(
// 	task2
// 	,  "Task2"  // A name just for humans
// 	,  configMINIMAL_STACK_SIZE  // This stack size can be checked & adjusted by reading the Stack Highwater
// 	,  NULL
// 	,  3  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
// 	,  NULL );
	
	xTaskCreate(
	temp_sensor_task
	,  "HIH8120_task"  // A name just for humans
	,  configMINIMAL_STACK_SIZE  // This stack size can be checked & adjusted by reading the Stack Highwater
	,  NULL
	,  3  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	,  NULL );
}

/*-----------------------------------------------------------*/
// void task1( void *pvParameters )
// {
// 	TickType_t xLastWakeTime;
// 	const TickType_t xFrequency = 1000/portTICK_PERIOD_MS; 
// 	xLastWakeTime = xTaskGetTickCount();
// 	
// 	uint16_t tx_buff[] = {10, 20, 30, 40};
// 	size_t xBytesSent;
// 	const TickType_t x100ms = pdMS_TO_TICKS(100);
// 
// 	for(;;)
// 	{
// 		xBytesSent = xMessageBufferSend(xMessageBufferHandle,
// 										(void *)tx_buff,
// 										sizeof(tx_buff),
// 										x100ms);
// 		if(xBytesSent != sizeof(tx_buff)){
// 			printf("Timed out.");
// 		}
// 		else{
// 			
// 			printf("Bytes put in buffer: %d\n", xBytesSent);
// 		
// 		}								
// 		vTaskDelay(1000);
// 	}
// 	
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

void receivePayload(){
	
		lora_driver_payload_t payload;
		int16_t tem;
		int16_t hum;
		
		size_t xReceivedBytes;
		const TickType_t xWaitingTime = portMAX_DELAY;
		const TickType_t x100ms = pdMS_TO_TICKS(100);
		xReceivedBytes = xMessageBufferReceive (xMessageBufferHandle,
												&payload,
												sizeof(payload),
												x100ms);
			
		if(xReceivedBytes > 0){
			printf("Bytes received: %d\n", xReceivedBytes);
			tem = (payload.bytes[0] << 8) | (payload.bytes[1]);
			hum = (payload.bytes[2] << 8) | (payload.bytes[3]);
			printf("Temperature received: %d\n", tem);
			printf("Humidity received: %d\n", hum);
			}
	}

/*-----------------------------------------------------------*/
void temp_sensor_task( void *pvParameters )
{
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 5000/portTICK_PERIOD_MS; 

	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();
	

	size_t xBytesSent = 0;
	const TickType_t x100ms = pdMS_TO_TICKS(100);
	int16_t tem;
	int16_t hum;

	for(;;)
	{
		if ( HIH8120_OK != hih8120_wakeup() )
		{
			// Something went wrong
			// Investigate the return code further
			printf("Temperature and humidity sensor HIH8120 wakeup error.\n");
		}
		
		vTaskDelay(100);
		
		if ( HIH8120_OK !=  hih8120_measure() )
		{
			// Something went wrong
			// Investigate the return code further
			printf("Temperature and humidity sensor HIH8120 measure error.\n");
		}
		vTaskDelay(100);
		
		tem = hih8120_getTemperature_x10();
		setTemperaturePercent(tem);
		hum = hih8120_getHumidityPercent_x10();
		setHumidityPercent(hum);
		
		lora_driver_payload_t payload = getLoraPackage(2);
		
		xBytesSent = xMessageBufferSend(xMessageBufferHandle,
										&payload,
										sizeof(payload),
										x100ms);
		if(xBytesSent != sizeof(payload)){
			printf("Timed out.\n");
		}
		else{
			
			printf("Bytes sent: %d\n", xBytesSent);
			printf("Temp sent: %d\n", tem);
			printf("Humidity sent: %d\n", hum);
// 			printf("Size of payload: %d\n", sizeof(payload));
			receivePayload();
			
		}
		vTaskDelay(xFrequency);

	}
}

/*-----------------------------------------------------------*/
void initialiseSystem()
{
	// Set output ports for leds used in the example
	DDRA |= _BV(DDA0) | _BV(DDA7);

	// Make it possible to use stdio on COM port 0 (USB) on Arduino board - Setting 57600,8,N,1
	stdio_initialise(ser_USART0);
	// Let's create some tasks
	create_tasks_and_semaphores();

	// vvvvvvvvvvvvvvvvv BELOW IS LoRaWAN initialisation vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
	// Status Leds driver
	status_leds_initialise(5); // Priority 5 for internal task
	// Initialise the LoRaWAN driver without down-link buffer
	lora_driver_initialise(1, NULL);
	// Create LoRaWAN task and start it up with priority 3
	lora_handler_initialise(3);
	
	// Initialize temperature and humidity sensor
	if ( HIH8120_OK == hih8120_initialise() )
	{
		// Driver initialised OK
		// Always check what hih8120_initialise() returns
		printf("HIH8120 initialized\n");
	}
	
	
}

/*-----------------------------------------------------------*/
int main(void)
{
	initialiseSystem(); // Must be done as the very first thing!!
	printf("Program Started!!\n");
	vTaskStartScheduler(); // Initialise and run the freeRTOS scheduler. Execution should never return from here.

	/* Replace with your application code */
	while (1)
	{
	}
}

