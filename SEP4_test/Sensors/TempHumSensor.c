/*
* TempHumSensor.c
*
* Created: 11/20/2022 3:19:03 PM
*  Author: himal, Christopher
*/

#include "TempHumSensor.h"

//Initializing temperature and humidity as 0. 
uint16_t humidity = 0;
int16_t temperature = 0;

void tempHumSensor_task(void* pvpParameter);

//Initializes the temperature and humidity sensor driver and creates the temperature and humidity task.
void tempHumSensor_create(UBaseType_t priority)
{
	tempHumSensor_initialise();
	tempHumSensor_createTask(priority);
}
//Getter for temperature.
int16_t tempHumSensor_getTemp(){
	return temperature;
}
//Getter for humidity.
uint16_t tempHumSensor_getHum(){
	return humidity;
}

//Initializes the temperature and humidity sensor driver and prints the return code.
void tempHumSensor_initialise()
{
	hih8120_driverReturnCode_t rc = hih8120_initialise();
	
	if (rc != HIH8120_OK)
	{
		printf("ERROR: Initializing temperature & Humidity Sensor, ");
		tempHumSensor_printReturnCode(rc);
	}
	else
	{
		printf("--->Initialized, Temperature & Humidity Sensor<---");
	}
}


//Measures the temperature and humidity.
void tempHumSensor_measure(){
	//waking up the sensor and getting return code.
	hih8120_driverReturnCode_t wakeup_rc = hih8120_wakeup();
	
	//checking return code and printing result.
	if (wakeup_rc != HIH8120_OK)
	{
		printf("ERROR: Waking temperature & Humidity Sensor up, ");
		tempHumSensor_printReturnCode(wakeup_rc);
	}
	else
	{
		printf("--->Woke Temperature & Humidity Sensor up<---");
	}
	
	//note: After the hih8120_wakeup() call the sensor will need minimum 50 ms to be ready! 
	vTaskDelay(pdMS_TO_TICKS(100));
	
	//waking up the sensor and getting return code.
	hih8120_driverReturnCode_t measure_rc = hih8120_measure();
	
	//checking return code and printing result.
	if (measure_rc != HIH8120_OK)
	{
		printf("ERROR: Temperature & Humidity Sensor could not measure, ");
		tempHumSensor_printReturnCode(measure_rc);
	}
	else
	{
		printf("--->Temperature & Humidity Sensor done measuring<---");
	}
	
	//note: After the hih8120_measure() call the two wire inteface (TWI) will need minimum 1 ms to fetch the results from the sensor!  
	vTaskDelay(pdMS_TO_TICKS(50));
	
	//Checking if sensor is ready to return measurements.
	if (hih8120_isReady())
	{
		printf("--->HIH8120 is Ready.<---");
			humidity = hih8120_getHumidityPercent_x10();
			printf("--->Humidity Set.<---");
			temperature = hih8120_getTemperature_x10();
			printf("--->Temperature Set.<---");
	}
}

// Creates the temperature and humidity task.
void tempHumSensor_createTask(UBaseType_t priority){
	xTaskCreate(tempHumSensor_task,
	"TempHumTask",
	configMINIMAL_STACK_SIZE,
	NULL,
	tskIDLE_PRIORITY + priority,
	NULL);
}

//The temperature and humidity task.
void tempHumSensor_task(void* pvpParameter){
	while (1)
	{
	EventBits_t uxBits = xEventGroupWaitBits(measureEventGroup,TEMP_HUM_MEASURE_BIT,pdTRUE,pdTRUE,portMAX_DELAY);
	if (uxBits &(TEMP_HUM_MEASURE_BIT))
	{
		tempHumSensor_measure();
		//After everything is done just setting 1 to ready bit so its now unblocked
		xEventGroupSetBits(dataReadyEventGroup,TEMP_HUM_READY_BIT);
		//vTaskDelay(pdMS_TO_TICKS(51));
	}}
}


//Prints a formatted return code.
void tempHumSensor_printReturnCode(hih8120_driverReturnCode_t rc)
{
	char* returnCodeString;
	switch(rc){
		case HIH8120_OK: returnCodeString = "HIH8120_OK - Everything went well ";												
		case HIH8120_OUT_OF_HEAP: returnCodeString = "HIH8120_OUT_OF_HEAP - Not enough heap to initialize the driver";								
		case HIH8120_DRIVER_NOT_INITIALISED: returnCodeString = "HIH8120_DRIVER_NOT_INITIALISED - Driver must be initialize before use";		
		case HIH8120_TWI_BUSY: returnCodeString = "HIH8120_TWI_BUSY - The two wire/I2C interface is busy";									
	}
	printf("RETURNCODE: %s \n", returnCodeString);
}