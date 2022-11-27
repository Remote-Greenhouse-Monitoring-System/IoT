#include "gtest/gtest.h"

extern "C"
{
//#include "TempHum"
}

class TempHumSensor : public ::testing::Test
{
protected:
	void SetUp() override
	{

	}

	void TearDown() override
	{

	}
};

TEST_F(TempHumSensor, SensorReadsZeroWhenCreated)
{
	//Arrange

	//Act
//	tempHumSensor_t = tempHumSensor_create();
	//Assert
}