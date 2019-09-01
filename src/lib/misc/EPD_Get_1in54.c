/*****************************************************************************
* | File        :   EPD_Get_1in54.c
* | Author      :   SvOlli
* | Function    :   Electronic paper driver wrapper
*****************************************************************************/

#include "EPD_1in54.h"
#include "EPD_Get.h"

epd_api_t setup_epd_1in54()
{
   return setup_epd( EPD_1IN54_WIDTH, EPD_1IN54_HEIGHT, 1,
                     EPD_1IN54_Init,
                     EPD_1IN54_Clear,
                     EPD_1IN54_Display,
                     EPD_1IN54_Sleep );
}
