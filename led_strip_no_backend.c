
#include "led_strip_no_backend.h"
#include "led_strip_struct.h"

#include <string.h>
#include <stdio.h> // for printf
#include <stdlib.h> // for calloc

led_strip_t * led_strip_create_no_backend(uint32_t num_leds)
{
	if (num_leds == 0) {
        printf("Enter a value > 0 for the number of LEDs.\n");
        return NULL;
    }
	
	led_strip_t * led_strip = (led_strip_t*) calloc(1, sizeof(led_strip_t));

	led_strip->num_leds = num_leds;

	// Set first byte of each 4-byte pixel to 0xFF, rest to 0x00 (off)
	led_strip->pixels = (uint32_t *) calloc(led_strip->num_leds, sizeof(uint32_t));
	
    for (uint32_t i = 0; i < led_strip->num_leds; i++)
    {
        led_strip->pixels[i] = 0xFF;
    }

	// Header is all zeros
	led_strip->header_data = (uint8_t *) calloc(HEADER_LENGTH_IN_BYTES, 1);

	// Datasheet says 32*1 bits for footer, but testing shows we must use
    // at least (num_leds + 1)/2 high values.
	led_strip->footer_len = (led_strip->num_leds + 15)/16;
	led_strip->footer_data = (uint8_t *) malloc(led_strip->footer_len);
	memset(led_strip->footer_data, 0xFF, led_strip->footer_len);

	return led_strip;
}

void led_strip_destroy_no_backend(led_strip_t * led_strip)
{
	if (led_strip->pixels) {
		free(led_strip->pixels);
	}
	
	if (led_strip->header_data) {
		free(led_strip->header_data);
	}
	
	if (led_strip->footer_data) {
		free(led_strip->footer_data);
	}
	
	free(led_strip);
}
