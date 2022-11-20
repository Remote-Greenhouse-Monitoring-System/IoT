/*
 * TempHumSensor.c
 *
 * Created: 11/20/2022 3:19:03 PM
 *  Author: himal
 */ 


#include "TempHumSensor.h"


static uint16_t humidity = 0.0;
static temperature = 0.0;


void initialise_TempHumSensor(){
	if ( HIH8120_OK == hih8120_initialise() )
	{
		printf("Initialised  tempHum sensor");
		// Driver initialised OK
		// Always check what hih8120_initialise() returns
		
	}else{printf("Something went wrong while initialising tempHum sensor");}
}

void create_TempHumSensorTask(){
	initialise_TempHumSensor();
	
	xTaskCreate(Temp_Hum_Main_Task,
	"TempHumTask",
	configMINIMAL_STACK_SIZE,
	NULL,
	tskIDLE_PRIORITY,
	NULL);
	
}

void measure_Temp_Hum(){
	
	
	if ( HIH8120_OK != hih8120_wakeup() )
	{
		printf("Could not wake up temp hum sensor ");
		// Something went wrong
		// Investigate the return code further
	}
	vTaskDelay(pdMS_TO_TICKS(51));
	if ( HIH8120_OK !=  hih8120_measure() )
	{
		printf("Could not measure temp hum sensor ");
		// Something went wrong
		// Investigate the return code further
	}
	vTaskDelay(pdMS_TO_TICKS(51))
	
	
}
	
uint16_t TempHumSensor_getTemp(){
	return temperature;
}
	
uint16_t TempHumSensor_getHum(){
	return humidity;
}


void Temp_Hum_Main_Task(){
	
	while(1){
		EventBits_t uxBits = xEventGroupWaitBits(meassureEventGroup,TEMP_HUM_MEASSURE_BIT,pdTRUE,pdTRUE,portMAX_DELAY);
		
		if (uxBits &(TEMP_HUM_MEASSURE_BIT))
		{
			measure_Temp_Hum();
			humidity = hih8120_getHumidityPercent_x10();
			temperature = hih8120_getTemperature_x10();
			printf("Measuring done for temp and hum");
			
			
			//After everything is done just setting 1 to ready bit so its now unblocked 
			xEventGroupSetBits(dataReadyEventGroup,TEMP_HUM_READY_BIT);
			
			//vTaskDelay(pdMS_TO_TICKS(51));
			
			
		}
	}
}