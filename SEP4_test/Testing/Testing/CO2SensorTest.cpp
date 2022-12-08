#include "gtest/gtest.h"
#include "FreeRTOS_FFF_MocksDeclaration.h"

DEFINE_FFF_GLOBALS

extern "C" {
#include <CO2Sensor.h>
#include "FreeRTOS.h"
#include "message_buffer.h"
#include "event_groups.h"
#include "task.h"
}
typedef void(*myCo2CallBacka) (uint16_t);

//create mocks for sensor functions
FAKE_VOID_FUNC(mh_z19_initialise, serial_comPort_t);
FAKE_VALUE_FUNC(mh_z19_returnCode_t, mh_z19_takeMeassuring);
FAKE_VALUE_FUNC(mh_z19_returnCode_t, mh_z19_getCo2Ppm, uint16_t*);
FAKE_VOID_FUNC(mh_z19_injectCallBack, myCo2CallBacka);


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
		RESET_FAKE(mh_z19_injectCallBack);
		RESET_FAKE(xTaskCreate);
		FFF_RESET_HISTORY();
	}

	void TearDown() override
	{

	}
};

TEST_F(CO2SensorTest, Test_mh_z19_initialise_is_called_and_mh_z19_injectCallBack)
{
	//Arange
	//Act  
	CO2_createSensor();
	//Assert/expect
	ASSERT_EQ(mh_z19_initialise_fake.arg0_val, ser_USART3);
	//ASSERT_EQ(mh_z19_injectCallBack_fake.arg0_val, myCo2CallBack); //TODO FIGURE THIS OUT 
	ASSERT_EQ(mh_z19_initialise_fake.call_count, 1);
	ASSERT_EQ(mh_z19_injectCallBack_fake.call_count, 1);
}

TEST_F(CO2SensorTest, test_myCo2CallBack_with_0)
{
	//Arange
	uint16_t ppm_parameter = 0;
	//Act
	myCo2CallBack(ppm_parameter);
	uint16_t temp = CO2_getPPM();
	//Assert/expect
	ASSERT_EQ(temp, 0);
}

TEST_F(CO2SensorTest, test_myCo2CallBack_with_5)
{
	//Arange
	uint16_t ppm_parameter = 5;
	//Act
	myCo2CallBack(ppm_parameter);
	uint16_t temp = CO2_getPPM();
	//Assert/expect
	ASSERT_EQ(temp, 5);
}

TEST_F(CO2SensorTest, test_myCo2CallBack_with_negativ)
{
	//Arange
	uint16_t ppm_parameter = -1;
	//Act
	myCo2CallBack(ppm_parameter);
	uint16_t temp = CO2_getPPM();
	//Assert/expect
	ASSERT_NE(temp, -1);
}

TEST_F(CO2SensorTest, test_mh_z19_takeMeassuring_with_OK)
{
	//Arange

	mh_z19_takeMeassuring_fake.return_val = MHZ19_OK;
	mh_z19_getCo2Ppm_fake.return_val = MHZ19_OK;
	
	//Act
	CO2_measure();

	//Assert/expect

	ASSERT_EQ(mh_z19_takeMeassuring_fake.call_count, 1);
	ASSERT_EQ(mh_z19_takeMeassuring_fake.return_val, MHZ19_OK);
	
}

TEST_F(CO2SensorTest, test_mh_z19_takeMeassuring_with_NO_MEASSURING_AVAILABLE)
{
	//Arange
	uint16_t ppm_parameter = -1;
	mh_z19_takeMeassuring_fake.return_val = MHZ19_NO_MEASSURING_AVAILABLE;
	mh_z19_getCo2Ppm_fake.return_val = MHZ19_NO_MEASSURING_AVAILABLE;

	//Act
	CO2_measure();

	//Assert/expect
	ASSERT_EQ(mh_z19_takeMeassuring_fake.call_count, 1);
	ASSERT_EQ(mh_z19_injectCallBack_fake.call_count, 0);
	ASSERT_EQ(mh_z19_takeMeassuring_fake.return_val, MHZ19_NO_MEASSURING_AVAILABLE);
}

TEST_F(CO2SensorTest, test_create_co2_sensor_task_with_priortiy_2)
{
	//Arange
	 mh_z19_takeMeassuring_fake.return_val = MHZ19_OK;
	 xEventGroupWaitBits_fake.return_val = CO2_MEASURE_BIT;
	//Act
	create_CO2_sensor_task(2);
	//Assert/expect
	

	ASSERT_EQ(xTaskCreate_fake.call_count, 1);
	ASSERT_EQ(xTaskCreate_fake.arg4_val,2);
	ASSERT_EQ(mh_z19_initialise_fake.call_count, 1);
	ASSERT_EQ(mh_z19_injectCallBack_fake.call_count, 1);
	ASSERT_EQ(CO2_MEASURE_BIT, xEventGroupWaitBits_fake.return_val);
}

TEST_F(CO2SensorTest, test_create_co2_sensor_task_with_priortiy_1)
{
	//Arange
	mh_z19_takeMeassuring_fake.return_val = MHZ19_OK;
	xEventGroupWaitBits_fake.return_val = CO2_MEASURE_BIT;
	//Act
	create_CO2_sensor_task(1);
	//Assert/expect


	ASSERT_EQ(xTaskCreate_fake.call_count, 1);
	ASSERT_EQ(xTaskCreate_fake.arg4_val, 1);
	ASSERT_EQ(mh_z19_initialise_fake.call_count, 1);
	ASSERT_EQ(mh_z19_injectCallBack_fake.call_count, 1);
	ASSERT_EQ(CO2_MEASURE_BIT, xEventGroupWaitBits_fake.return_val);
}


TEST_F(CO2SensorTest, test_runMeasureCO2Task)
{
	//Arange
	xEventGroupWaitBits_fake.return_val = CO2_MEASURE_BIT;

	//Act
	RunMeasureCo2Task();
	//Assert/expect
	ASSERT_EQ(xEventGroupWaitBits_fake.arg0_val, measureEventGroup);
	ASSERT_EQ(xEventGroupWaitBits_fake.arg1_val, CO2_MEASURE_BIT);
	ASSERT_EQ(mh_z19_takeMeassuring_fake.call_count, 1);
	ASSERT_EQ(xEventGroupSetBits_fake.call_count, 1);
	ASSERT_EQ(xEventGroupSetBits_fake.arg0_val, dataReadyEventGroup);
	ASSERT_EQ(xEventGroupSetBits_fake.arg1_val, CO2_READY_BIT);
}