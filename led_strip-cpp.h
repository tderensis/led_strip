/*!
@file led_strip-cpp.hpp

@brief The header file for cpp projects.
**/

#ifndef LED_STRIP_CPP_H
#define LED_STRIP_CPP_H

#include "led_strip.h"
#include "led_strip_struct.h"

class LedStrip
{
public:
    inline LedStrip(uint32_t num_leds);

    inline ~LedStrip();

    inline int show();

    inline void clear();

    inline void setPixelColorAndBrightness(uint32_t p,
                                           uint8_t r, uint8_t g, uint8_t b,
                                           uint8_t brightness);

    inline void setPixelColor(uint32_t p, uint8_t r, uint8_t g, uint8_t b);

    inline void setPixelBrightness(uint32_t p, uint8_t brightness);

    inline void getPixelColorAndBrightness(uint32_t p,
                                           uint8_t *r, uint8_t *g, uint8_t *b,
                                           uint8_t *brightness);

    inline void setColorAndBrightness(uint8_t r, uint8_t g, uint8_t b,
                                      uint8_t brightness);

    inline void setColor(uint8_t r, uint8_t g, uint8_t b);

    inline void setBrightness(uint8_t brightness);

    inline void pushPixelFront(uint8_t r, uint8_t g, uint8_t b,
                               uint8_t brightness);

    inline void pushPixelBack(uint8_t r, uint8_t g, uint8_t b,
                              uint8_t brightness);

    inline void rotateLeft();

    inline void rotateRight();

protected:
    led_strip_t * led_strip;
};

#include "led_strip-cpp-implementation.h"

#endif
