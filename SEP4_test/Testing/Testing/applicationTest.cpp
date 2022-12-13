#include "gtest/gtest.h"
#include "FreeRTOS_FFF_MocksDeclaration.h"


extern "C" {
#include "../TestFiles/application.h"
}



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

TEST_F(applicationTest, test_create_main_application_task_with_priority_1)
{
	//Arange


	//Act
	create_main_application_task(1);

	//Assert/Expect
	ASSERT_EQ(xTaskCreate_fake.call_count, 1);
	ASSERT_EQ(xTaskCreate_fake.arg4_val, 1);
}

TEST_F(applicationTest, test_create_main_application_task_with_priority_2)
{
	//Arange


	//Act
	create_main_application_task(2);

	//Assert/Expect
	ASSERT_EQ(xTaskCreate_fake.call_count, 1);
	ASSERT_EQ(xTaskCreate_fake.arg4_val, 2);
}

TEST_F(applicationTest, test_main_application_task_init)
{
	//Arange


	//Act
	main_application_task_init();

	//Assert/Expect
	ASSERT_EQ(xTaskGetTickCount_fake.call_count, 1);
}

TEST_F(applicationTest, test_main_application_task_run_semaphore_given)
{
	//Arange
	const TickType_t xFrequency = pdMS_TO_TICKS(300000UL);
	xSemaphoreTake_fake.return_val = pdTRUE;
	xEventGroupWaitBits_fake.return_val = ALL_READY_BITS;

	//Act
	main_application_task_run();

	//Assert/Expect
	ASSERT_EQ(xTaskDelayUntil_fake.call_count, 1);
	ASSERT_EQ(xTaskDelayUntil_fake.arg1_val, xFrequency);

	ASSERT_EQ(xSemaphoreTake_fake.call_count, 1);
	ASSERT_EQ(xSemaphoreGive_fake.call_count, 1);

	ASSERT_EQ(xEventGroupSetBits_fake.call_count, 1);
	ASSERT_EQ(xEventGroupSetBits_fake.arg0_val, dataReadyEventGroup);
	ASSERT_EQ(xEventGroupSetBits_fake.arg1_val, ALL_MEASURE_BITS);

	ASSERT_EQ(xEventGroupWaitBits_fake.arg0_val, dataReadyEventGroup);
	ASSERT_EQ(xEventGroupWaitBits_fake.arg1_val, ALL_READY_BITS);

	ASSERT_EQ(xMessageBufferSend_fake.call_count, 1);
	ASSERT_EQ(xMessageBufferSend_fake.arg0_val, uplinkMessageBufferHandle);
}

TEST_F(applicationTest, test_main_application_task_run_semaphore_not_given)
{
	//Arange
	const TickType_t xFrequency = pdMS_TO_TICKS(300000UL);
	xSemaphoreTake_fake.return_val = pdFALSE;
	xEventGroupWaitBits_fake.return_val = ALL_READY_BITS;

	//Act
	main_application_task_run();

	//Assert/Expect
	ASSERT_EQ(xTaskDelayUntil_fake.call_count, 1);
	ASSERT_EQ(xTaskDelayUntil_fake.arg1_val, xFrequency);

	ASSERT_EQ(xSemaphoreTake_fake.call_count, 1);
	ASSERT_EQ(xSemaphoreGive_fake.call_count, 0);

	ASSERT_EQ(xEventGroupSetBits_fake.call_count, 1);
	ASSERT_EQ(xEventGroupSetBits_fake.arg0_val, dataReadyEventGroup);
	ASSERT_EQ(xEventGroupSetBits_fake.arg1_val, ALL_MEASURE_BITS);

	ASSERT_EQ(xEventGroupWaitBits_fake.arg0_val, dataReadyEventGroup);
	ASSERT_EQ(xEventGroupWaitBits_fake.arg1_val, ALL_READY_BITS);

	ASSERT_EQ(xMessageBufferSend_fake.call_count, 1);
	ASSERT_EQ(xMessageBufferSend_fake.arg0_val, uplinkMessageBufferHandle);
}