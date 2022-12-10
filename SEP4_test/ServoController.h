/*
 * servoController.h
*  Git: https://github.com/Remote-Greenhouse-Monitoring-System/IoT
*  Authors: Christopher, Himal, Jurin
*/


#pragma once

#include <stdint.h>

void servoController_create();
void servoController_setPosition(uint8_t servoNo, int8_t percent);