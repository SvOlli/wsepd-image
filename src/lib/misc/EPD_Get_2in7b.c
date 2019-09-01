/*****************************************************************************
* | File        :   EPD_Get_2in7b.c
* | Author      :   SvOlli
* | Function    :   Electronic paper driver wrapper
*****************************************************************************/

#include "EPD_2in7b.h"
#include "EPD_Get.h"

static void epd_2in7b_display( uint8_t *image )
{
   EPD_2IN7B_Display( image, image + EPD_BITPLANE_OFFSET( EPD_2IN7B_WIDTH, EPD_2IN7B_HEIGHT ) );
}

epd_api_t setup_epd_2in7b()
{
   return setup_epd( EPD_2IN7B_WIDTH, EPD_2IN7B_HEIGHT, 2,
                     EPD_2IN7B_Init,
                     EPD_2IN7B_Clear,
                     epd_2in7b_display,
                     EPD_2IN7B_Sleep );
}
