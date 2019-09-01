/*****************************************************************************
* | File        :   EPD_Get_7in5.c
* | Author      :   SvOlli
* | Function    :   Electronic paper driver wrapper
*****************************************************************************/

#include "EPD_7in5.h"
#include "EPD_Get.h"

epd_api_t setup_epd_7in5()
{
   return setup_epd( EPD_7IN5_WIDTH, EPD_7IN5_HEIGHT, 1,
                     EPD_7IN5_Init,
                     EPD_7IN5_Clear,
                     EPD_7IN5_Display,
                     EPD_7IN5_Sleep );
}

