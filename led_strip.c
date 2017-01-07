/*!
@file led_strip.c

@brief The main implementation file for manipulating the led strip.
**/

#include "led_strip.h"
#include "led_strip_struct.h"
#include "led_strip_no_backend.h"
#include <assert.h>
#include <string.h>

#define PIXEL_BRIGHTNESS_MASK 0x0F
#define PIXEL_BRIGHTNESS_HIGH_BITS 0xE0

void led_strip_destroy(led_strip_t * led_strip)
{
    assert(led_strip->destroy && "No destroy function was set in create function");

    // First destroy any backend specific data
    led_strip->destroy(led_strip);

    // Then destroy everything else.
    led_strip_destroy_no_backend(led_strip);
}

int led_strip_show(led_strip_t * led_strip)
{
    assert(led_strip->show && "No show function was set in create function");
    
    return led_strip->show(led_strip);
}

void led_strip_clear(led_strip_t * led_strip)
{
    for (uint32_t i = 0; i < led_strip->num_leds; i++) {
        uint8_t * ptr = (uint8_t*) &led_strip->pixels[i];
        ptr[0] = PIXEL_MAX_BRIGHTNESS | PIXEL_BRIGHTNESS_HIGH_BITS;
        ptr[1] = 0;
        ptr[2] = 0;
        ptr[3] = 0;
    }
}

void led_strip_set_pixel_color(led_strip_t * led_strip, uint32_t p,
                               uint8_t r, uint8_t g, uint8_t b)
{
    if (p < led_strip->num_leds) {
        uint8_t *ptr = (uint8_t*) &led_strip->pixels[p];
        // Ignore brightness
        ptr[1] = b;
        ptr[2] = g;
        ptr[3] = r;
    }
}

void led_strip_set_pixel_brightness(led_strip_t * led_strip, uint32_t p,
                                    uint8_t brightness)
{
    if (p < led_strip->num_leds) {
        uint8_t *ptr = (uint8_t*) &led_strip->pixels[p];
        if (brightness > PIXEL_MAX_BRIGHTNESS) {
            brightness = PIXEL_MAX_BRIGHTNESS;
        }
        ptr[0] = brightness | PIXEL_BRIGHTNESS_HIGH_BITS;
        // Ignore color
    }
}

void led_strip_get_pixel_color(led_strip_t * led_strip, uint32_t p,
                               uint8_t *r, uint8_t *g, uint8_t *b)
{
    if (p < led_strip->num_leds) {
        uint8_t *ptr = (uint8_t*) &led_strip->pixels[p];

        if (r != NULL) {
            *r = ptr[3];
        }
        if (g != NULL) {
            *g = ptr[2];
        }
        if (b != NULL) {
            *b = ptr[1];
        }
    }
}

uint8_t led_strip_get_pixel_brightness(led_strip_t * led_strip, uint32_t p)
{
    if (p < led_strip->num_leds) {
        uint8_t *ptr = (uint8_t*) &led_strip->pixels[p];
        return ptr[0] & PIXEL_BRIGHTNESS_MASK;
    } else {
        return 0;
    }
}

void led_strip_set_color(led_strip_t * led_strip, uint8_t r, uint8_t g, uint8_t b)
{
    for (uint32_t i = 0; i < led_strip->num_leds; i++) {
        uint8_t * ptr = (uint8_t*) &led_strip->pixels[i];
        // Ignore brightness
        ptr[1] = b;
        ptr[2] = g;
        ptr[3] = r;
    }
}

void led_strip_set_brightness(led_strip_t * led_strip, uint8_t brightness)
{
    if (brightness > PIXEL_MAX_BRIGHTNESS) {
        brightness = PIXEL_MAX_BRIGHTNESS | PIXEL_BRIGHTNESS_HIGH_BITS;
    } else {
        brightness = brightness | PIXEL_BRIGHTNESS_HIGH_BITS;
    }

    for (uint32_t i = 0; i < led_strip->num_leds; i++) {
        uint8_t * ptr = (uint8_t*) &led_strip->pixels[i];
        ptr[0] = brightness;
        // Ignore color
    }
}

void led_strip_push_pixel_front(led_strip_t * led_strip,
                                uint8_t r, uint8_t g, uint8_t b, uint8_t brightness)
{
    for (uint32_t i = led_strip->num_leds - 1; i > 0; i--) {
        uint8_t * ptr = (uint8_t*) &led_strip->pixels[i];
        uint8_t * ptr_previous = (uint8_t*) &led_strip->pixels[i-1];
        ptr[0] = ptr_previous[0];
        ptr[1] = ptr_previous[1];
        ptr[2] = ptr_previous[2];
        ptr[3] = ptr_previous[3];
    }

    // Set the first pixel to the desired color and brightness
    led_strip_set_pixel_color(led_strip, 0, r, g, b);
    led_strip_set_pixel_brightness(led_strip, 0, brightness);
}

void led_strip_push_pixel_back(led_strip_t * led_strip,
                               uint8_t r, uint8_t g, uint8_t b, uint8_t brightness)
{
    for (uint32_t i = 0; i < led_strip->num_leds - 1; i++) {
        uint8_t * ptr = (uint8_t*) &led_strip->pixels[i];
        uint8_t * ptr_next = (uint8_t*) &led_strip->pixels[i+1];
        ptr[0] = ptr_next[0];
        ptr[1] = ptr_next[1];
        ptr[2] = ptr_next[2];
        ptr[3] = ptr_next[3];
    }

    // Set the last pixel to the desired color and brightness
    led_strip_set_pixel_color(led_strip,led_strip->num_leds - 1, r, g, b);
    led_strip_set_pixel_brightness(led_strip, led_strip->num_leds - 1, brightness);
}

void led_strip_rotate_left(led_strip_t * led_strip)
{
    uint8_t r, g, b, brightness;
    brightness = led_strip_get_pixel_brightness(led_strip, 0);
    led_strip_get_pixel_color(led_strip, 0, &r, &g, &b);
    
    led_strip_push_pixel_back(led_strip, r, g, b, brightness);
}

void led_strip_rotate_right(led_strip_t * led_strip)
{
    uint8_t r, g, b, brightness;
    brightness = led_strip_get_pixel_brightness(led_strip, led_strip->num_leds - 1);
    led_strip_get_pixel_color(led_strip, led_strip->num_leds - 1, &r, &g, &b);
    
    led_strip_push_pixel_front(led_strip, r, g, b, brightness);
}

