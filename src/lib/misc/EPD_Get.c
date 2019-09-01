/*****************************************************************************
* | File        :   EPD_Get_2in7.c
* | Author      :   SvOlli
* | Function    :   Electronic paper drivers wrapper
*****************************************************************************/

#include "EPD_Get.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

epd_api_t setup_epd( uint16_t width, uint16_t height, uint8_t bitplanes,
                     void(*init)(),
                     void(*clear)(),
                     void(*display)(),
                     void(*sleep)() )
{
   epd_api_t epd;

   epd.dispsize.x = width;
   epd.dispsize.y = height;
   epd.linestep   = (width + 7) / 8;
   epd.bitplanes  = bitplanes;
   epd.datasize   = epd.linestep * height;
   epd.init       = init;
   epd.clear      = clear;
   epd.sleep      = sleep;
   epd.display    = display;

   return epd;
}

static const epd_list_t _epd_list[] =
{
   { setup_epd_1in54,    "1.54",    "" },
   { setup_epd_1in54_v2, "1.54_v2", "" },
   { setup_epd_1in54b,   "1.54b",   ", additional red color" },
   { setup_epd_1in54c,   "1.54c",   ", additional yellow color" },
   { setup_epd_2in13,    "2.13",    "" },
   { setup_epd_2in13_v2, "2.13_v2", "" },
   { setup_epd_2in13bc,  "2.13bc",  ", additional red or yellow color" },
   { setup_epd_2in13d,   "2.13d",   ", flexible" },
   { setup_epd_2in9,     "2.9",     "" },
   { setup_epd_2in9bc,   "2.9bc",   ", additional red or yellow color" },
   { setup_epd_4in2,     "4.2",     "" },
   { setup_epd_4in2bc,   "4.2bc",   ", additional red or yellow color" },
   { setup_epd_5in83,    "5.83",    "" },
   { setup_epd_5in83bc,  "5.83bc",  ", additional red or yellow color" },
   { setup_epd_2in7,     "2.7",     "" },
   { setup_epd_2in7b,    "2.7b",    ", additional red color" },
   { setup_epd_7in5,     "7.5",     "" },
   { setup_epd_7in5bc,   "7.5bc",   ", additional red or yellow color" },
   { 0, 0, 0 }
};

const epd_list_t *epd_list = &_epd_list[0];

