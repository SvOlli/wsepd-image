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
                     uint8_t(*init)(),
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
   { setup_epd_1in54,  "1.54",  "200x200" },
   { setup_epd_1in54b, "1.54b", "200x200, additional red or yellow color" },
   { setup_epd_2in13,  "2.13",  "122x250" },
   { setup_epd_2in13b, "2.13b", "104x212, additional red or yellow color" },
   { setup_epd_2in13d, "2.13d", "104x212, flexible" },
   { setup_epd_2in7,   "2.7",   "176x264" },
   { setup_epd_2in7b,  "2.7b",  "176x264, additional red color" },
   { setup_epd_2in9,   "2.9",   "128x294" },
   { setup_epd_2in9b,  "2.9b",  "128x294, additional red or yellow color" },
   { setup_epd_4in2,   "4.2",   "400x300" },
   { setup_epd_4in2b,  "4.2b",  "400x300, additional red or yellow color" },
   { setup_epd_5in83,  "5.83",  "600x448" },
   { setup_epd_5in83b, "5.83b", "600x448, additional red or yellow color" },
   { setup_epd_7in5,   "7.5",   "640x384" },
   { setup_epd_7in5b,  "7.5b",  "640x384, additional red or yellow color" },
   { 0, 0, 0 }
};

const epd_list_t *epd_list = &_epd_list[0];

