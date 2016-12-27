/*!
  @file led_strip_no_backend.h

  All backends should include this file for the create function. 
*/
#ifndef LED_STRIP_NO_BACKEND_H
#define LED_STRIP_NO_BACKEND_H

#include "led_strip.h"

#define HEADER_LENGTH_IN_BYTES 4

led_strip_t * led_strip_create_no_backend(uint32_t num_leds);

void led_strip_destroy_no_backend(led_strip_t * led_strip);
#endif
