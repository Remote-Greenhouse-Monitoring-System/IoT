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
		
		FFF_RESET_HISTORY();

	}

	void TearDown() override
	{

	}
};