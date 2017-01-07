/*
@file led_strip_struct.h

@brief The definition of the led strip object.
*/
#ifndef LED_STRIP_STRUCT_H
#define LED_STRIP_STRUCT_H

#define HEADER_LENGTH_IN_BYTES 4

struct _led_strip_t {
    uint32_t *pixels;
    uint32_t num_leds;
    uint8_t * header_data;
    uint8_t * footer_data;
    uint32_t footer_len;
    int (*show) (led_strip_t *);
    void (*destroy) (led_strip_t *);
    void * backend_data; // Backend dependent data
};
#endif
