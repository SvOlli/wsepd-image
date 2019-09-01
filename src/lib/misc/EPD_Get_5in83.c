/*****************************************************************************
* | File        :   EPD_Get_5in83.c
* | Author      :   SvOlli
* | Function    :   Electronic paper driver wrapper
*****************************************************************************/

#include "EPD_5in83.h"
#include "EPD_Get.h"

epd_api_t setup_epd_5in83()
{
   return setup_epd( EPD_5IN83_WIDTH, EPD_5IN83_HEIGHT, 1,
                     EPD_5IN83_Init,
                     EPD_5IN83_Clear,
                     EPD_5IN83_Display,
                     EPD_5IN83_Sleep );
}
