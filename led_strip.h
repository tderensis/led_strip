/*!
  @file led_strip.h
**/

#ifndef LED_STRIP_H
#define LED_STRIP_H

#define PIXEL_MAX_BRIGHTNESS 15

#include <stdint.h>

// Opaque data structure containing the LED strip data.
// Actual structure defined in .c file
typedef struct _led_strip_t led_strip_t;

/*
@brief Opens the SPI device.

@param device  The device string, such as /dev/spidev1.0
@param frequency  The SPI clock frequency in Hz. Actual speed may be lower
                  because hardware SPI speed is a function of the system core
                  frequency and the smallest power-of-two prescaler
                  that will not exceed the requested rate.
@param numLEDs  The number of LEDs in the strip. Must be > 0.
@return led strip pointer on success, NULL otherwise
*/
//led_strip_t * led_strip_create_linux_spi(const char * device,
//										 uint32_t frequency,
//										 uint32_t numLEDs);

/*
@brief Close the SPI device and free all resources.
*/
void led_strip_destroy(led_strip_t * led_strip);

/*
@breief Clear the entire LED strip. Just clears the buffer and does not
        write to the strip
*/
void led_strip_clear(led_strip_t * led_strip);

/*
@brief Write the internal buffer to the LED strip.

@return -1 on error
*/
int led_strip_show(led_strip_t * led_strip);

/*
@brief Set a pixel to a given color. Does not change brightness.

@param p  The pixel index, starting at 0
@param r  red
@param g  green
@param b  blue
@param brightness  The global brightness of the pixel, independent of color.
                   Max brightness is 15.
*/
void led_strip_set_pixel_color(led_strip_t * led_strip, uint32_t p,
							   uint8_t r, uint8_t g, uint8_t b);

/*
@brief Set the global brightness of a pixel. Does not change color.

@param p  The pixel index, starting at 0
@param brightness  The global brightness of the pixel, independent of color.
                   Max brightness is 15.
*/
void led_strip_set_pixel_brightness(led_strip_t * led_strip, uint32_t p,
									uint8_t brightness);

/*
@brief Get the color components of a pixel

@param r  pointer to red
@param g  pointer to green
@param b  pointer to blue
@param p  The pixel index, starting at 0
*/
void led_strip_get_pixel_color(led_strip_t * led_strip, uint32_t p,
							   uint8_t *r, uint8_t *g, uint8_t *b);

/*
@brief Get the global brightness of a pixel

@param p  The pixel index, starting at 0
@return brightness  The global brightness of the pixel, independent of color.
                    Max brightness is 15.
*/
uint8_t led_strip_get_pixel_brightness(led_strip_t * led_strip, uint32_t p);

/*
@brief Set the whole strip to a given color

@param r  red
@param g  green
@param b  blue
*/
void led_strip_set_color(led_strip_t * led_strip, uint8_t r, uint8_t g, uint8_t b);

/*
@brief Set the whole strip to a given brightness

@param brightness  The global brightness, independent of color.
                   Max brightness is 15.
*/
void led_strip_set_brightness(led_strip_t * led_strip, uint8_t brightness);

/*
@brief Push a pixel into the front of the strip and move all other pixels
       over. The pixel at the end is dropped.

@param r  red
@param g  green
@param b  blue
@param brightness  The global brightness of the pixel, independent of color.
                   Max brightness is 15.
*/
void led_strip_push_pixel_front(led_strip_t * led_strip,
								uint8_t r, uint8_t g, uint8_t b, uint8_t brightness);

/*
@brief Push a pixel into the back of the strip and move all other pixels
       over. The pixel at the front is dropped.

@param r  red
@param g  green
@param b  blue
@param brightness  The global brightness of the pixel, independent of color.
                   Max brightness is 15.
*/
void led_strip_push_pixel_back(led_strip_t * led_strip,
							   uint8_t r, uint8_t g, uint8_t b, uint8_t brightness);

/*
@brief Rotate the entire strip to the left. The pixel on the leftmost side is
       moved to the right side. Left is defined as index 0.
*/
void led_strip_rotate_left(led_strip_t * led_strip);

/*
@brief Rotate the entire strip to the right. The pixel on the rightmost side is
       moved to the left side. Left is defined as index 0.
*/
void led_strip_rotate_right(led_strip_t * led_strip);

#endif
