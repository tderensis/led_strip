
#ifndef LED_STRIP_LINUX_SPI_BACKEND_H
#define LED_STRIP_LINUX_SPI_BACKEND_H

#include "led_strip.h"

led_strip_t * led_strip_create_linux_spi(const char * device,
                                         uint32_t frequency,
                                         uint32_t num_leds);
#endif
