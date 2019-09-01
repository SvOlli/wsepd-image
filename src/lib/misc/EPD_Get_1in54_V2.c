/*****************************************************************************
* | File        :   EPD_Get_1in54_V2.c
* | Author      :   SvOlli
* | Function    :   Electronic paper driver wrapper
*****************************************************************************/

#include "EPD_1in54_V2.h"
#include "EPD_Get.h"

epd_api_t setup_epd_1in54_v2()
{
   return setup_epd( EPD_1IN54_V2_WIDTH, EPD_1IN54_V2_HEIGHT, 1,
                     EPD_1IN54_V2_Init,
                     EPD_1IN54_V2_Clear,
                     EPD_1IN54_V2_Display,
                     EPD_1IN54_V2_Sleep );
}
