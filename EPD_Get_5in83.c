/*****************************************************************************
* | File        :   EPD_Get_5in83.c
* | Author      :   SvOlli
* | Function    :   Electronic paper driver wrapper
*****************************************************************************/

#include "EPD_5in83.h"
#include "EPD_Get.h"

epd_api_t setup_epd_5in83()
{
   return setup_epd( EPD_WIDTH, EPD_HEIGHT, 1,
                     EPD_Init,
                     EPD_Clear,
                     EPD_Display,
                     EPD_Sleep );
}

