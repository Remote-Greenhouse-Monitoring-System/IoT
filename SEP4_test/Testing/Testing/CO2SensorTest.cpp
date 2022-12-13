#include "gtest/gtest.h"
#include "FreeRTOS_FFF_MocksDeclaration.h"

DEFINE_FFF_GLOBALS

extern "C" {
#include "CO2Sensor.h"
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



class co2SensorTest : public::testing::Test
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



TEST_F(co2SensorTest, Test_CO2_createSensor_is_called)
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

TEST_F(co2SensorTest, test_myCo2CallBack_is_called_with_0)
{
	//Arange
	uint16_t ppm_parameter = 0;

	//Act
	myCo2CallBack(ppm_parameter);
	uint16_t temp = CO2_getPPM();

	//Assert/expect
	ASSERT_EQ(temp, 0);
}

TEST_F(co2SensorTest, test_myCo2CallBack_is_called_with_5)
{
	//Arange
	uint16_t ppm_parameter = 5;

	//Act
	myCo2CallBack(ppm_parameter);
	uint16_t temp = CO2_getPPM();

	//Assert/expect
	ASSERT_EQ(temp, 5);
}

TEST_F(co2SensorTest, test_myCo2CallBack_is_called_with_negativ)
{
	//Arange
	uint16_t ppm_parameter = -1;

	//Act
	myCo2CallBack(ppm_parameter);
	uint16_t temp = CO2_getPPM();

	//Assert/expect
	ASSERT_NE(temp, -1);
}

TEST_F(co2SensorTest, test_CO2_measure_is_called_with_OK) //LOOK INTO THIS ONE
{
	//Arange
	//uint16_t ppm_parameter = 700;
	mh_z19_takeMeassuring_fake.return_val = MHZ19_OK;
	mh_z19_getCo2Ppm_fake.return_val = MHZ19_OK;
	//mh_z19_getCo2Ppm_fake.arg0_val = &ppm_parameter;

	//Act
	CO2_measure();

	//Assert/expect
	ASSERT_EQ(mh_z19_takeMeassuring_fake.call_count, 1);
	ASSERT_EQ(mh_z19_takeMeassuring_fake.return_val, MHZ19_OK);
	//ASSERT_EQ(ppm_parameter, CO2_getPPM);
}

TEST_F(co2SensorTest, test_CO2_measure_is_called_with_not_OK) //LOOK INTO THIS ONE
{
	//Arange
	//uint16_t ppm_parameter = -1;
	mh_z19_takeMeassuring_fake.return_val = MHZ19_NO_MEASSURING_AVAILABLE;
	mh_z19_getCo2Ppm_fake.return_val = MHZ19_NO_MEASSURING_AVAILABLE;
	//mh_z19_getCo2Ppm_fake.arg0_val = &ppm_parameter;

	//Act
	CO2_measure();

	//Assert/expect
	ASSERT_EQ(mh_z19_takeMeassuring_fake.call_count, 1);
	ASSERT_EQ(mh_z19_takeMeassuring_fake.return_val, MHZ19_NO_MEASSURING_AVAILABLE);
	//ASSERT_EQ(ppm_parameter, CO2_getPPM);
}


TEST_F(co2SensorTest, test_create_co2_sensor_task_with_priortiy_1)
{
	//Arange

	//Act
	create_CO2_sensor_task(1);
	
	//Assert/expect
	ASSERT_EQ(xTaskCreate_fake.call_count, 1);
	ASSERT_EQ(xTaskCreate_fake.arg4_val, 1);
}

TEST_F(co2SensorTest, test_create_co2_sensor_task_with_priortiy_2)
{
	//Arange

	//Act
	create_CO2_sensor_task(2);

	//Assert/expect
	ASSERT_EQ(xTaskCreate_fake.call_count, 1);
	ASSERT_EQ(xTaskCreate_fake.arg4_val, 2);
}




TEST_F(co2SensorTest, test_MeasureCO2Task)
{
	//Arange
	xEventGroupWaitBits_fake.return_val = CO2_MEASURE_BIT;

	//Act
	MeasureCo2Task();

	//Assert/expect
	ASSERT_EQ(xEventGroupWaitBits_fake.arg0_val, measureEventGroup);
	ASSERT_EQ(xEventGroupWaitBits_fake.arg1_val, CO2_MEASURE_BIT);

	ASSERT_EQ(pdMS_TO_TICKS(100), vTaskDelay_fake.arg0_val);
	ASSERT_EQ(vTaskDelay_fake.call_count, 1);
	
	ASSERT_EQ(xEventGroupSetBits_fake.call_count, 1);
	ASSERT_EQ(xEventGroupSetBits_fake.arg0_val, dataReadyEventGroup);
	ASSERT_EQ(xEventGroupSetBits_fake.arg1_val, CO2_READY_BIT);
}