/*
 * Application.c
 *
 * Created: 11/20/2022 2:27:49 PM
 *  Author: himal
 */ 
#include <ATMEGA_FreeRTOS.h>
#include <stdio.h>

#include "Application.h"

EventGroupHandle_t meassureEventGroup;
EventGroupHandle_t dataReadyEventGroup;

void run_all_Task() 
{
	createCO2SensorTask();
	create_TempHumSensorTask();
	
	
	
}
void initialize_everything() {
	dataReadyEventGroup = xEventGroupCreate();
	meassureEventGroup = xEventGroupCreate();
	
}

void start_application() {
	
}

// Main task For application to get result when every measurnment is done

void MainApplicationTask() {
	
	printf ("Activate");
	
	puts("Application");
	//First trying to measure everything
	xEventGroupSetBits(meassureEventGroup,ALL_MEASSURE_BITS);
	
	printf("Measuring from sensor is done now ready bit are done ");
	
	EventBits_t uxBits = xEventGroupWaitBits(dataReadyEventGroup,ALL_READY_BITS,pdTRUE,pdTRUE,portMAX_DELAY);
	
	//If everything is done now we need to set the measurement and it's done 
	
	if (uxBits&(ALL_READY_BITS))
	{
		printf("Yahuuu !!! Everything is measured now setting the value from sensor");
		
		// set here what we need 
		printf("Temp is : %u",TempHumSensor_getTemp());
		printf("HUM is : %u",TempHumSensor_getHum());
		printf("co2 is : %u", CO2_getPPM());
		
		//I guess lorawan part goes here and then we need to repeat it again and again 
		
		//As of now 1 min
		vTaskDelay(pdMS_TO_TICKS(6000));
	}
	

}