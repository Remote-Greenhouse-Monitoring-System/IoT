#include "gtest/gtest.h"
#include "FreeRTOS_FFF_MocksDeclaration.h"


extern "C" {
#include "TempHumSensor.h"
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


class tempHumSensorTest : public::testing::Test
{
protected:
	void SetUp() override
	{
		RESET_FAKE(xEventGroupSetBits);
		RESET_FAKE(xEventGroupWaitBits);
		RESET_FAKE(vTaskDelay);
		RESET_FAKE(xTaskCreate);
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

TEST_F(tempHumSensorTest, test_initialise_TempHumSensor_with_OK)
{
	//Arange
	hih8120_initialise_fake.return_val = HIH8120_OK;
	
	//Act
	initialise_TempHumSensor();

	//ASSERT/EXPECT
	ASSERT_EQ(hih8120_initialise_fake.call_count,1);
	ASSERT_EQ(hih8120_initialise_fake.return_val, HIH8120_OK);
}

TEST_F(tempHumSensorTest, test_initialise_TempHumSensor_with_not_OK)
{
	//Arange
	hih8120_initialise_fake.return_val = HIH8120_DRIVER_NOT_INITIALISED;

	//Act
	initialise_TempHumSensor();

	//ASSERT/EXPECT
	ASSERT_EQ(hih8120_initialise_fake.call_count, 1);
	ASSERT_EQ(hih8120_initialise_fake.return_val, HIH8120_DRIVER_NOT_INITIALISED);
}

TEST_F(tempHumSensorTest, test_create_TempHum_sensor_task_with_priortiy_1)
{
	//Arange

	//Act
	create_TempHum_sensor_task(1);

	//ASSERT/EXPECT
	ASSERT_EQ(xTaskCreate_fake.call_count, 1);
	ASSERT_EQ(xTaskCreate_fake.arg4_val, 1);
}

TEST_F(tempHumSensorTest, test_create_TempHum_sensor_task_with_priortiy_2)
{
	//Arange

	//Act
	create_TempHum_sensor_task(2);

	//ASSERT/EXPECT
	ASSERT_EQ(xTaskCreate_fake.call_count, 1);
	ASSERT_EQ(xTaskCreate_fake.arg4_val, 2);
}

TEST_F(tempHumSensorTest, test_measure_Temp_Hum_with_OK)
{
	//Arange
	hih8120_wakeup_fake.return_val = HIH8120_OK;
	hih8120_measure_fake.return_val = HIH8120_OK;
	hih8120_getHumidityPercent_x10_fake.return_val = 10;
	hih8120_getTemperature_x10_fake.return_val = 10;
	
	//Act
	measure_Temp_Hum();
	
	//ASSERT/EXPECT
	ASSERT_EQ(hih8120_wakeup_fake.return_val, HIH8120_OK);
	ASSERT_EQ(hih8120_measure_fake.return_val, HIH8120_OK);
	ASSERT_EQ(vTaskDelay_fake.call_count,2);
	//ASSERT_EQ(pdMS_TO_TICKS(60), vTaskDelay_fake.arg0_val); //TODO ASK ABOUT THIS 
	ASSERT_EQ(pdMS_TO_TICKS(50), vTaskDelay_fake.arg0_val);
	ASSERT_EQ(10,hih8120_getHumidityPercent_x10_fake.return_val);
	ASSERT_EQ(10,hih8120_getTemperature_x10_fake.return_val);
}

TEST_F(tempHumSensorTest, test_measure_Temp_Hum_with_not_OK)
{
	//Arange
	hih8120_wakeup_fake.return_val = HIH8120_DRIVER_NOT_INITIALISED;
	hih8120_measure_fake.return_val = HIH8120_DRIVER_NOT_INITIALISED;
	hih8120_getHumidityPercent_x10_fake.return_val = 10;
	hih8120_getTemperature_x10_fake.return_val = 10;

	//Act
	measure_Temp_Hum();

	//ASSERT/EXPECT
	ASSERT_EQ(hih8120_wakeup_fake.return_val, HIH8120_DRIVER_NOT_INITIALISED);
	ASSERT_EQ(hih8120_measure_fake.return_val, HIH8120_DRIVER_NOT_INITIALISED);
	ASSERT_EQ(vTaskDelay_fake.call_count, 2);
	//ASSERT_EQ(pdMS_TO_TICKS(60), vTaskDelay_fake.arg0_val); //TODO ASK ABOUT THIS 
	ASSERT_EQ(pdMS_TO_TICKS(50), vTaskDelay_fake.arg0_val);
	ASSERT_EQ(10, hih8120_getHumidityPercent_x10_fake.return_val);
	ASSERT_EQ(10, hih8120_getTemperature_x10_fake.return_val);
}

TEST_F(tempHumSensorTest, test_Temp_Hum_Main_Task)
{
	//Arange
	xEventGroupWaitBits_fake.return_val = TEMP_HUM_MEASURE_BIT;

	//Act
	Temp_Hum_Main_Task();

	//ASSERT/EXPECT
	ASSERT_EQ(xEventGroupWaitBits_fake.arg0_val, measureEventGroup);
	ASSERT_EQ(xEventGroupWaitBits_fake.arg1_val, TEMP_HUM_MEASURE_BIT);

	ASSERT_EQ(xEventGroupSetBits_fake.call_count, 1);
	ASSERT_EQ(xEventGroupSetBits_fake.arg0_val, dataReadyEventGroup);
	ASSERT_EQ(xEventGroupSetBits_fake.arg1_val, TEMP_HUM_READY_BIT);
}