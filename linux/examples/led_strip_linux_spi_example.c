/*
@file led_strip_test.c

@brief An example of how to use the led strip library on linux.
*/
#define BUILD_LED_STRIP_LINUX_SPI_BACKEND

#include "led_strip_linux_spi_backend.h"

// compile with -std=gnu99
#include <time.h>
#include <stdio.h>

int main()
{
    // Test 0: pulsating strip
    int test = 0;
    
    int repeat = 0; // How many times to repeat the test. 0 is infinite

    int leds = 300; // Number of leds in the strip

    int update_interval_ms = 100;

    // Used for timing
    struct timespec tim;
    tim.tv_sec = 0;
    tim.tv_nsec = (1000 * 10000);// * update_interval_ms%1000;

    // Test 0 vars
    uint8_t strip_r = 0;
    uint8_t strip_g = 255;
    uint8_t strip_b = 0;
    uint8_t increment = 2;
    
    // Test 1 vars
    uint8_t center = 5;
    uint8_t center_r = 255;
    uint8_t center_g = 0;
    uint8_t center_b = 0;
    uint8_t back_r = 0;
    uint8_t back_g = 0;
    uint8_t back_b = 255;

    // Initialize led strip
    led_strip_t * strip = led_strip_create_linux_spi("/dev/spidev1.0", 5000000, leds);
    
    // Initialization
    switch(test) {
    case 0:
        break;
    case 1:
        led_strip_set_color(strip, back_r, back_g, back_b);
        for (int i = 0; i < center; i++)
        {
            led_strip_push_pixel_front(strip, center_r, center_g, center_b, PIXEL_MAX_BRIGHTNESS);
        }
        led_strip_show(strip);
        break;
    }
    
    
    do {
        switch (test) {
        case 0:
            for (int i = 0; i < UINT8_MAX; i+=increment)
            {
                int r = (i * strip_r)/UINT8_MAX;
                int g = (i * strip_g)/UINT8_MAX;
                int b = (i * strip_b)/UINT8_MAX;
                
                led_strip_set_color(strip, r, g, b);
                led_strip_show(strip);
                nanosleep(&tim, NULL);
            }
            for (int i = UINT8_MAX; i >= 0; i-=increment)
            {
                int r = (i * strip_r)/UINT8_MAX;
                int g = (i * strip_g)/UINT8_MAX;
                int b = (i * strip_b)/UINT8_MAX;
                
                led_strip_set_color(strip, r, g, b);
                led_strip_show(strip);
                nanosleep(&tim, NULL);
            }
            break;
        case 1:
            for (int i = 0; i < leds-center; i++)
            {
                led_strip_rotate_right(strip);
                led_strip_show(strip);
                nanosleep(&tim, NULL);
            }
            for (int i = 0; i < leds-center; i++)
            {
                led_strip_rotate_left(strip);
                led_strip_show(strip);
                nanosleep(&tim, NULL);
            }
            break;
        default:
            printf("Invalid test %d\n", test);
        }
        
        if (repeat > 0) {
            repeat--;
        } else {
            repeat = -1;
        }
    } while(repeat);

    led_strip_clear(strip);
    led_strip_show(strip);
    led_strip_destroy(strip);
}
