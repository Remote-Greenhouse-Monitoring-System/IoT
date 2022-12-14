#include "actionsController.h"

void fan_controller_task(void* pvParameters);
void temperature_action(int16_t currentTemp, int16_t thresholdTemp);
void humidity_action(uint16_t currentHum, uint16_t thresholdHum);
void co2_action(uint16_t currentCO2, uint16_t thresholdCO2);

static int16_t currentTemperature = 0;
static int16_t thresholdTemperature = 0;
static uint16_t currentHumidity = 0;
static uint16_t thresholdHumidity = 0;
static uint16_t currentCO2 = 0;
static uint16_t thresholdCO2 = 0;

TickType_t xLastWakeTime;
const TickType_t xFrequency = pdMS_TO_TICKS(5000);

void create_fan_controller_task(UBaseType_t priority) {

	//DDRA = 0xFF;
	//PORTA = 0xFF;

	xTaskCreate(
		fan_controller_task
		, "FanController"
		, configMINIMAL_STACK_SIZE
		, NULL
		, 0 + priority
		, NULL);
}

void fan_controller_task_init()
{
	currentTemperature = 0;
	thresholdTemperature = 0;
	currentHumidity = 0;
	thresholdHumidity = 0;
	currentCO2 = 0;
	thresholdCO2 = 0;

	xLastWakeTime = xTaskGetTickCount();
}

void fan_controller_task_run()
{
	xTaskDelayUntil(&xLastWakeTime, xFrequency);


	if (xSemaphoreTake(configSemaphore, (TickType_t)10) == pdTRUE) {
		thresholdTemperature = get_max_temperature();
		thresholdHumidity = get_max_humidity();
		thresholdCO2 = get_max_co2();
		xSemaphoreGive(configSemaphore);
	}

	xEventGroupSetBits(measureEventGroup, ALL_MEASURE_BITS);
	EventBits_t uxBits = xEventGroupWaitBits(dataReadyEventGroup, ALL_READY_BITS, pdTRUE, pdTRUE, portMAX_DELAY);

	if (uxBits & (ALL_READY_BITS)) {
		currentTemperature = TempHumSensor_getTemp();
		currentHumidity = TempHumSensor_getHum();
		currentCO2 = CO2_getPPM();
		printf("CURR/THRS: tmp %d/%d, hum %d/%d, co2ppm %d/%d\n",
			currentTemperature / 10, thresholdTemperature, currentHumidity / 10, thresholdHumidity, currentCO2, thresholdCO2);

		if (!(thresholdTemperature == 0 && thresholdHumidity == 0 && thresholdCO2 == 0)) {
			if (xSemaphoreTake(configSemaphore, (TickType_t)10) == pdTRUE) {
				temperature_action(currentTemperature, thresholdTemperature);
				humidity_action(currentHumidity, thresholdHumidity);
				co2_action(currentCO2, thresholdCO2);
				printf("status: %x\n", get_system_status());
				xSemaphoreGive(configSemaphore);
			}
		}
		else {
			printf("No config yet.\n");
		}
	}
}

void fan_controller_task(void* pvParameters) {
	 fan_controller_task_init();
	for (;;)
	{
		fan_controller_task_run();
	}
}

void temperature_action(int16_t currentTemp, int16_t thresholdTemp) {
	if (currentTemp / 10 > thresholdTemp) {
		servo_set_position(0, 100);
		//PORTA &= ~(1 << 0);
		set_system_status(TEMPERATURE_ACTION_ON);
	}
	else {
		servo_set_position(0, -100);
		//PORTA |= (1 << 0);
		set_system_status(TEMPERATURE_ACTION_OFF);
	}
}
void humidity_action(uint16_t currentHum, uint16_t thresholdHum) {
	if (currentHum / 10 > thresholdHum) {
		//PORTA &= ~(1 << 1);
		set_system_status(HUMIDITY_ACTION_ON);
	}
	else {
		//PORTA |= (1 << 1);
		set_system_status(HUMIDITY_ACTION_OFF);
	}
}
void co2_action(uint16_t currentCO2, uint16_t thresholdCO2) {
	if (currentCO2 > thresholdCO2) {
		//PORTA &= ~(1 << 2);
		set_system_status(CO2_ACTION_ON);
	}
	else {
		//PORTA |= (1 << 2);
		set_system_status(CO2_ACTION_OFF);
	}
}