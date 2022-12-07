
#include "CO2Sensor.h"

uint16_t lastCO2ppm = 0;

uint16_t CO2_getPPM()
{
	return lastCO2ppm;
}

void MeasureCo2Task()
{
	//printf("Measurement of co2 task has been started ");

		//Usage of Event group Wait fun until co2 measure bit is set to 1 

		EventBits_t uxBits = xEventGroupWaitBits(measureEventGroup, CO2_MEASURE_BIT, pdTRUE, pdTRUE, portMAX_DELAY);

		if ((uxBits & (CO2_MEASURE_BIT)) == CO2_MEASURE_BIT)
		{
			//printf("Measure bit and event bit was successfully checked ");

			//CO2_measure();

			//printf("Measurement successful , now time to set ready bit of c02 ");

			xEventGroupSetBits(dataReadyEventGroup, CO2_READY_BIT);

			//vTaskDelay(pdMS_TO_TICKS(100));
		}
	
}

void createCO2SensorTask()
{
	while (1)
	{
		MeasureCo2Task();
	}
}
