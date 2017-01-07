/*!
@file led_strip.c

@brief The main implementation file for manipulating the led strip.
**/

#include "led_strip.h"
#include "led_strip_struct.h"
#include "led_strip_no_backend.h"
#include <assert.h>
#include <string.h>

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
    uint32_t i = 0;
    for (uint8_t * ptr = (uint8_t*)led_strip->pixels; i < led_strip->num_leds; i++, ptr += 4) {
        ptr[1] = 0;
        ptr[2] = 0;
        ptr[3] = 0;
    }
}

void led_strip_set_pixel_color(led_strip_t * led_strip, uint32_t p,
                               uint8_t r, uint8_t g, uint8_t b)
{
    if (p < led_strip->num_leds) {
        uint8_t *ptr = (uint8_t*)&led_strip->pixels[p];
        ptr[3] = r;
        ptr[2] = g;
        ptr[1] = b;
    }
}

void led_strip_set_pixel_brightness(led_strip_t * led_strip, uint32_t p,
                                    uint8_t brightness)
{
    if (p < led_strip->num_leds) {
        uint8_t *ptr = (uint8_t*)&led_strip->pixels[p];
        if (brightness > PIXEL_MAX_BRIGHTNESS) {
            brightness = PIXEL_MAX_BRIGHTNESS;
        }
        ptr[0] = brightness | 0xE0;
    }
}

void led_strip_get_pixel_color(led_strip_t * led_strip, uint32_t p,
                               uint8_t *r, uint8_t *g, uint8_t *b)
{
    if (p < led_strip->num_leds) {
        uint8_t *ptr = (uint8_t*)&led_strip->pixels[p];

        if (r != NULL)
            *r = ptr[3];
        if (g != NULL)
            *g = ptr[2];
        if (b != NULL)
            *b = ptr[1];
    }
}

uint8_t led_strip_get_pixel_brightness(led_strip_t * led_strip, uint32_t p)
{
    if (p < led_strip->num_leds) {
        uint8_t *ptr = (uint8_t*)&led_strip->pixels[p];
        return ptr[0] & 0x0F;
    } else {
        return 0;
    }
}

void led_strip_set_color(led_strip_t * led_strip, uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t i = 0;
    for (uint8_t * ptr = (uint8_t*)led_strip->pixels; i < led_strip->num_leds; i++, ptr += 4) {
        ptr[1] = b;
        ptr[2] = g;
        ptr[3] = r;
    }
}

void led_strip_set_brightness(led_strip_t * led_strip, uint8_t brightness)
{
    if (brightness > PIXEL_MAX_BRIGHTNESS) {
        brightness = PIXEL_MAX_BRIGHTNESS;
    }
    uint32_t i = 0;
    for (uint8_t * ptr = (uint8_t*)led_strip->pixels; i < led_strip->num_leds; i++, ptr += 4) {
        ptr[0] = brightness | 0xE0;
    }
}

void led_strip_push_pixel_front(led_strip_t * led_strip,
                                uint8_t r, uint8_t g, uint8_t b, uint8_t brightness)
{
    uint32_t i = 0;
    for (uint8_t * ptr = (uint8_t*)&led_strip->pixels[led_strip->num_leds-2];
         i < led_strip->num_leds-1; i++, ptr -= 4) {
        ptr[4] = ptr[0];
        ptr[5] = ptr[1];
        ptr[6] = ptr[2];
        ptr[7] = ptr[3];
    }
    led_strip_set_pixel_color(led_strip, 0, r, g, b);
    led_strip_set_pixel_brightness(led_strip, 0, brightness);
}

void led_strip_push_pixel_back(led_strip_t * led_strip,
                               uint8_t r, uint8_t g, uint8_t b, uint8_t brightness)
{
    uint32_t i = 0;
    for (uint8_t * ptr = (uint8_t*)led_strip->pixels; i < led_strip->num_leds-1; i++, ptr += 4) {
        ptr[0] = ptr[4];
        ptr[1] = ptr[5];
        ptr[2] = ptr[6];
        ptr[3] = ptr[7];
    }
    led_strip_set_pixel_color(led_strip,led_strip->num_leds - 1, r, g, b);
    led_strip_set_pixel_brightness(led_strip, led_strip->num_leds - 1, brightness);
}

void led_strip_rotate_left(led_strip_t * led_strip)
{
    uint32_t i;
    uint8_t r, g, b, brightness;
    brightness = led_strip_get_pixel_brightness(led_strip, 0);
    led_strip_get_pixel_color(led_strip, 0, &r, &g, &b);
    
    led_strip_push_pixel_back(led_strip, r, g, b, brightness);
}

void led_strip_rotate_right(led_strip_t * led_strip)
{
    uint32_t i;
    uint8_t r, g, b, brightness;
    brightness = led_strip_get_pixel_brightness(led_strip, led_strip->num_leds - 1);
    led_strip_get_pixel_color(led_strip, led_strip->num_leds - 1, &r, &g, &b);
    
    led_strip_push_pixel_front(led_strip, r, g, b, brightness);
}

