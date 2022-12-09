/*
 * ServoControllerImpl.c
 *
 * Created: 08/12/2022 22.35.11
 *  Author: jurin
 */ 

#include "ServoController.h"

void initialise_rc_servo(){
	rc_servo_initialise();
}
void servo_set_position(uint8_t servoNo, int8_t percent){
	rc_servo_setPosition(servoNo, percent);
}
