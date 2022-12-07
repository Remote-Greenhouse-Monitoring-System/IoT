/*
 * LoraUtils.h
 *
 * Created: 05/12/2022 18.59.31
 *  Author: jurin
 */ 


#ifndef LORAUTILS_H_
#define LORAUTILS_H_
#include <message_buffer.h>
#include <ATMEGA_FreeRTOS.h>

void setUplinkMessageBufferHandle(MessageBufferHandle_t uplinkBufferHandle);


#endif /* LORAUTILS_H_ */