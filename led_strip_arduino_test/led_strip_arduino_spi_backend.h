/*
@file led_strip_arduino_spi_backend.h

@brief Header file for the Arduino SPI backend.
*/
#ifndef LED_STRIP_ARDUINO_SPI_BACKEND_H
#define LED_STRIP_ARDUINO_SPI_BACKEND_H

#include "led_strip.h"

led_strip_t * led_strip_create_arduino_spi(uint32_t ss_pin,
                                           uint32_t frequency,
                                           uint32_t num_leds);
#endif
