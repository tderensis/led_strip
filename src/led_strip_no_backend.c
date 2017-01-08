/*!
@file led_strip_no_backend.c

@brief Implementation file for the create function that is not specific to
       the backend
**/

#include "led_strip_no_backend.h"
#include "led_strip_struct.h"

#include <string.h> // for memset
#include <assert.h> // for assert
#include <stdlib.h> // for calloc


led_strip_t * led_strip_create_no_backend(uint32_t num_leds)
{
    assert(num_leds && "Enter a value > 0 for the number of LEDs.");

    led_strip_t * led_strip = (led_strip_t *) malloc(sizeof(led_strip_t));

    if (!led_strip) {
        goto led_strip_allocation_error;
    }

    led_strip->pixels = (uint32_t *) malloc(num_leds * sizeof(uint32_t));

    if (!led_strip->pixels) {
        goto led_strip_pixel_allocation_error;
    }

    // Header is all zeros
    led_strip->header_data = (uint8_t *) calloc(HEADER_LENGTH_IN_BYTES, 1);

    if (!led_strip->header_data) {
        goto led_strip_header_allocation_error;
    }

    // Datasheet says 32*1 bits for footer, but testing shows we must use
    // at least (num_leds + 1)/2 high values.
    led_strip->footer_len = (led_strip->num_leds + 15)/16;
    led_strip->footer_data = (uint8_t *) malloc(led_strip->footer_len);

    if (!led_strip->footer_data) {
        goto led_strip_footer_allocation_error;
    }

    // Footer is all ones
    memset(led_strip->footer_data, 0xFF, led_strip->footer_len);

    led_strip->num_leds = num_leds;

    // Make sure the led strip is off
    led_strip_clear(led_strip);

    return led_strip;

led_strip_footer_allocation_error:
    free(led_strip->header_data);
led_strip_header_allocation_error:
    free(led_strip->pixels);
led_strip_pixel_allocation_error:
    free(led_strip);
led_strip_allocation_error:
    return NULL;
}
