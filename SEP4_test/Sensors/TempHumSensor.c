/*
 * TempHumSensor.c
 *
 * Created: 11/20/2022 3:19:03 PM
 *  Author: himal
 */ 

#include "TempHumSensor.h"


uint16_t humidity = 0;
int16_t temperature = 0;

void Temp_Hum_Main_Task(void *pvParameters);


void initialise_TempHumSensor()
{
	if ( HIH8120_OK == hih8120_initialise() )
	{
	//	printf("Initialised  tempHum sensor");
		// Driver initialised OK
		// Always check what hih8120_initialise() returns
		
	}
	else 
	{
		printf("Something went wrong while initialising tempHum sensor");
	}
}


void create_TempHum_sensor_task(UBaseType_t priority){
	initialise_TempHumSensor();
	
	xTaskCreate(Temp_Hum_Main_Task,
	"TempHumTask",
	configMINIMAL_STACK_SIZE,
	NULL,
	tskIDLE_PRIORITY + priority,
	NULL);
	
}

void measure_Temp_Hum(){
	
	if ( HIH8120_OK != hih8120_wakeup() )
	{
		printf("Could not wake up temp hum sensor \n");
		// Something went wrong
		// Investigate the return code further
	}
	vTaskDelay(pdMS_TO_TICKS(60));
	int16_t returnCode = hih8120_measure();
	char* returnCodeString;
	switch(returnCode){
		case HIH8120_OK: returnCodeString = "HIH8120_OK";												/**< Everything went well */
		case HIH8120_OUT_OF_HEAP: returnCodeString = "HIH8120_OUT_OF_HEAP";								/**< Not enough heap to initialise the driver */
		case HIH8120_DRIVER_NOT_INITIALISED: returnCodeString = "HIH8120_DRIVER_NOT_INITIALISED";		/**< Driver must be initialise before use */
		case HIH8120_TWI_BUSY: returnCodeString = "HIH8120_TWI_BUSY";									/**< The two wire/I2C interface is busy */
	}
	
	if ( returnCode != HIH8120_OK  )
	{
		printf("Could not measure temp hum sensor, code: %s \n", returnCodeString);
		// Something went wrong
		// Investigate the return code further
	}
	vTaskDelay(pdMS_TO_TICKS(50));
	
	int count = 0;
	
	while(!hih8120_isReady || count < 5)
	{
		vTaskDelay(pdMS_TO_TICKS(50));
	}
		humidity = hih8120_getHumidityPercent_x10();
		temperature = hih8120_getTemperature_x10();
		count = 0;
}
	
int16_t TempHumSensor_getTemp(){
	return temperature;
}
	
uint16_t TempHumSensor_getHum(){
	return humidity;
}



void Temp_Hum_Main_Task(void *pvParameters){
	
	while(1){
		EventBits_t uxBits = xEventGroupWaitBits(measureEventGroup,TEMP_HUM_MEASURE_BIT,pdTRUE,pdTRUE,portMAX_DELAY);
		
		if (uxBits &(TEMP_HUM_MEASURE_BIT))
		{
			measure_Temp_Hum();			
			//After everything is done just setting 1 to ready bit so its now unblocked 
			xEventGroupSetBits(dataReadyEventGroup,TEMP_HUM_READY_BIT);
			
			//vTaskDelay(pdMS_TO_TICKS(51));
			
		}
	}
}