#pragma once

#include "../TestFiles/rc_servo.h"

void initialise_rc_servo();
void servo_set_position(uint8_t servoNo, int8_t percent);