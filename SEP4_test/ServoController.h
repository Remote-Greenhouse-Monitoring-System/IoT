/*
 * ServoController.h
 *
 * Created: 08/12/2022 22.33.05
 *  Author: jurin
 */ 

#pragma once

#include <rc_servo.h>

void initialise_rc_servo();
void servo_set_position(uint8_t servoNo, int8_t percent);