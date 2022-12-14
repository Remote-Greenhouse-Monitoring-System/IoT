/*
 * lightSensor.c
 *
 * Created: 12/12/2022 18.02.50
 *  Author: jurin
 */ 

#include "lightSensor.h"

static float lux = 0.0;


void light_sensor_measure();
void tsl2591Callback(tsl2591_returnCode_t rc);
void measure_light_task(void *pvParameters);

void initialize_light_sensor(){
	if(TSL2591_OK == tsl2591_initialise(tsl2591Callback)){
		if(TSL2591_OK != tsl2591_enable()){
			printf("Couldn't power up light sensor.\n");
		}
	}
	else{
		printf("Couldn't initialize light sensor.\n");
	}
}

void tsl2591Callback(tsl2591_returnCode_t rc)
{
	float _lux;
	switch (rc)
	{
		case TSL2591_DATA_READY:
		
		if ( TSL2591_OK == (rc = tsl2591_getLux(&_lux)) )
		{
			lux = _lux;
		}
		else if( TSL2591_OVERFLOW == rc )
		{
			printf("Lux overflow - change gain and integration time\n");
		}
		break;
		
		case TSL2591_OK:
		// Last command performed successful
		break;
		
		case TSL2591_DEV_ID_READY:
		// Dev ID now fetched
		break;
		
		default:
		break;
	}
}

void light_sensor_measure(){
	if (TSL2591_OK != tsl2591_fetchData()){
		printf("Couldn't fetch data from light sensor.\n");
	}
}

float light_sensor_get_lux(){
	return lux;
}

void create_light_sensor_task(UBaseType_t priority){
	
	initialize_light_sensor();
	
	xTaskCreate(
	measure_light_task,
	"MeasureLight",
	configMINIMAL_STACK_SIZE,
	NULL,
	0 + priority,
	NULL);
}

void measure_light_task(void *pvParameters){
	for(;;){
		measure_light_task_inline();
	}
}

inline void measure_light_task_inline() {

	EventBits_t uxBits = xEventGroupWaitBits(measureEventGroup, LIGHT_MEASURE_BIT, pdTRUE, pdTRUE, portMAX_DELAY);

	if ((uxBits & (LIGHT_MEASURE_BIT)) == LIGHT_MEASURE_BIT) {
		light_sensor_measure();
		vTaskDelay(pdMS_TO_TICKS(100));
		xEventGroupSetBits(dataReadyEventGroup, LIGHT_READY_BIT);
	}
}
