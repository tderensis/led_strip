/*
@file led_strip_arduino_spi_backend.h

@brief Header file for the Arduino SPI backend.
*/
#ifndef LED_STRIP_ARDUINO_SPI_BACKEND_H
#define LED_STRIP_ARDUINO_SPI_BACKEND_H

#include "led_strip-cpp.h"

class LedStripArduinoSpi : public LedStrip
{
public:
    LedStripArduinoSpi(uint32_t frequency, uint32_t num_leds);
private:

};

#endif
