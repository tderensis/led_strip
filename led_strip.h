/*!
@file led_strip.h

@brief The main header file for the led_strip. This file contains all public
       interfaces for led strip except for the create function. Users will need
       to include the header file for their specific backend which has the
       create function.
**/

#ifndef LED_STRIP_H
#define LED_STRIP_H

#define PIXEL_MAX_BRIGHTNESS 0x1F

#include <stdint.h>

// Opaque data structure containing the LED strip data.
// Users should only deal with a pointer to this object.
typedef struct _led_strip_t led_strip_t;

/*
 * NOTE: Create functions can be found in the backend specific headers.
 */

/*
@brief Destroy the led_strip and free all resources.

@param led_strip The led strip object.
*/
void led_strip_destroy(led_strip_t * led_strip);

/*
@brief Write the internal buffer to the LED strip.

@param led_strip The led strip object.
@return -1 on error
*/
int led_strip_show(led_strip_t * led_strip);

/*
@breief Clear the entire LED strip and reset the strip to max brightness.
        Just clears the buffer and does not write to the strip.

@param led_strip The led strip object.
*/
void led_strip_clear(led_strip_t * led_strip);

/*
@brief Set a pixel to a given color and brightness

@param led_strip The led strip object.
@param p  The pixel index, starting at 0
@param r  red
@param g  green
@param b  blue
@param brightness  The global brightness of the pixel, independent of color.
                   Max brightness is defined in PIXEL_MAX_BRIGHTNESS.
*/
void led_strip_set_pixel_color_and_brightness(led_strip_t * led_strip,
                                              uint32_t p,
                                              uint8_t r, uint8_t g, uint8_t b,
                                              uint8_t brightness);

/*
@brief Set a pixel to a given color. Does not change brightness.

@param led_strip The led strip object.
@param p  The pixel index, starting at 0
@param r  red
@param g  green
@param b  blue
*/
void led_strip_set_pixel_color(led_strip_t * led_strip,
                               uint32_t p,
                               uint8_t r, uint8_t g, uint8_t b);

/*
@brief Set the global brightness of a pixel. Does not change color.

@param led_strip The led strip object.
@param p  The pixel index, starting at 0
@param brightness  The global brightness of the pixel, independent of color.
                   Max brightness is defined in PIXEL_MAX_BRIGHTNESS.
*/
void led_strip_set_pixel_brightness(led_strip_t * led_strip,
                                    uint32_t p,
                                    uint8_t brightness);

/*
@brief Get the color components of a pixel. NULL can be passed as
       a pointer and that component will be ignored.

@param led_strip The led strip object.
@param p  The pixel index, starting at 0
@param r  pointer to red
@param g  pointer to green
@param b  pointer to blue
@param brightness  The global brightness of the pixel, independent of color.
                   Max brightness is defined in PIXEL_MAX_BRIGHTNESS.
*/
void led_strip_get_pixel_color_and_brightness(led_strip_t * led_strip,
                                              uint32_t p,
                                              uint8_t *r, uint8_t *g, uint8_t *b,
                                              uint8_t *brightness);

/*
@brief Set the whole strip to a given color and brightness

@param led_strip The led strip object.
@param r  red
@param g  green
@param b  blue
@param brightness  The global brightness, independent of color.
                   Max brightness is defined in PIXEL_MAX_BRIGHTNESS.
*/
void led_strip_set_color_and_brightness(led_strip_t * led_strip,
                                        uint8_t r, uint8_t g, uint8_t b,
                                        uint8_t brightness);

/*
@brief Set the whole strip to a given color

@param led_strip The led strip object.
@param r  red
@param g  green
@param b  blue
*/
void led_strip_set_color(led_strip_t * led_strip,
                         uint8_t r, uint8_t g, uint8_t b);

/*
@brief Set the whole strip to a given brightness

@param led_strip The led strip object.
@param brightness  The global brightness, independent of color.
                   Max brightness is defined in PIXEL_MAX_BRIGHTNESS.
*/
void led_strip_set_brightness(led_strip_t * led_strip,
                              uint8_t brightness);

/*
@brief Push a pixel into the front of the strip and move all other pixels
       over. The pixel at the end is dropped.

@param led_strip The led strip object.
@param r  red
@param g  green
@param b  blue
@param brightness  The global brightness of the pixel, independent of color.
                   Max brightness is defined in PIXEL_MAX_BRIGHTNESS.
*/
void led_strip_push_pixel_front(led_strip_t * led_strip,
                                uint8_t r, uint8_t g, uint8_t b,
                                uint8_t brightness);

/*
@brief Push a pixel into the back of the strip and move all other pixels
       over. The pixel at the front is dropped.

@param led_strip The led strip object.
@param r  red
@param g  green
@param b  blue
@param brightness  The global brightness of the pixel, independent of color.
                   Max brightness is defined in PIXEL_MAX_BRIGHTNESS.
*/
void led_strip_push_pixel_back(led_strip_t * led_strip,
                               uint8_t r, uint8_t g, uint8_t b, uint8_t brightness);

/*
@brief Rotate the entire strip to the left. The pixel on the leftmost side is
       moved to the right side. Left is defined as index 0.

@param led_strip The led strip object.
*/
void led_strip_rotate_left(led_strip_t * led_strip);

/*
@brief Rotate the entire strip to the right. The pixel on the rightmost side is
       moved to the left side. Left is defined as index 0.

@param led_strip The led strip object.
*/
void led_strip_rotate_right(led_strip_t * led_strip);

#endif
