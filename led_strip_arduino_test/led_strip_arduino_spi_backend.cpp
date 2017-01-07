/*
@file led_strip_arduino_spi_backend.cpp

@brief Implements the create, destroy, and show functions for the
       Linux SPI backend.
*/
#include "led_strip_arduino_spi_backend.h"
#include "led_strip_no_backend.h"
#include "led_strip_struct.h"

#include <SPI.h>

typedef struct led_strip_backend_arduino_spi_t {
    int ss_pin;
} led_strip_backend_arduino_spi_t;


int led_strip_show_arduino_spi(led_strip_t * led_strip);
void led_strip_destroy_arduino_spi(led_strip_t * led_strip);

led_strip_t * led_strip_create_arduino_spi(uint32_t ss_pin,
                                           uint32_t frequency,
                                           uint32_t num_leds)
{
    led_strip_t * led_strip = led_strip_create_no_backend(num_leds);

    if (led_strip == NULL) {
        return NULL;
    }

    // start the SPI library:
#ifdef SPI_HAS_TRANSACTION
    SPI.begin();
    SPI.beginTransaction(SPISettings(frequency, MSBFIRST, SPI_MODE0));
#else
    uint32_t base_frequency = F_CPU;
    if (frequency >= base_frequency>>1) {
        SPI.setClockDivider(SPI_CLOCK_DIV2);
        Serial.println("div 2");
    } else if (frequency >= base_frequency>>2) {
        SPI.setClockDivider(SPI_CLOCK_DIV4);
    } else if (frequency >= base_frequency>>3) {
        SPI.setClockDivider(SPI_CLOCK_DIV8);
    } else if (frequency >= base_frequency>>4) {
        SPI.setClockDivider(SPI_CLOCK_DIV16);
    } else if (frequency >= base_frequency>>5) {
        SPI.setClockDivider(SPI_CLOCK_DIV32);
    } else if (frequency >= base_frequency>>6) {
        SPI.setClockDivider(SPI_CLOCK_DIV64);
    } else if (frequency >= base_frequency>>7) {
        SPI.setClockDivider(SPI_CLOCK_DIV128);
    }
    SPI.begin();
#endif

    // initalize the chip select
    pinMode(ss_pin, OUTPUT);
    digitalWrite(ss_pin, HIGH);
    
    // Set the backend functions
    led_strip->show = &led_strip_show_arduino_spi;
    led_strip->destroy = &led_strip_destroy_arduino_spi;
    
    // Allocate and configure backend data
    led_strip->backend_data = calloc(sizeof(led_strip_backend_arduino_spi_t), 1);

    // This will make it easier to read the following code
    led_strip_backend_arduino_spi_t * backend_data =
        ((led_strip_backend_arduino_spi_t*)led_strip->backend_data);

    backend_data->ss_pin = ss_pin;
    
    return led_strip;
}

int led_strip_show_arduino_spi(led_strip_t * led_strip)
{
    led_strip_backend_arduino_spi_t * backend_data =
        ((led_strip_backend_arduino_spi_t*)led_strip->backend_data);

    digitalWrite(backend_data->ss_pin, LOW);

    for (uint32_t i = 0; i < HEADER_LENGTH_IN_BYTES; i++) {
        SPI.transfer(led_strip->header_data[i]);
    }
    
    for (uint32_t i = 0; i < led_strip->num_leds; i++) {
        uint8_t * ptr = (uint8_t*) &led_strip->pixels[i];
        SPI.transfer(ptr[0]);
        SPI.transfer(ptr[1]);
        SPI.transfer(ptr[2]);
        SPI.transfer(ptr[3]);
    }

    for (uint32_t i = 0; i < led_strip->footer_len; i++) {
        SPI.transfer(led_strip->footer_data[i]);
    }

    digitalWrite(backend_data->ss_pin, HIGH);
    
    return 0;
}

void led_strip_destroy_arduino_spi(led_strip_t * led_strip)
{
    // Cast to the correct backend
    led_strip_backend_arduino_spi_t * backend_data =
        ((led_strip_backend_arduino_spi_t*)led_strip->backend_data);

#ifdef SPI_HAS_TRANSACTION
    SPI.endTransaction();
#endif

    SPI.end();
    
    pinMode(backend_data->ss_pin, INPUT);
    
    free(backend_data);
}

