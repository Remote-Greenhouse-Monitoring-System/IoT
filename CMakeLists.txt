cmake_minimum_required(VERSION 3.23)
project(IoT C)

set(CMAKE_C_STANDARD 11)

include_directories(SEP4_test/drivers)
include_directories(SEP4_test/FreeRTOS/FreeRTOSTraceDriver)
include_directories(SEP4_test/FreeRTOS/src)

add_executable(IoT
        SEP4_test/drivers/docs/example/loraWANHandler.c
        SEP4_test/drivers/docs/example/main.c
        SEP4_test/drivers/display_7seg.h
        SEP4_test/drivers/fifo.h
        SEP4_test/drivers/FreeRTOSTraceDriver.h
        SEP4_test/drivers/hcSr501.h
        SEP4_test/drivers/hih8120.h
        SEP4_test/drivers/lora_driver.h
        SEP4_test/drivers/lora_driver_utils.h
        SEP4_test/drivers/mh_z19.h
        SEP4_test/drivers/rc_servo.h
        SEP4_test/drivers/sen14262.h
        SEP4_test/drivers/serial.h
        SEP4_test/drivers/spi_iha.h
        SEP4_test/drivers/status_leds.h
        SEP4_test/drivers/stdio_driver.h
        SEP4_test/drivers/tsl2591.h
        SEP4_test/drivers/twi.h
        SEP4_test/FreeRTOS/FreeRTOSTraceDriver/FreeRTOSTraceDriver.c
        SEP4_test/FreeRTOS/FreeRTOSTraceDriver/FreeRTOSTraceDriver.h
        SEP4_test/FreeRTOS/src/ATMEGA_FreeRTOS.h
        SEP4_test/FreeRTOS/src/atomic.h
        SEP4_test/FreeRTOS/src/croutine.c
        SEP4_test/FreeRTOS/src/croutine.h
        SEP4_test/FreeRTOS/src/event_groups.c
        SEP4_test/FreeRTOS/src/event_groups.h
        SEP4_test/FreeRTOS/src/FreeRTOSConfig.h
        SEP4_test/FreeRTOS/src/FreeRTOSVariant.h
        SEP4_test/FreeRTOS/src/heap_4.c
        SEP4_test/FreeRTOS/src/list.c
        SEP4_test/FreeRTOS/src/list.h
        SEP4_test/FreeRTOS/src/message_buffer.h
        SEP4_test/FreeRTOS/src/mpu_wrappers.h
        SEP4_test/FreeRTOS/src/port.c
        SEP4_test/FreeRTOS/src/portable.h
        SEP4_test/FreeRTOS/src/portmacro.h
        SEP4_test/FreeRTOS/src/projdefs.h
        SEP4_test/FreeRTOS/src/queue.c
        SEP4_test/FreeRTOS/src/queue.h
        SEP4_test/FreeRTOS/src/semphr.h
        SEP4_test/FreeRTOS/src/stack_macros.h
        SEP4_test/FreeRTOS/src/stream_buffer.c
        SEP4_test/FreeRTOS/src/stream_buffer.h
        SEP4_test/FreeRTOS/src/task.h
        SEP4_test/FreeRTOS/src/tasks.c
        SEP4_test/FreeRTOS/src/timers.c
        SEP4_test/FreeRTOS/src/timers.h
        SEP4_test/FreeRTOS/src/variantHooks.c
        SEP4_test/LoRaWANHandler.c
        SEP4_test/Application.c
        SEP4_test/DriverConnection/CO2Sensor.c
        SEP4_test/DriverConnection/TempHumSensor.c
        SEP4_test/main.c "SEP4_test/application.h")
