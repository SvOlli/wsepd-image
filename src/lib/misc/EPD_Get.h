
#ifndef __EPD_GET_H__
#define __EPD_GET_H__ __EPD_GET_H__

#include "types.h"

#define EPD_BITPLANE_OFFSET(WIDTH, HEIGHT) (((WIDTH + 7) / 8) * HEIGHT)

epd_api_t setup_epd( uint16_t width, uint16_t height, uint8_t bitplanes,
                     void(*init)(),
                     void(*clear)(),
                     void(*display)(),
                     void(*sleep)() );

extern const epd_list_t *epd_list;

/* implemented */
epd_api_t setup_epd_1in54();
epd_api_t setup_epd_1in54b();
epd_api_t setup_epd_1in54c();
epd_api_t setup_epd_1in54_v2();
epd_api_t setup_epd_2in13();
epd_api_t setup_epd_2in13bc();
epd_api_t setup_epd_2in13d();
epd_api_t setup_epd_2in13_v2();
epd_api_t setup_epd_2in9();
epd_api_t setup_epd_2in9bc();
epd_api_t setup_epd_4in2();
epd_api_t setup_epd_4in2bc();
epd_api_t setup_epd_5in83();
epd_api_t setup_epd_5in83bc();
epd_api_t setup_epd_2in7();
epd_api_t setup_epd_2in7b();
epd_api_t setup_epd_7in5();
epd_api_t setup_epd_7in5bc();

#endif

