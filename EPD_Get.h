
#ifndef __EPD_GET_H__
#define __EPD_GET_H__ __EPD_GET_H__

#include "types.h"

#if defined(EPD_WIDTH) && defined(EPD_HEIGHT)
#define EPD_BITPLANESIZE (((EPD_WIDTH + 7) / 8) * EPD_HEIGHT)
#endif

epd_api_t setup_epd( uint16_t width, uint16_t height, uint8_t bitplanes,
                     uint8_t(*init)(),
                     void(*clear)(),
                     void(*display)(),
                     void(*sleep)() );

extern const epd_list_t *epd_list;

/* implemented */
epd_api_t setup_epd_1in54();
epd_api_t setup_epd_1in54b();
epd_api_t setup_epd_2in13();
epd_api_t setup_epd_2in13b();
epd_api_t setup_epd_2in13d();
epd_api_t setup_epd_2in7();
epd_api_t setup_epd_2in7b();
epd_api_t setup_epd_2in9();
epd_api_t setup_epd_2in9b();
epd_api_t setup_epd_4in2();
epd_api_t setup_epd_4in2b();
epd_api_t setup_epd_5in83();
epd_api_t setup_epd_5in83b();
epd_api_t setup_epd_7in5();
epd_api_t setup_epd_7in5b();

#endif

