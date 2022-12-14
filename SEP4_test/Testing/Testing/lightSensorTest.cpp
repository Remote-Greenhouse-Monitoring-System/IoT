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

	//Act  
	initialize_light_sensor();

	//Assert/expect
	ASSERT_EQ(tsl2591_initialise_fake.call_count, 1);
}



