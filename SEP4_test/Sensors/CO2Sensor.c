/*
* CO2Sensor.c
*
* Created: 11/20/2022 2:43:52 PM
*  Author: Himal, Christopher
*/

#include "CO2Sensor.h"

void CO2Sensor_task(void* pvpParameter);

//Initializing last ppm as 0.
uint16_t lastCO2ppm = 0;


//Initializes the CO2 sensor driver, creates the CO2 task and sets up the callback.
// The parameter is the USART port the MH-Z19 sensor is connected to - in this case USART3.
void CO2Sensor_create(UBaseType_t priority) {
	mh_z19_initialise(ser_USART3);
	mh_z19_injectCallBack(myCo2CallBack);
	create_CO2_sensor_createTask(priority);
}

//Getter for lastCO2ppm.
uint16_t CO2Sensor_getPPM() {
	return lastCO2ppm;
}

//Sets lastCO2ppm when the callback is called
void myCo2CallBack(uint16_t ppm_parameter)
{
	lastCO2ppm = ppm_parameter;
}

//Measures the CO2.
void CO2Sensor_measure() {
	mh_z19_returnCode_t measure_rc = mh_z19_takeMeassuring();
	if (measure_rc != MHZ19_OK)
	{
		printf("ERROR: CO2 Sensor could not measure, ");
		CO2Sensor_printReturnCode(measure_rc);
	}
	else
	{
		printf("--->Initialized, CO2 Sensor<---");
	}
	lastCO2ppm = mh_z19_getCo2Ppm(&lastCO2ppm);
}

//Creates the CO2 task.
void create_CO2_sensor_createTask(UBaseType_t priority){
	xTaskCreate(
	CO2Sensor_task,
	"MeasuringCO2_Task",
	configMINIMAL_STACK_SIZE,
	NULL,
	tskIDLE_PRIORITY + priority,
	NULL);
}

//The CO2 sensor task.
void CO2Sensor_task(void* pvpParameter){
	while(1)
	{
	//Usage of Event group Wait fun until co2 measure bit is set to 1
	EventBits_t uxBits = xEventGroupWaitBits(measureEventGroup,CO2_MEASURE_BIT,pdTRUE,pdTRUE,portMAX_DELAY);
	
	if ((uxBits & (CO2_MEASURE_BIT)) == CO2_MEASURE_BIT)
	{
		//printf("Measure bit and event bit was successfully checked ");
		CO2Sensor_measure();
		//printf("Measurement successful , now time to set ready bit of c02 ");
		xEventGroupSetBits(dataReadyEventGroup,CO2_READY_BIT);
		//vTaskDelay(pdMS_TO_TICKS(100));
	}}
}

//Prints a formatted return code.
void CO2Sensor_printReturnCode(mh_z19_returnCode_t rc)
{
	char* returnCodeString;
	switch(rc){
		case MHZ19_OK: returnCodeString = "MHZ19_OK - Everything went well";
		case MHZ19_NO_MEASSURING_AVAILABLE: returnCodeString = "MHZ19_NO_MEASSURING_AVAILABLE - No results are received from the sensor";
		case MHZ19_NO_SERIAL: returnCodeString = "MHZ19_NO_SERIAL - No serial driver is specified";
		case MHZ19_PPM_MUST_BE_GT_999: returnCodeString = "MHZ19_PPM_MUST_BE_GT_999 - Span calibration is only allowed from ppm >= 1000";
	}
	printf("RETURNCODE: %s \n", returnCodeString);
}
