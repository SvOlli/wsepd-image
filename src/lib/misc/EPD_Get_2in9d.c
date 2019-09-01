/*****************************************************************************
* | File        :   EPD_Get_2in9d.c
* | Author      :   SvOlli
* | Function    :   Electronic paper driver wrapper
*****************************************************************************/

#include "EPD_2in9d.h"
#include "EPD_Get.h"

epd_api_t setup_epd_2in9d()
{
   return setup_epd( EPD_2IN9D_WIDTH, EPD_2IN9D_HEIGHT, 1,
                     EPD_2IN9D_Init,
                     EPD_2IN9D_Clear,
                     EPD_2IN9D_Display,
                     EPD_2IN9D_Sleep );
}
