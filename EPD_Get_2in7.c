/*****************************************************************************
* | File        :   EPD_Get_2in7.c
* | Author      :   SvOlli
* | Function    :   Electronic paper driver wrapper
*****************************************************************************/

#include "EPD_2in7.h"
#include "EPD_Get.h"

epd_api_t setup_epd_2in7()
{
   return setup_epd( EPD_WIDTH, EPD_HEIGHT, 1,
                     EPD_Init,
                     EPD_Clear,
                     EPD_Display,
                     EPD_Sleep );
}
