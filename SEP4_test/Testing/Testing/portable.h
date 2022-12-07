#pragma once
#include "FreeRTOS.h"

void* pvPortMalloc(size_t xSize);
void vPortFree(void*);
