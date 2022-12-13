#include "gtest/gtest.h"
#include "FreeRTOS_FFF_MocksDeclaration.h"


extern "C" {
#include "actionsController.h"
#include "../TestFiles/rc_servo.h"
}

FAKE_VOID_FUNC(rc_servo_initialise);

class actionsControllerTest : public::testing::Test
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
		RESET_FAKE(rc_servo_initialise);
		FFF_RESET_HISTORY();
	}

	void TearDown() override
	{

	}
};

TEST_F(actionsControllerTest, test_create_fan_controller_task_with_priority_1)
{
	//Arange

	
	//Act
	create_fan_controller_task(1);

	//Assert/Expect
	ASSERT_EQ(xTaskCreate_fake.call_count, 1);
	ASSERT_EQ(xTaskCreate_fake.arg4_val, 1);
}

TEST_F(actionsControllerTest, test_create_fan_controller_task_with_priority_2)
{
	//Arange


	//Act
	create_fan_controller_task(2);

	//Assert/Expect
	ASSERT_EQ(xTaskCreate_fake.call_count, 1);
	ASSERT_EQ(xTaskCreate_fake.arg4_val, 2);
}

TEST_F(actionsControllerTest, test_fan_controller_task_init)
{
	//Arange
	

	//Act
	fan_controller_task_init();

	//Assert/Expect
	ASSERT_EQ(1, xTaskGetTickCount_fake.call_count);
}

TEST_F(actionsControllerTest, test_fan_controller_task_run) //TODO ASK ABOUT THIS
{
	//Arange
	xEventGroupWaitBits_fake.return_val = ALL_READY_BITS;
	const TickType_t xFrequency = pdMS_TO_TICKS(5000);
	xSemaphoreTake_fake.return_val = pdTRUE;

	//Act
	fan_controller_task_run();

	//Assert/Expect
	ASSERT_EQ(xTaskDelayUntil_fake.call_count,1);
	ASSERT_EQ(xTaskDelayUntil_fake.arg1_val,xFrequency);
	
	ASSERT_EQ(xSemaphoreTake_fake.call_count, 1);
	ASSERT_EQ(xSemaphoreGive_fake.call_count, 1);
	
	ASSERT_EQ(xEventGroupSetBits_fake.call_count, 1);
	ASSERT_EQ(xEventGroupSetBits_fake.arg0_val, dataReadyEventGroup);
	ASSERT_EQ(xEventGroupSetBits_fake.arg1_val, ALL_MEASURE_BITS);

	ASSERT_EQ(xEventGroupWaitBits_fake.arg0_val, dataReadyEventGroup);
	ASSERT_EQ(xEventGroupWaitBits_fake.arg1_val, ALL_READY_BITS);
}
