/*****************************************************************************
* | File        :   EPD_Get_5in83b.c
* | Author      :   SvOlli
* | Function    :   Electronic paper driver wrapper
*****************************************************************************/

#include "EPD_5in83b.h"
#include "EPD_Get.h"

static void epd_display( uint8_t *image )
{
   EPD_Display( image, image + EPD_BITPLANESIZE );
}

epd_api_t setup_epd_5in83b()
{
   return setup_epd( EPD_WIDTH, EPD_HEIGHT, 2,
                     EPD_Init,
                     EPD_Clear,
                     epd_display,
                     EPD_Sleep );
}

