/*****************************************************************************
* | File        :   EPD_Get_2in9.c
* | Author      :   SvOlli
* | Function    :   Electronic paper driver wrapper
*****************************************************************************/

#include "EPD_2in9.h"
#include "EPD_Get.h"

epd_api_t setup_epd_2in9()
{
   return setup_epd( EPD_2IN9_WIDTH, EPD_2IN9_HEIGHT, 1,
                     EPD_2IN9_Init,
                     EPD_2IN9_Clear,
                     EPD_2IN9_Display,
                     EPD_2IN9_Sleep );
}
