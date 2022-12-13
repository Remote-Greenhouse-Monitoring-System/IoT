/*
 * FanController.c
 *
 * Created: 06/12/2022 21.18.14
 *  Author: jurin
 */ 

#include "actionsController.h"



void actions_controller_task(void *pvParameters);
void temperature_action(int16_t currentTemp, int16_t thresholdTemp);
void humidity_action(uint16_t currentHum, uint16_t thresholdHum);
void co2_action(uint16_t currentCO2, uint16_t thresholdCO2);

void create_actions_controller_task(UBaseType_t priority){
	
	DDRA = 0xFF;
	PORTA = 0xFF;
	
	xTaskCreate(
	actions_controller_task
	,  "FanController"
	,  configMINIMAL_STACK_SIZE
	,  NULL
	,  tskIDLE_PRIORITY + priority
	,  NULL );
}

void actions_controller_task(void *pvParameters) {
	
	int16_t currentTemperature = 0;
	int16_t thresholdTemperature = 0;
	uint16_t currentHumidity = 0;
	uint16_t thresholdHumidity = 0;
	uint16_t currentCO2 = 0;
	uint16_t thresholdCO2 = 0;
	float currentLight = 0;
	
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = pdMS_TO_TICKS(60000); 
// 	const TickType_t xFrequency = pdMS_TO_TICKS(5000);

	xLastWakeTime = xTaskGetTickCount();
	
	for(;;)
	{
		xTaskDelayUntil( &xLastWakeTime, xFrequency );
		

		if(xSemaphoreTake(configSemaphore, (TickType_t) 10 ) == pdTRUE){
			thresholdTemperature = get_max_temperature();
			thresholdHumidity = get_max_humidity();
			thresholdCO2 = get_max_co2();
			xSemaphoreGive(configSemaphore);
			}
			
		xEventGroupSetBits(measureEventGroup, ALL_MEASURE_BITS);		
		EventBits_t uxBits = xEventGroupWaitBits(dataReadyEventGroup,ALL_READY_BITS,pdTRUE,pdTRUE,portMAX_DELAY);
				
		if (uxBits&(ALL_READY_BITS)){
			currentTemperature = TempHumSensor_getTemp();
			currentHumidity = TempHumSensor_getHum();
			currentCO2 = CO2_getPPM();
			currentLight = light_sensor_get_lux();
			printf("CURR/THRS: tmp %d/%dC, hum %d/%d%%, co2 %d/%dppm, (light %5.2flux)\n", 
			currentTemperature/10, thresholdTemperature, currentHumidity/10, thresholdHumidity, currentCO2, thresholdCO2, currentLight);
			
			if(!(thresholdTemperature == 0 && thresholdHumidity == 0 && thresholdCO2 == 0)){
				if(xSemaphoreTake(configSemaphore, (TickType_t) 10 ) == pdTRUE){
					temperature_action(currentTemperature, thresholdTemperature);
					humidity_action(currentHumidity, thresholdHumidity);
					co2_action(currentCO2, thresholdCO2);
					printf("status: %x\n", get_system_status());
					xSemaphoreGive(configSemaphore);
				}
			}
			else{
				printf("No config yet.\n");
			}	
		}
	}
}

void temperature_action(int16_t currentTemp, int16_t thresholdTemp){
	if(currentTemp/10 > thresholdTemp){
		servo_set_position(0, 100);
		PORTA &= ~(1 << 0);
		set_system_status(TEMPERATURE_ACTION_ON);
	}
	else{
		servo_set_position(0, -100);
		PORTA |= (1 << 0);
		set_system_status(TEMPERATURE_ACTION_OFF);
	}
}
void humidity_action(uint16_t currentHum, uint16_t thresholdHum){
	if(currentHum/10 > thresholdHum){
		PORTA &= ~(1 << 1);
		set_system_status(HUMIDITY_ACTION_ON);
	}
	else{
		PORTA |= (1 << 1);
		set_system_status(HUMIDITY_ACTION_OFF);
	}
}
void co2_action(uint16_t currentCO2, uint16_t thresholdCO2){
	if(currentCO2 > thresholdCO2){
		PORTA &= ~(1 << 2);
		set_system_status(CO2_ACTION_ON);
	}
	else{
		PORTA |= (1 << 2);
		set_system_status(CO2_ACTION_OFF);
	}
}