/*
 * UplinkHandlerImpl.c
 *
 * Created: 07/12/2022 21.36.34
 *  Author: jurin
 */ 


#include "UplinkHandler.h"

void lora_uplink_handler_task(void *pvParameters);

static lora_driver_payload_t _uplink_payload;
MessageBufferHandle_t uplinkMessageBufferHandle;

void create_lora_uplink_handler_task(UBaseType_t priority){
	xTaskCreate(
	lora_uplink_handler_task
	,  "LRHandUplink"  
	,  configMINIMAL_STACK_SIZE+200  
	,  NULL
	,  tskIDLE_PRIORITY + priority  
	,  NULL );
}

static void _lora_setup(void)
{
	char _out_buf[20];
	lora_driver_returnCode_t rc;
	status_leds_slowBlink(led_ST2); // OPTIONAL: Led the green led blink slowly while we are setting up LoRa

	// Factory reset the transceiver
	printf("FactoryReset >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_rn2483FactoryReset()));
	
	// Configure to EU868 LoRaWAN standards
	printf("Configure to EU868 >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_configureToEu868()));

	// Get the transceivers HW EUI
	rc = lora_driver_getRn2483Hweui(_out_buf);
	printf("Get HWEUI >%s<: %s\n",lora_driver_mapReturnCodeToText(rc), _out_buf);

	// Set the HWEUI as DevEUI in the LoRaWAN software stack in the transceiver
	printf("Set DevEUI: %s >%s<\n", _out_buf, lora_driver_mapReturnCodeToText(lora_driver_setDeviceIdentifier(_out_buf)));

	// Set Over The Air Activation parameters to be ready to join the LoRaWAN
	printf("Set OTAA Identity appEUI:%s appKEY:%s devEUI:%s >%s<\n", LORA_appEUI, LORA_appKEY, _out_buf, lora_driver_mapReturnCodeToText(lora_driver_setOtaaIdentity(LORA_appEUI,LORA_appKEY,_out_buf)));

	// Save all the MAC settings in the transceiver
	printf("Save mac >%s<\n",lora_driver_mapReturnCodeToText(lora_driver_saveMac()));

	// Enable Adaptive Data Rate
	printf("Set Adaptive Data Rate: ON >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_setAdaptiveDataRate(LORA_ON)));

	// Set receiver window1 delay to 500 ms - this is needed if down-link messages will be used
	printf("Set Receiver Delay: %d ms >%s<\n", 500, lora_driver_mapReturnCodeToText(lora_driver_setReceiveDelay(500)));

	// Join the LoRaWAN
	uint8_t maxJoinTriesLeft = 10;
	
	do {
		rc = lora_driver_join(LORA_OTAA);
		printf("Join Network TriesLeft:%d >%s<\n", maxJoinTriesLeft, lora_driver_mapReturnCodeToText(rc));

		if ( rc != LORA_ACCEPTED)
		{
			// Make the red led pulse to tell something went wrong
			status_leds_longPuls(led_ST1); // OPTIONAL
			// Wait 5 sec and lets try again
			vTaskDelay(pdMS_TO_TICKS(5000UL));
		}
		else
		{
			break;
		}
	} while (--maxJoinTriesLeft);

	if (rc == LORA_ACCEPTED)
	{
		// Connected to LoRaWAN :-)
		// Make the green led steady
		status_leds_ledOn(led_ST2); // OPTIONAL
	}
	else
	{
		// Something went wrong
		// Turn off the green led
		status_leds_ledOff(led_ST2); // OPTIONAL
		// Make the red led blink fast to tell something went wrong
		status_leds_fastBlink(led_ST1); // OPTIONAL

		// Lets stay here
		while (1)
		{
			taskYIELD();
		}
	}
}

void lora_uplink_handler_task( void *pvParameters )
{
	// Hardware reset of LoRaWAN transceiver
	lora_driver_resetRn2483(1);
	vTaskDelay(2);
	lora_driver_resetRn2483(0);
	// Give it a chance to wakeup
	vTaskDelay(150);

	lora_driver_flushBuffers(); // get rid of first version string from module after reset!

	_lora_setup();
	
	for(;;)
	{

		int16_t tem = 0;
		uint16_t hum = 0;
		uint16_t co2 = 0;
		uint8_t status = 0;
		uint8_t xReceivedBytes = 0;
		
		xReceivedBytes = xMessageBufferReceive (uplinkMessageBufferHandle,
		&_uplink_payload,
		sizeof(_uplink_payload),
		portMAX_DELAY);

		if(xReceivedBytes > 0){
			// 				printf("Number of bytes read from the message buffer: %d\n", xReceivedBytes);
			tem = (_uplink_payload.bytes[0] << 8) | (_uplink_payload.bytes[1]);
			hum = (_uplink_payload.bytes[2] << 8) | (_uplink_payload.bytes[3]);
			co2 = (_uplink_payload.bytes[4] << 8) | (_uplink_payload.bytes[5]);
			status = _uplink_payload.bytes[6];
			
			printf("Temperature sent: %d\n", tem);
			printf("Humidity sent: %d\n", hum);
			printf("CO2 sent: %d\n", co2);
			printf("Status sent: %d\n", status);
			
			status_leds_shortPuls(led_ST4);  // OPTIONAL
			printf("Upload Message >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_sendUploadMessage(false, &_uplink_payload)));

		}
	}
}

// lora_driver_returnCode_t rc;
// 
// if ((rc = lora_driver_sendUploadMessage(false, &_uplinkPayload)) == LORA_MAC_TX_OK )
// {
// 	// The uplink message is sent and there is no downlink message received
// }
// else if (rc == LORA_MAC_RX_OK)
// {
// 	// The uplink message is sent and a downlink message is received
// }
