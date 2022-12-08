#include "TempHumSensor.h"

uint16_t humidity = 0;
int16_t temperature = 0;

void initialise_TempHumSensor()
{
	if (HIH8120_OK == hih8120_initialise())
	{
		// printf("Initialised  tempHum sensor");
		// Driver initialised OK
		// Always check what hih8120_initialise() returns
	}
	else
	{
		printf("Something went wrong while initialising tempHum sensor");
	}
}


void create_TempHum_sensor_task(UBaseType_t priority) {
	initialise_TempHumSensor();

	xTaskCreate(Temp_Hum_Main_Task,
		"TempHumTask",
		configMINIMAL_STACK_SIZE,
		NULL,
		0 + priority,
		NULL);

}

void measure_Temp_Hum()
{
	if (HIH8120_OK != hih8120_wakeup())
	{
		printf("Could not wake up temp hum sensor ");
		// Something went wrong
		// Investigate the return code further
	}
	vTaskDelay(pdMS_TO_TICKS(51));
	if (HIH8120_OK != hih8120_measure())
	{
		printf("Could not measure temp hum sensor ");
		// Something went wrong
		// Investigate the return code further
	}
	vTaskDelay(pdMS_TO_TICKS(51));
	
}

int16_t TempHumSensor_getTemp()
{
	return temperature;
}

uint16_t TempHumSensor_getHum()
{
	return humidity;
}


void RunTemp_Hum_Main_Task()
{
		EventBits_t uxBits = xEventGroupWaitBits(measureEventGroup, TEMP_HUM_MEASURE_BIT, pdTRUE, pdTRUE, portMAX_DELAY);

		if (uxBits & (TEMP_HUM_MEASURE_BIT))
		{
			measure_Temp_Hum();
			humidity = hih8120_getHumidityPercent_x10();
			temperature = hih8120_getTemperature_x10();

			//After everything is done just setting 1 to ready bit so its now unblocked 
			xEventGroupSetBits(dataReadyEventGroup, TEMP_HUM_READY_BIT);

			//vTaskDelay(pdMS_TO_TICKS(51));
		}
}

void Temp_Hum_Main_Task()
{
	while (1)
	{
		RunTemp_Hum_Main_Task();
	}
}