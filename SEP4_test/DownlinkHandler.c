/*
* downlinkHandler.c
*  Git: https://github.com/Remote-Greenhouse-Monitoring-System/IoT
*  Authors: Christopher, Himal, Jurin
*/

#include <ATMEGA_FreeRTOS.h>
#include <lora_driver.h>
#include <stdio.h>
#include <stdint.h>
#include <message_buffer.h>
#include <task.h>

#include "configuration.h"
#include "initialize.h"

#include "downlinkHandler.h"

static lora_driver_payload_t _downlink_payload;

void downlinkHandler_create(UBaseType_t priority)
{
	downlinkHandler_createTask(priority);
}

void downlinkHandler_createTask(UBaseType_t priority){
	xTaskCreate(
	downlinkHandler_task()
	,  "LRHandDownlink"
	,  configMINIMAL_STACK_SIZE+200
	,  NULL
	,  tskIDLE_PRIORITY + priority
	,  NULL );
}

void downlinkHandler_task(void *pvParameters){
	
	uint8_t xReceivedBytes = 0;
	
	for(;;){
		
		
		xReceivedBytes =  xMessageBufferReceive(downlinkMessageBufferHandle,
		&_downlink_payload,
		sizeof(lora_driver_payload_t),
		portMAX_DELAY);
		
		if(xReceivedBytes > 0){
			printf("downlinkHandler ---> DOWN LINK: from port: %d with %d bytes received.\n", _downlink_payload.portNo, _downlink_payload.len); // Just for Debug
			
			if(configSemaphore != NULL){
				if(xSemaphoreTake(configSemaphore, (TickType_t) 10 ) == pdTRUE){
					configuration_setConfiguration(_downlink_payload);
					xSemaphoreGive(configSemaphore);
				}
				else{
					printf("downlinkHandler ---> ERROR: DownlinkHandler Couldn't obtain semaphore.\n");
				}
			}
		}
	}
}

/*
\page lora_receive_downlink_message Receive a downlink message

In this use case, a downlink link message will be received.
A downlink message is received in a lora_driver_payload_t variable.

\note The driver must be initialised \ref lora_setup_use_case and must be setup to OTAA \ref lora_setup_to_OTAA or ABP \ref lora_setup_to_OTAA.
\note To be able to receive any downlink messages you may specify a FreeRTOS message buffer during the initialisation of the driver.
In this message buffer the received messages will be delivered by the driver (\ref lora_setup_use_case).

In this example a downlink message with 4 bytes will be received from the LoRaWAN.
These 4 bytes will in this example represent a maximum humidity setting and a maximum temperature setting that we want to be able to recieve from the LoRaWAN.
\par
\code
uint16_t maxHumSetting; // Max Humidity
int16_t maxTempSetting; // Max Temperature
\endcode

\section lora_receive_downlink_message_setup Down-link Message Setup

The following must be added to a FreeRTOS tasks for(;;) loop in your application - typical you will have a separate task for handling downlink messages:
-# Define a payload struct variable
Create a payload variable to receive the down-link message in
\code
lora_driver_payload_t downlinkPayload;
\endcode

-# Wait for a message to be received
\code
// this code must be in the loop of a FreeRTOS task!
xMessageBufferReceive(downLinkMessageBufferHandle, &downlinkPayload, sizeof(lora_driver_payload_t), portMAX_DELAY);
printf("DOWN LINK: from port: %d with %d bytes received!", downlinkPayload.port_no, downlinkPayload.len); // Just for Debug
if (4 == downlinkPayload.len) // Check that we have got the expected 4 bytes
{
// decode the payload into our variales
maxHumSetting = (downlinkPayload.bytes[0] << 8) + downlinkPayload.bytes[1];
maxTempSetting = (downlinkPayload.bytes[2] << 8) + downlinkPayload.bytes[3];
}
\endcode
*/