#include "gtest/gtest.h"
#include "FreeRTOS_FFF_MocksDeclaration.h"

extern "C" {
#include <CO2Sensor.h>
#include "FreeRTOS.h"
#include "message_buffer.h"
#include "event_groups.h"
#include "task.h"
}

class CO2SensorTest : public::testing::Test
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


TEST_F(CO2SensorTest, Initialise_MeasureBitNotSent)
{
	MeasureCo2Task();
	ASSERT_EQ(1, xEventGroupWaitBits_fake.call_count);
}

TEST_F(CO2SensorTest, Initialise_MeasureBitSent)
{
	//xEventGroupWaitBits_fake.return_val = CO2_MEASURE_BIT;
	//MeasureCo2Task();
	//ASSERT_EQ(1, xEventGroupWaitBits_fake.call_count);
	//ASSERT_EQ(CO2_MEASURE_BIT, xEventGroupWaitBits_fake.return_val);
	//ASSERT_EQ(MeasureCo2Task(); , 50);
	//ASSERT_EQ(1, xEventGroupSetBits_fake.call_count);
	//ASSERT_EQ(1, vTaskDelay_fake.call_count);
}