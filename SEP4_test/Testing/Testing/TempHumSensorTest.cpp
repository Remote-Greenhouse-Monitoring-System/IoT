#include "gtest/gtest.h"
#include "FreeRTOS_FFF_MocksDeclaration.h"

extern "C" {
#include <TempHumSensor.h>
#include "FreeRTOS.h"
#include "message_buffer.h"
#include "event_groups.h"
#include "task.h"
}

//create mocks for sensor functions
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_initialise);
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_destroy);
FAKE_VALUE_FUNC(bool, hih8120_isReady);
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_wakeup);
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_measure);
FAKE_VALUE_FUNC(uint16_t, hih8120_getHumidityPercent_x10);
FAKE_VALUE_FUNC(int16_t, hih8120_getTemperature_x10);
FAKE_VALUE_FUNC(float, hih8120_getHumidity);
FAKE_VALUE_FUNC(float, hih8120_getTemperature);


class TempHumSensorTest : public::testing::Test
{
protected:
	void SetUp() override
	{
		RESET_FAKE(xEventGroupSetBits);
		RESET_FAKE(xEventGroupWaitBits);
		RESET_FAKE(vTaskDelay);
		RESET_FAKE(hih8120_initialise);
		RESET_FAKE(hih8120_destroy);
		RESET_FAKE(hih8120_isReady);
		RESET_FAKE(hih8120_wakeup);
		RESET_FAKE(hih8120_measure);
		RESET_FAKE(hih8120_getHumidityPercent_x10);
		RESET_FAKE(hih8120_getTemperature_x10);
		RESET_FAKE(hih8120_getHumidity);
		RESET_FAKE(hih8120_getTemperature);
		FFF_RESET_HISTORY();
	}

	void TearDown() override
	{

	}
};

TEST_F(TempHumSensorTest, test_hih8120_initialise_OK)
{
	//Arange
	hih8120_initialise_fake.return_val = HIH8120_OK;
	//Act
	initialise_TempHumSensor();
	//ASSERT/EXPECT
	ASSERT_EQ(hih8120_initialise_fake.call_count,1);
	ASSERT_EQ(hih8120_initialise_fake.return_val, HIH8120_OK);
}

TEST_F(TempHumSensorTest, test_hih8120_wakeup_and_hih8120_measure_OK)
{
	//Arange
	hih8120_wakeup_fake.return_val = HIH8120_OK;
	hih8120_measure_fake.return_val = HIH8120_OK;
	//Act
	measure_Temp_Hum();
	//ASSERT/EXPECT

	ASSERT_EQ(hih8120_wakeup_fake.return_val, HIH8120_OK);
	ASSERT_EQ(hih8120_measure_fake.return_val, HIH8120_OK);
	ASSERT_EQ(vTaskDelay_fake.call_count,2);
	ASSERT_EQ(pdMS_TO_TICKS(51), vTaskDelay_fake.arg0_val);
}

TEST_F(TempHumSensorTest, test_temperature_and_humidity_equal_to_0)
{
	//Arange
	
	//Act

	//ASSERT/EXPECT

}

TEST_F(TempHumSensorTest, test_RunTemp_Hum_Main_task)
{
	//Arange

	//Act

	//ASSERT/EXPECT

}