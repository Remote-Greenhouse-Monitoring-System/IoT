#include <stdio.h>
//#include <avr/io.h>
#include "../Testing/FreeRTOS.h"
#include "../Testing/task.h"
#include "../Testing/semphr.h"
#include "../Testing/message_buffer.h"
#include "stdio_driver.h"
#include "serial.h"
#include <string.h>

 // Needed for LoRaWAN
#include "lora_driver.h"
#include "status_leds.h"


#include "application.h"
#include "initialize.h"
#include "actionsController.h"
#include "co2Sensor.h"
#include "tempHumSensor.h"
#include "uplinkHandler.h"
#include "downlinkHandler.h"
#include "servoController.h"


void create_all_tasks(){
	create_lora_uplink_handler_task(4);
	create_lora_downlink_handler_task(4);
	create_main_application_task(3);
	create_CO2_sensor_task(1);
	create_TempHum_sensor_task(1);
	create_fan_controller_task(2);
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
	initialise_rc_servo();
	// Initialise the LoRaWAN driver with down-link buffer
	lora_driver_initialise(ser_USART1, downlinkMessageBufferHandle);
	create_all_tasks();
			
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
