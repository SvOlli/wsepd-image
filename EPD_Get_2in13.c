/*****************************************************************************
* | File        :   EPD_Get_2in13.c
* | Author      :   SvOlli
* | Function    :   Electronic paper driver wrapper
*****************************************************************************/

#include "EPD_2in13.h"
#include "EPD_Get.h"

static UBYTE epd_init()
{
   return EPD_Init(lut_full_update);
}

epd_api_t setup_epd_2in13()
{
   return setup_epd( EPD_WIDTH, EPD_HEIGHT, 1,
                     epd_init,
                     EPD_Clear,
                     EPD_Display,
                     EPD_Sleep );
}

