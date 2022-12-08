/*
 * SystemSetupImpl.c
 *
 * Created: 07/12/2022 19.26.39
 *  Author: jurin
 */ 

#include "Initialize.h"

MessageBufferHandle_t uplinkMessageBufferHandle;
MessageBufferHandle_t downlinkMessageBufferHandle;


void initialize_event_groups(){
	dataReadyEventGroup = xEventGroupCreate();
	measureEventGroup = xEventGroupCreate();
}

void initialize_message_buffers(){
	uplinkMessageBufferHandle = xMessageBufferCreate(sizeof(lora_driver_payload_t)*2);
	if(uplinkMessageBufferHandle == NULL)
		printf("Failed to create uplink message buffer.\n");
	downlinkMessageBufferHandle = xMessageBufferCreate(sizeof(lora_driver_payload_t)*2);
	if(downlinkMessageBufferHandle == NULL)
		printf("Failed to create downlink message buffer.\n");

}
