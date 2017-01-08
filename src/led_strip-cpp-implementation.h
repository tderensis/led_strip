/*!
@file led_strip-cpp-implementation.hpp

@brief This file should never be included by the user. This is the cpp
       implementation file.
**/

#include "led_strip_no_backend.h"

inline LedStrip::LedStrip(uint32_t num_leds)
{
    this->led_strip = led_strip_create_no_backend(num_leds);
}

inline LedStrip::~LedStrip()
{
    led_strip_destroy(this->led_strip);
}

inline int LedStrip::show()
{
    return led_strip_show(this->led_strip);
}

inline void LedStrip::clear()
{
    led_strip_clear(this->led_strip);
}

inline void LedStrip::setPixelColorAndBrightness(uint32_t p,
                                                 uint8_t r, uint8_t g, uint8_t b,
                                                 uint8_t brightness)
{
    led_strip_set_pixel_color_and_brightness(this->led_strip, p, r, g, b, brightness);
}

inline void LedStrip::setPixelColor(uint32_t p, uint8_t r, uint8_t g, uint8_t b)
{
    led_strip_set_pixel_color(this->led_strip, p, r, g, b);
}

inline void LedStrip::setPixelBrightness(uint32_t p, uint8_t brightness)
{
    led_strip_set_pixel_brightness(this->led_strip, p, brightness);
}

inline void LedStrip::getPixelColorAndBrightness(uint32_t p,
                                                 uint8_t *r, uint8_t *g, uint8_t *b,
                                                 uint8_t *brightness)
{
    led_strip_get_pixel_color_and_brightness(this->led_strip, p, r, g, b, brightness);
}

inline void LedStrip::setColorAndBrightness(uint8_t r, uint8_t g, uint8_t b,
                                               uint8_t brightness)
{
    led_strip_set_color_and_brightness(this->led_strip, r, g, b, brightness);
}

inline void LedStrip::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    led_strip_set_color(this->led_strip, r, g, b);
}

inline void LedStrip::setBrightness(uint8_t brightness)
{
    led_strip_set_brightness(this->led_strip, brightness);
}

inline void LedStrip::pushPixelFront(uint8_t r, uint8_t g, uint8_t b,
                                       uint8_t brightness)
{
    led_strip_push_pixel_front(this->led_strip, r, g, b, brightness);
}

inline void LedStrip::pushPixelBack(uint8_t r, uint8_t g, uint8_t b,
                                      uint8_t brightness)
{
    led_strip_push_pixel_back(this->led_strip, r, g, b, brightness);
}

inline void LedStrip::rotateLeft()
{
    led_strip_rotate_left(this->led_strip);
}

inline void LedStrip::rotateRight()
{
    led_strip_rotate_right(this->led_strip);
}

