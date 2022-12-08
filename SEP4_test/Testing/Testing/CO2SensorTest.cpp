#include "gtest/gtest.h"
#include "FreeRTOS_FFF_MocksDeclaration.h"

extern "C" {
#include <CO2Sensor.h>
#include "FreeRTOS.h"
#include "message_buffer.h"
#include "event_groups.h"
#include "task.h"
}

//create mocks for sensor functions
FAKE_VOID_FUNC(mh_z19_initialise, serial_comPort_t);
FAKE_VALUE_FUNC(mh_z19_returnCode_t, mh_z19_takeMeassuring);
FAKE_VALUE_FUNC(mh_z19_returnCode_t, mh_z19_getCo2Ppm, uint16_t*);

class CO2SensorTest : public::testing::Test
{
protected:
	void SetUp() override
	{
		RESET_FAKE(xEventGroupSetBits);
		RESET_FAKE(xEventGroupWaitBits);
		RESET_FAKE(vTaskDelay);
		RESET_FAKE(mh_z19_initialise);
		RESET_FAKE(mh_z19_takeMeassuring);
		RESET_FAKE(mh_z19_getCo2Ppm);
		FFF_RESET_HISTORY();
	}

	void TearDown() override
	{

	}
};

TEST_F(CO2SensorTest, Test_mh_z19_initialise_is_called)
{
	//Arange
	//Act
	CO2_createSensor();
	//Assert/expect
	ASSERT_EQ(mh_z19_initialise_fake.call_count, 1);
}

TEST_F(CO2SensorTest, temp)
{
	//Arange
	//Act
	//Assert/expect
}

TEST_F(CO2SensorTest, temp2)
{
	//Arange
	//Act
	//Assert/expect
}

TEST_F(CO2SensorTest, temp3)
{
	//Arange
	//Act
	//Assert/expect
}

TEST_F(CO2SensorTest, temp4)
{
	//Arange
	//Act
	//Assert/expect
}

TEST_F(CO2SensorTest, temp5)
{
	//Arange
	//Act
	//Assert/expect
}