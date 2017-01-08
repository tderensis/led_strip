# led_strip
Library for controlling LED strips that use the APA102 5050 RGB LED. Both C and C++ are currently supported.

## Dependencies
CMake 2.8.11 or later

## Usage

### C
First include the backend you are using. The example here is for the Linux SPI backend, which will work on the Raspberry Pi, BeagleBone, and any other Linux system with SPI pins.

``` c
#include "led_strip_linux_spi_backend.h"
```

Then create the device. Here is an example of the Linux SPI create function. The create function is the only one specific to the backend. The rest of the functions (defined in led_strip.h) apply regardless of backend.

Note that devices such as the BeagleBone and Raspberry Pi require you to enable the SPI device first.

``` c
uint32_t leds = 300; // Number of leds in the strip
uint32_t frequency_hz = 5000000; // SPI frequency in Hz
char * spi_dev = "/dev/spidev1.0";

led_strip_t * strip = led_strip_create_linux_spi(spi_dev, frequency_hz, leds);
```

When the strip is created it sets every pixel to off. Next you can set the pixels of the strip. These functions only modify memory and do not write to the strip. This allows you to change multiple pixels and then write the changes all at once.

``` c
uint32_t p = 9; \\ pixel index (starting at 0)
uint8_t r = 255, g = 255, b = 0; \\ yellow
uint8_t brightness = PIXEL_MAX_BRIGHTNESS; \\ Max is 32, Min is 0 (off)

\\ Set everything
led_strip_set_pixel_color_and_brightness(strip, p, r, g, b, brightness);

\\ Only set color
led_strip_set_pixel_color(strip, p, r, g, b);

\\ Only set brightness
led_strip_set_pixel_brightness(strip, p, brightness);

\\ Get the value of a given pixel. Passing NULL will ignore that component.
led_strip_set_pixel_color_and_brightness(strip, p, &r, &g, &b, NULL);

```

Or you can write to the entire strip at once.

``` c
led_strip_set_color_and_brightness(strip, r, g, b, brightness);

led_strip_set_color(strip, r, g, b);

led_strip_set_brightness(strip, brightness);
```

There are even handy functions that will push pixels into the strip and rotate it. These are useful for animations.

``` c
// Push a pixel into the front of the strip and move all other pixels
// over. The pixel at the end is dropped.
led_strip_push_pixel_front(strip, r, g, b, brightness);

// Push a pixel into the back of the strip and move all other pixels
// over. The pixel at the front is dropped.
led_strip_push_pixel_back(strip, r, g, b, brightness);

// Rotate the entire strip to the left. The pixel on the leftmost side is
// moved to the right side. Left is defined as index 0.
led_strip_rotate_left(strip);

// Rotate the entire strip to the right. The pixel on the rightmost side is
// moved to the left side. Left is defined as index 0.
led_strip_rotate_right(strip);
```

Once you are ready to display to the strip, call the show fuction!

``` c
led_strip_show(strip);
```

When you are done using the led strip, you can call the destroy function.

``` c
// Turn the strip off
led_strip_clear(strip);
led_strip_show(strip);

// Free all of the resources associated with the led strip
led_strip_destroy(strip);
```

### C++
The C++ library is a wrapper around the C library, so it is very similar to the C usage.

The Arduino SPI backend uses this C++ wrapper. First include it.

``` c
#include "led_strip_arduino_spi_backend.h"
```

Next create the device.

``` c
uint32_t num_leds = 300;
uint32_t spi_freq_hz = 8000000;
LedStripArduinoSpi strip(spi_freq_hz, num_leds);
```

The same led strip functions exist in C++, but they look like this instead. The strip is an object instead of a struct, and the underlines are replaced with CamelCase.

``` cpp
strip.setPixelColorAndBrightness(p, r, g, b, brightness);
```

See the C Usage for more details.

## Backends
So far the following backends are complete.

### Linux SPI
To build examples
```
cd build
cmake ../
make
```
Examples will be installed to bin.

### Arduino SPI
To install as a library, run the createArduinoLibrary.sh script in arduino folder. This will create a LedStrip.zip file which can be imported via the Arduino GUI under Sketch->Include Library->Add .ZIP Library. You can then find examples under File->Examples->LedStrip.

## TODO
* Migrate to CMake with build options for each backend
* Create Linux and Arduino bit-bang backend
* Make C++ examples
