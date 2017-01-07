/*!
  @file led_strip_no_backend.h

  All backends should include this file for the create function. 
*/
#ifndef LED_STRIP_NO_BACKEND_H
#define LED_STRIP_NO_BACKEND_H

#include "led_strip.h"

/*
@brief Initialize the led strip without the backend. Every backend
       should call this to create the led strip object.

@param num_leds The number of LEDs in the strip
@return A pointer to the allocated led strip object
*/
led_strip_t * led_strip_create_no_backend(uint32_t num_leds);

/*
@brief Destroy the led strip object. Must be called after the
       backend is destroyed.

@param led_strip The led strip object
*/
void led_strip_destroy_no_backend(led_strip_t * led_strip);

#endif
