/*****************************************************************************
* | File        :   EPD_Get_1in54c.c
* | Author      :   SvOlli
* | Function    :   Electronic paper driver wrapper
*****************************************************************************/

#include "EPD_1in54c.h"
#include "EPD_Get.h"

static void epd_1in54c_display( uint8_t *image )
{
   EPD_1IN54C_Display( image, image + EPD_BITPLANE_OFFSET( EPD_1IN54C_WIDTH, EPD_1IN54C_HEIGHT ) );
}

epd_api_t setup_epd_1in54c()
{
   return setup_epd( EPD_1IN54C_WIDTH, EPD_1IN54C_HEIGHT, 2,
                     EPD_1IN54C_Init,
                     EPD_1IN54C_Clear,
                     epd_1in54c_display,
                     EPD_1IN54C_Sleep );
}
