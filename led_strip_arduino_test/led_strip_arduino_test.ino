
#include "led_strip_arduino_spi_backend.h"
#include "led_strip.h"

led_strip_t * strip;

/*
CIE Lightness to PWM conversion
L* = 116(Y/Yn)^1/3 - 16 , Y/Yn > 0.008856
L* = 903.3(Y/Yn), Y/Yn <= 0.008856

Alternativly,
PWM = ROUND(((brightness + 16)/116)^3 * MAX_PWM), for brightness > 7.9996
PWM = ROUND(brightness/903.3 * MAX_PWM), for brightness < 7.9996
Where:
 * MAX_PWM is the maximum PWM value you expect to output (255 for 8-bit, etc.)
 * brightness is a value of 0 to 100 and can be calculated as:
   brightness = (i*100)/(n-1), where n is the number of array indices
   and i is the array index 0 to n-1
*/
uint8_t lightness_8bit_32[32] = {
  0,   1,   2,   3,   4,   5,   7,   9,
 12,  15,  18,  22,  27,  32,  37,  44,
 50,  58,  66,  75,  85,  96, 107, 120,
133, 147, 163, 179, 196, 215, 234, 255
};

uint8_t lightness_8bit_50[50] = {
  0,   1,   1,   2,   2,   3,   4,   5,   6,   7,
  8,   9,  11,  13,  14,  17,  19,  21,  24,  27,
 30,  33,  37,  41,  45,  49,  54,  59,  64,  69,
 75,  81,  88,  95, 102, 109, 117, 125, 134, 143,
152, 162, 172, 182, 193, 205, 217, 229, 242, 255
};

#define RED 0
#define GREEN 1
#define BLUE 2
uint32_t log_len = 50;
uint8_t color_changing = GREEN;
int8_t dir = 1;
uint8_t r = 255, g = 0, b = 0;

void setup() {
  // put your setup code here, to run once:
  uint32_t num_leds = 300;
  int slave_select_pin = 10;
  uint32_t spi_freq_hz = 8000000;
  Serial.begin(9600);
  strip = led_strip_create_arduino_spi(slave_select_pin,
                                       spi_freq_hz,
                                       num_leds);
  for (int i = 0; i < 6; i++) {
    for (uint32_t i = (dir == 1) ? 0 : log_len-1 ; i < log_len && i >=0 ; i+=dir) {
      if (color_changing == RED) {
        r = lightness_8bit_50[i];
      } else if (color_changing == GREEN) {
        g = lightness_8bit_50[i];
      } else if (color_changing == BLUE) {
        b = lightness_8bit_50[i];
      }
      led_strip_push_pixel_front(strip, r, g, b, PIXEL_MAX_BRIGHTNESS);
    }
  
    // Change which color is changing
    if (color_changing == GREEN) {
      color_changing = RED;
    } else if (color_changing == RED) {
      color_changing = BLUE;
    } else if (color_changing == BLUE) {
      color_changing = GREEN;
    }
  
    // Switch direction
    dir = (dir == 1) ? -1 : 1;
  }
}



void loop() {
  // put your main code here, to run repeatedly:

  led_strip_rotate_right(strip);
  led_strip_show(strip);
  delay(10);
}

