/*
 * ServoController.h
 *
 *  Github: https://github.com/Remote-Greenhouse-Monitoring-System/IoT
 *  Author: Christopher, Himal, Juraj
 */

#pragma once

#include <rc_servo.h>

void initialise_rc_servo();
void servo_set_position(uint8_t servoNo, int8_t percent);