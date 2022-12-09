
#include <stdio.h>
#include <avr/io.h>
#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <message_buffer.h>
#include <stdio_driver.h>
#include <serial.h>
#include <string.h>

 // Needed for LoRaWAN
#include <lora_driver.h>
#include <status_leds.h>


#include "Application.h"
#include "Initialize.h"
#include "FanController.h"
#include "Sensors/CO2Sensor.h"
#include "Sensors/TempHumSensor.h"
#include "UplinkHandler.h"
#include "DownlinkHandler.h"


void main_create(){
	uplinkHandler_create(4);
	downlinkHandler_create(4);
	application_create(3);
	CO2Sensor_create(1);
	tempHumSensor_create(1);
	fanController_create(2);
}
void initializeSystem()
{	
	// Make it possible to use stdio on COM port 0 (USB) on Arduino board - Setting 57600,8,N,1
	stdio_initialise(ser_USART0);
	// Status Leds driver
	status_leds_initialise(5); // Priority 5 for internal task

	initialize_event_groups();
	initialize_message_buffers();
	initialize_semaphore();
	// Initialise the LoRaWAN driver with down-link buffer
	lora_driver_initialise(ser_USART1, downlinkMessageBufferHandle);
	main_create();
			
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
