/*****************************************************************************
* | File        :   EPD_Get_2in13.c
* | Author      :   SvOlli
* | Function    :   Electronic paper driver wrapper
*****************************************************************************/

#include "EPD_2in13.h"
#include "EPD_Get.h"

void epd_2in13_init()
{
   EPD_2IN13_Init( EPD_2IN13_FULL );
}

epd_api_t setup_epd_2in13()
{
   return setup_epd( EPD_2IN13_WIDTH, EPD_2IN13_HEIGHT, 1,
                     epd_2in13_init,
                     EPD_2IN13_Clear,
                     EPD_2IN13_Display,
                     EPD_2IN13_Sleep );
}
