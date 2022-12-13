#include "initialize.h"

EventGroupHandle_t measureEventGroup;
EventGroupHandle_t dataReadyEventGroup;
MessageBufferHandle_t uplinkMessageBufferHandle;
MessageBufferHandle_t downlinkMessageBufferHandle;
SemaphoreHandle_t configSemaphore;


void initialize_event_groups(){
	dataReadyEventGroup = xEventGroupCreate();
	measureEventGroup = xEventGroupCreate();
}

void initialize_message_buffers(){
	uplinkMessageBufferHandle = xMessageBufferCreate(sizeof(lora_driver_payload_t)*2);
	if(uplinkMessageBufferHandle == NULL){
		printf("Failed to create uplink message buffer.\n");
	}
	downlinkMessageBufferHandle = xMessageBufferCreate(sizeof(lora_driver_payload_t)*2);
	if(downlinkMessageBufferHandle == NULL){
		printf("Failed to create downlink message buffer.\n");
	}
}

 void initialize_semaphore(){
 	configSemaphore = xSemaphoreCreateMutex();
	 if(configSemaphore != NULL){
		 xSemaphoreGive(configSemaphore);
	 }
	 else{
		 printf("Failed to create config semaphore\n");
	 }
 }
