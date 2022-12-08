#include "gtest/gtest.h"
#include "../fff/fff.h"
#include <stdint.h>

DEFINE_FFF_GLOBALS



extern "C" {

#include <stdio.h>

#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"
#include "FreeRTOS/semphr.h"
#include "FreeRTOS/queue.h"
#include "FreeRTOS/message_buffer.h"
#include "FreeRTOS/event_groups.h"
#include "FreeRTOS/timers.h"
#include "FreeRTOS/portable.h"

#include <CO2sensor.h>
#include "../SEP4_test/drivers/mh_z19.h"
//#include "../SEP4_test/Application.h"
}


//void intialize
//FAKE_VOID_FUNC(create_sensor_tasks);
/**
FAKE_VOID_FUNC(createCO2SensorTask);
FAKE_VOID_FUNC(CO2_measure);
FAKE_VOID_FUNC(MeasureCo2Task, void*);
FAKE_VOID_FUNC(myCo2CallBack, uint16_t);
FAKE_VALUE_FUNC(uint16_t, CO2_getPPM);
*/


FAKE_VOID_FUNC(mh_z19_initialise, serial_comPort_t);


//void mh_z19_injectCallBack(void(*mh_z19_callBack)(uint16_t));

//FAKE_VOID_FUNC(mh_z19_injectCallBack, *uint16_t;

FAKE_VALUE_FUNC(mh_z19_returnCode_t, mh_z19_takeMeassuring);
FAKE_VALUE_FUNC(mh_z19_returnCode_t, mh_z19_getCo2Ppm, uint16_t*);
FAKE_VALUE_FUNC(mh_z19_returnCode_t, mh_z19_setAutoCalibration, bool);
FAKE_VALUE_FUNC(mh_z19_returnCode_t, mh_z19_calibrateZeroPoint);

FAKE_VALUE_FUNC(mh_z19_returnCode_t, mh_z19_calibrateSpanPoint, uint16_t);



class CO2Test :public::testing::Test {
protected:
	void SetUp() override {
	/*  RESET_FAKE(createCO2SensorTask);
		RESET_FAKE(CO2_getPPM);
		RESET_FAKE(MeasureCo2Task);
		RESET_FAKE(CO2_measure);
		RESET_FAKE(myCo2CallBack);
		*/
		RESET_FAKE(mh_z19_initialise);
		RESET_FAKE(mh_z19_calibrateSpanPoint);
		RESET_FAKE(mh_z19_calibrateZeroPoint);
		RESET_FAKE(mh_z19_setAutoCalibration);
		RESET_FAKE(mh_z19_getCo2Ppm);
		RESET_FAKE(mh_z19_takeMeassuring)
		


		//RESET_FAKE(mh_z19_injectCallBack)

		FFF_RESET_HISTORY();
	}
	void TearDown() override{

	}



};


TEST_F(CO2Test, fuck) { 

	CO2_createSensor();
	ASSERT_EQ(1, mh_z19_initialise_fake.call_count);

  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}
TEST_F(CO2Test, CO2_Measure_the_data) {
	mh_z19_takeMeassuring_fake.return_val = MHZ19_NO_MEASSURING_AVAILABLE;
	CO2_measure();
	
	ASSERT_EQ(1, mh_z19_getCo2Ppm_fake.call_count );

	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}