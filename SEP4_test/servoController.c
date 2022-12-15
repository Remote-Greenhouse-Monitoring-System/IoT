/*
 *  Github: https://github.com/Remote-Greenhouse-Monitoring-System/IoT
 *  Author: Christopher, Himal, Juraj
 */

#include "servoController.h"

void initialise_rc_servo(){
	rc_servo_initialise();
}
void servo_set_position(uint8_t servoNo, int8_t percent){
	rc_servo_setPosition(servoNo, percent);
}
