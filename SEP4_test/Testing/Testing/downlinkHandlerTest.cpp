#include "gtest/gtest.h"
#include "FreeRTOS_FFF_MocksDeclaration.h"


extern "C" {
#include "downlinkHandler.h"
}

class downlinkHandlerTest : public::testing::Test
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
		RESET_FAKE(xMessageBufferReceive);
		RESET_FAKE(xSemaphoreCreateMutex);
		FFF_RESET_HISTORY();
	}

	void TearDown() override
	{

	}
};

TEST_F(downlinkHandlerTest, test_create_lora_downlink_handler_task_with_priority_1)
{
	//Arange


	//Act
	create_lora_downlink_handler_task(1);

	//Assert/Expect
	ASSERT_EQ(xTaskCreate_fake.call_count, 1);
	ASSERT_EQ(xTaskCreate_fake.arg4_val, 1);
}

TEST_F(downlinkHandlerTest, test_create_lora_downlink_handler_task_with_priority_2)
{
	//Arange


	//Act
	create_lora_downlink_handler_task(2);

	//Assert/Expect
	ASSERT_EQ(xTaskCreate_fake.call_count, 1);
	ASSERT_EQ(xTaskCreate_fake.arg4_val, 2);
}

TEST_F(downlinkHandlerTest, test_lora_downlink_handler_task_run)
{
	//Arange
	xSemaphoreTake_fake.return_val = pdTRUE;
	xMessageBufferReceive_fake.return_val = 1;
	initialize_semaphore();
	//Act
	lora_downlink_handler_task_run();

	//Assert/Expect
	ASSERT_EQ(xMessageBufferReceive_fake.call_count, 1);
	ASSERT_EQ(xMessageBufferReceive_fake.return_val, 1);
	ASSERT_EQ(xMessageBufferReceive_fake.arg0_val, downlinkMessageBufferHandle);

	ASSERT_EQ(xSemaphoreTake_fake.call_count, 0);
	ASSERT_EQ(xSemaphoreGive_fake.call_count, 0);
}