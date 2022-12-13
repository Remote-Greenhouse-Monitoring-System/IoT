#include "tempHumSensor.h"


uint16_t humidity = 0;
int16_t temperature = 0;

void Temp_Hum_Main_Task();
void tempHumSensor_printReturnCode(hih8120_driverReturnCode_t rc);

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
		printf("Something went wrong while initialising tempHum sensor\n");
	}
}

void create_TempHum_sensor_task(UBaseType_t priority){
	initialise_TempHumSensor();
	
	xTaskCreate(
	Temp_Hum_Main_Task,
	"TempHumTask",
	configMINIMAL_STACK_SIZE,
	NULL,
	0 + priority,
	NULL);
	
}

void measure_Temp_Hum(){
	
	if ( HIH8120_OK != hih8120_wakeup() )
	{
		printf("Could not wake up temp hum sensor\n");
		// Something went wrong
		// Investigate the return code further
	}

	vTaskDelay(pdMS_TO_TICKS(60));
	
	hih8120_driverReturnCode_t measure_rc = hih8120_measure();
	if (measure_rc != HIH8120_OK)
	{
		tempHumSensor_printReturnCode(measure_rc);
	}
	vTaskDelay(pdMS_TO_TICKS(50));
	
	humidity = hih8120_getHumidityPercent_x10();
	temperature = hih8120_getTemperature_x10();	
}

void tempHumSensor_printReturnCode(hih8120_driverReturnCode_t rc)
{
	char* returnCodeString;
	switch(rc){
	case 0: returnCodeString = "HIH8120_OK"; break;
		case 1: returnCodeString = "HIH8120_OUT_OF_HEAP"; break;
		case 2: returnCodeString = "HIH8120_DRIVER_NOT_INITIALISED"; break;
		case 3: returnCodeString = "HIH8120_TWI_BUSY---"; break;
	}
	printf("RETURNCODE: %s \n", returnCodeString);
}
	
int16_t TempHumSensor_getTemp(){
	return temperature;
}
	
uint16_t TempHumSensor_getHum(){
	return humidity;
}

void Temp_Hum_Main_Task(){
		EventBits_t uxBits = xEventGroupWaitBits(measureEventGroup,TEMP_HUM_MEASURE_BIT,pdTRUE,pdTRUE,portMAX_DELAY);		
		if (uxBits &(TEMP_HUM_MEASURE_BIT))
		{
			measure_Temp_Hum();			
			//After everything is done just setting 1 to ready bit so its now unblocked 
			xEventGroupSetBits(dataReadyEventGroup,TEMP_HUM_READY_BIT);
			//vTaskDelay(pdMS_TO_TICKS(51));
		}
}

void runTemp_Hum_Main_Task()
{
	while (1)
	{
		Temp_Hum_Main_Task();
	}
}