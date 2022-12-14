#include "gtest/gtest.h"
#include "FreeRTOS_FFF_MocksDeclaration.h"


extern "C" {
#include "FreeRTOS.h"

#include "../TestFiles/lightSensor.h"
#include "message_buffer.h"
#include "event_groups.h"
#include "task.h"
}

typedef void(*callBackForLightTest) (tsl2591_returnCode_t);

FAKE_VALUE_FUNC(tsl2591_returnCode_t, tsl2591_initialise, callBackForLightTest);
FAKE_VALUE_FUNC(tsl2591_returnCode_t, tsl2591_getLux, float*);
FAKE_VALUE_FUNC(tsl2591_returnCode_t, tsl2591_enable);
FAKE_VALUE_FUNC(tsl2591_returnCode_t, tsl2591_fetchData);





class lightSensorTest: public::testing::Test
{
protected:
	void SetUp() override
	{
		RESET_FAKE(xEventGroupSetBits);
		RESET_FAKE(xEventGroupWaitBits);
		RESET_FAKE(vTaskDelay);
		RESET_FAKE(xTaskCreate);
		RESET_FAKE(tsl2591_initialise);
		RESET_FAKE(tsl2591_getLux);
		RESET_FAKE(tsl2591_enable);
		RESET_FAKE(tsl2591_fetchData);
		FFF_RESET_HISTORY();
	}

	void TearDown() override
	{


	}
};


TEST_F(lightSensorTest, Test_light_sensor_is_initislised)
{
	//Arange
	tsl2591_initialise_fake.return_val = TSL2591_OK;
	tsl2591_enable_fake.return_val = TSL2591_OK;

	//Act  
	initialize_light_sensor();

	//Assert/expect
	ASSERT_EQ(tsl2591_initialise_fake.call_count, 1);
	ASSERT_EQ(tsl2591_enable_fake.call_count, 1);

}


TEST_F(lightSensorTest, Test_light_sensor_is_not_initislised)
{
	//Arange
	tsl2591_initialise_fake.return_val = TSL2591_ERROR;
	tsl2591_enable_fake.return_val = TSL2591_ERROR;

	//Act  
	initialize_light_sensor();

	//Assert/expect
	ASSERT_EQ(tsl2591_initialise_fake.call_count, 1);
	ASSERT_EQ(tsl2591_enable_fake.call_count, 0);

}



TEST_F(lightSensorTest, test_create_light_sensor_task_with_priortiy_1)
{
	//Arange

	//Act
	create_light_sensor_task(1);

	//Assert/expect
	ASSERT_EQ(xTaskCreate_fake.call_count, 1);
	ASSERT_EQ(xTaskCreate_fake.arg4_val, 1);
}

TEST_F(lightSensorTest, test_measure_light_task)
{
	//Arange
	xEventGroupWaitBits_fake.return_val = LIGHT_MEASURE_BIT;

	//Act
	measure_light_task_inline();
	//Assert/expect
	ASSERT_EQ(xEventGroupWaitBits_fake.arg0_val, measureEventGroup);
	ASSERT_EQ(xEventGroupWaitBits_fake.arg1_val, LIGHT_MEASURE_BIT);

	ASSERT_EQ(pdMS_TO_TICKS(100), vTaskDelay_fake.arg0_val);
	ASSERT_EQ(vTaskDelay_fake.call_count, 1);

	ASSERT_EQ(xEventGroupSetBits_fake.call_count, 1);
	ASSERT_EQ(xEventGroupSetBits_fake.arg0_val, dataReadyEventGroup);
	ASSERT_EQ(xEventGroupSetBits_fake.arg1_val, LIGHT_READY_BIT);

	ASSERT_EQ(tsl2591_fetchData_fake.call_count, 1);
}



TEST_F(lightSensorTest, test_TSL2591_Call_back_with_data_ready)
{
	//arrange 
	


	//act
	tsl2591Callback(TSL2591_DATA_READY);


	ASSERT_EQ(1, tsl2591_getLux_fake.call_count);

}







