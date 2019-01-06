/*****************************************************************************
* | File        :   EPD_Get_4in2.c
* | Author      :   SvOlli
* | Function    :   Electronic paper driver wrapper
*****************************************************************************/

#include "EPD_4in2.h"
#include "EPD_Get.h"

epd_api_t setup_epd_4in2()
{
   return setup_epd( EPD_WIDTH, EPD_HEIGHT, 1,
                     EPD_Init,
                     EPD_Clear,
                     EPD_Display,
                     EPD_Sleep );
}

