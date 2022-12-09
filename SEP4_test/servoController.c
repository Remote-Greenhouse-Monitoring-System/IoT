/*
 * servoController.c
*  Git: https://github.com/Remote-Greenhouse-Monitoring-System/IoT
*  Authors: Christopher, Himal, Jurin
*/

#include "servoController.h"
#include "rc_servo.h"

void servoController_craete(){
	rc_servo_initialise();
}

void servoController_setPosition(uint8_t servoNo, int8_t percent){
	rc_servo_setPosition(servoNo, percent);
}