#include "co2Sensor.h"

uint16_t lastCO2ppm = 0;
mh_z19_returnCode_t rc;

typedef void(*myCo2CallBacka) (uint16_t);

void MeasureCo2Task();


void CO2_createSensor() {
	// The parameter is the USART port the MH-Z19 sensor is connected to - in this case USART3
	

	//Note
	//If FreeRTOS is used then the initialise function Initialise the driver must be called before
	//	vTaskStartScheduler()
	//is called.

	mh_z19_initialise(ser_USART3);

	//If it is wanted to inject a call-back function, then it must be done like this
	mh_z19_injectCallBack(myCo2CallBack);
}


void myCo2CallBack(uint16_t ppm_parameter)
{
	// Here you can use the CO2 ppm value
	lastCO2ppm = ppm_parameter;

}

void CO2_measure() {
	//Driver must be initialized before

	rc = mh_z19_takeMeassuring();
	if (rc != MHZ19_OK)
	{
		// Something went wrong
		printf("  Something went wrong while measuring CO2!!!  \n");

	}
	lastCO2ppm = mh_z19_getCo2Ppm(&lastCO2ppm);
}

uint16_t CO2_getPPM() {
	return lastCO2ppm;
}



//To start the task and get measurement , calling it from Application and need to initialize c02 before starting task
void create_CO2_sensor_task(UBaseType_t priority){
	
	//Initializing 
		CO2_createSensor();
	
	//Starting task
		xTaskCreate(
		MeasureCo2Task,
		"MeasuringCO2_Task",
		configMINIMAL_STACK_SIZE,
		NULL,
		0 + priority,
		NULL);
}


void MeasureCo2Task(){
	//printf("Measurement of co2 task has been started ");

		//Usage of Event group Wait fun until co2 measure bit is set to 1 
		
		EventBits_t uxBits = xEventGroupWaitBits(measureEventGroup,CO2_MEASURE_BIT,pdTRUE,pdTRUE,portMAX_DELAY);
		
			if ((uxBits & (CO2_MEASURE_BIT)) == CO2_MEASURE_BIT)
			{
				//printf("Measure bit and event bit was successfully checked ");
				
				CO2_measure();
				
				//printf("Measurement successful , now time to set ready bit of c02 ");
				vTaskDelay(pdMS_TO_TICKS(100));
				xEventGroupSetBits(dataReadyEventGroup,CO2_READY_BIT);
			}
	
}

void runMeasureCo2Task()
{
	while (1)
	{
		MeasureCo2Task();
	}
}
