/*!
@file led_strip_linux_spi_backend.c

@brief Implements the create, destroy, and show functions for the
       Linux SPI backend.
**/

#include "led_strip_linux_spi_backend.h"
#include "led_strip_no_backend.h"
#include "led_strip_struct.h"

#include <stdio.h>
#include <stdlib.h> // for malloc
#include <string.h> // for memset
#include <unistd.h> // for close
#include <fcntl.h>
#include <assert.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

typedef struct led_strip_backend_linux_spi_t {
    int fd; // SPI file descriptor
    struct spi_ioc_transfer xfer[3];
} led_strip_backend_linux_spi_t;


int led_strip_show_linux_spi(led_strip_t * led_strip);
void led_strip_destroy_linux_spi(led_strip_t * led_strip);

led_strip_t * led_strip_create_linux_spi(const char * device,
                                         uint32_t frequency,
                                         uint32_t num_leds)
{
    // For this backend we want to make sure the SPI is working before
    // allocating anything.
    int ret = 0;

    int fd = open(device, O_RDWR);
    if (fd < 0) {
        printf("Can't open device %s. Try sudo.\n", device);
        return NULL;
    }

    uint8_t mode = 0;
    ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
    if (ret == -1) {
        printf("Can't set spi mode.\n");
        return NULL;
    }

    uint8_t bits = 8;
    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (ret == -1) {
        printf("Can't set bits per word.\n");
        return NULL;
    }

    ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &frequency);
    if (ret == -1) {
        printf("Can't set max speed HZ.\n");
        return NULL;
    }

    // Now we can create the strip without a backend.
    led_strip_t * led_strip = led_strip_create_no_backend(num_leds);

    if (led_strip == NULL) {
        return NULL;
    }

    // Set the backend functions
    led_strip->show = &led_strip_show_linux_spi;
    led_strip->destroy = &led_strip_destroy_linux_spi;

    // Allocate and configure backend data
    led_strip->backend_data = calloc(sizeof(led_strip_backend_linux_spi_t), 1);

    // This will make it easier to read the following code
    led_strip_backend_linux_spi_t * backend_data =
        ((led_strip_backend_linux_spi_t*)led_strip->backend_data);

    backend_data->fd = fd;

    // Header
    backend_data->xfer[0].tx_buf = (unsigned long) led_strip->header_data;
    backend_data->xfer[0].len = HEADER_LENGTH_IN_BYTES;
    backend_data->xfer[0].speed_hz = frequency;
    backend_data->xfer[0].bits_per_word = bits;
    // Color payload
    backend_data->xfer[1].tx_buf = (unsigned long) led_strip->pixels;
    backend_data->xfer[1].len = led_strip->num_leds * sizeof(led_strip->num_leds);
    backend_data->xfer[1].speed_hz = frequency;
    backend_data->xfer[1].bits_per_word = bits;
    // Footer
    backend_data->xfer[2].tx_buf = (unsigned long) led_strip->footer_data;
    backend_data->xfer[2].len = led_strip->footer_len;
    backend_data->xfer[2].speed_hz = frequency;
    backend_data->xfer[2].bits_per_word = bits;

    return led_strip;
}

int led_strip_show_linux_spi(led_strip_t * led_strip)
{
    led_strip_backend_linux_spi_t * backend_data =
        ((led_strip_backend_linux_spi_t*)led_strip->backend_data);

    int ret = ioctl(backend_data->fd, SPI_IOC_MESSAGE(3), backend_data->xfer);
    if (ret < 1) {
        printf("Can't send spi message.\n");
        return ret;
    }
    return 0;
}

void led_strip_destroy_linux_spi(led_strip_t * led_strip)
{
    assert(led_strip->backend_data && "No backend created in create function");

    // Cast to the correct backend
    led_strip_backend_linux_spi_t * backend_data =
        ((led_strip_backend_linux_spi_t*)led_strip->backend_data);

    // Close the SPI port
    if (backend_data->fd) {
        close(backend_data->fd);
    }

    free(backend_data);
}
