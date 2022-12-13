#include "gtest/gtest.h"
#include "FreeRTOS_FFF_MocksDeclaration.h"


extern "C" {
#include "../TestFiles/uplinkHandler.h"
}

FAKE_VALUE_FUNC(uint8_t, lora_driver_getMaxPayloadSize);
FAKE_VOID_FUNC(lora_driver_initialise, serial_comPort_t, MessageBufferHandle_t);
//FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setOtaaIdentity , char ,char ,char);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_configureToEu868);
FAKE_VALUE_FUNC(char*, lora_driver_mapReturnCodeToText, lora_driver_returnCode_t);
//FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setAbpIdentity, char, char, char);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_join, lora_driver_joinMode_t);
FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_sendUploadMessage, bool, lora_driver_payload_t*);
//FAKE_VALUE_FUNC(lora_driver_returnCode_t, lora_driver_setDeviceIdentifier,const char);




class applicationTest : public::testing::Test
{
protected:
	void SetUp() override
	{
		RESET_FAKE(xTaskGetTickCount);
		RESET_FAKE(xTaskCreate);
		RESET_FAKE(xTaskDelayUntil);
		RESET_FAKE(xSemaphoreTake);
		RESET_FAKE(xSemaphoreGive);
		RESET_FAKE(xEventGroupWaitBits);
		RESET_FAKE(xEventGroupSetBits);
		RESET_FAKE(xMessageBufferSend);
		FFF_RESET_HISTORY();
	}

	void TearDown() override
	{

	}
};