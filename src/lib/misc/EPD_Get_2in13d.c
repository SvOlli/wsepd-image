/*****************************************************************************
* | File        :   EPD_Get_2in13d.c
* | Author      :   SvOlli
* | Function    :   Electronic paper driver wrapper
*****************************************************************************/

#include "EPD_2in13d.h"
#include "EPD_Get.h"

epd_api_t setup_epd_2in13d()
{
   return setup_epd( EPD_2IN13D_WIDTH, EPD_2IN13D_HEIGHT, 1,
                     EPD_2IN13D_Init,
                     EPD_2IN13D_Clear,
                     EPD_2IN13D_Display,
                     EPD_2IN13D_Sleep );
}
