/*****************************************************************************
* | File        :   EPD_Get_2in7.c
* | Author      :   SvOlli
* | Function    :   Electronic paper driver wrapper
*****************************************************************************/

#include "EPD_2in7.h"
#include "EPD_Get.h"

epd_api_t setup_epd_2in7()
{
   return setup_epd( EPD_2IN7_WIDTH, EPD_2IN7_HEIGHT, 1,
                     EPD_2IN7_Init,
                     EPD_2IN7_Clear,
                     EPD_2IN7_Display,
                     EPD_2IN7_Sleep );
}
