/*****************************************************************************
* | File        :   EPD_Get_2in13_V2.c
* | Author      :   SvOlli
* | Function    :   Electronic paper driver wrapper
*****************************************************************************/

#include "EPD_2in13_V2.h"
#include "EPD_Get.h"

void epd_2in13_v2_init()
{
   EPD_2IN13_V2_Init( EPD_2IN13_V2_FULL );
}

epd_api_t setup_epd_2in13_v2()
{
   return setup_epd( EPD_2IN13_V2_WIDTH, EPD_2IN13_V2_HEIGHT, 1,
                     epd_2in13_v2_init,
                     EPD_2IN13_V2_Clear,
                     EPD_2IN13_V2_Display,
                     EPD_2IN13_V2_Sleep );
}
