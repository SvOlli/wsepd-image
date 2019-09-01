/*****************************************************************************
* | File        :   EPD_Get_4in2.c
* | Author      :   SvOlli
* | Function    :   Electronic paper driver wrapper
*****************************************************************************/

#include "EPD_4in2.h"
#include "EPD_Get.h"

epd_api_t setup_epd_4in2()
{
   return setup_epd( EPD_4IN2_WIDTH, EPD_4IN2_HEIGHT, 1,
                     EPD_4IN2_Init,
                     EPD_4IN2_Clear,
                     EPD_4IN2_Display,
                     EPD_4IN2_Sleep );
}
