/*****************************************************************************
* | File        :   EPD_Get_1in54b.c
* | Author      :   SvOlli
* | Function    :   Electronic paper driver wrapper
*****************************************************************************/

#include "EPD_1in54b.h"
#include "EPD_Get.h"

static void epd_1in54b_display( uint8_t *image )
{
   EPD_1IN54B_Display( image, image + EPD_BITPLANE_OFFSET( EPD_1IN54B_WIDTH, EPD_1IN54B_HEIGHT ) );
}

epd_api_t setup_epd_1in54b()
{
   return setup_epd( EPD_1IN54B_WIDTH, EPD_1IN54B_HEIGHT, 2,
                     EPD_1IN54B_Init,
                     EPD_1IN54B_Clear,
                     epd_1in54b_display,
                     EPD_1IN54B_Sleep );
}
