/*****************************************************************************
* | File        :   EPD_Get_5in83bc.c
* | Author      :   SvOlli
* | Function    :   Electronic paper driver wrapper
*****************************************************************************/

#include "EPD_5in83bc.h"
#include "EPD_Get.h"

static void epd_5in83bc_display( uint8_t *image )
{
   EPD_5IN83BC_Display( image, image + EPD_BITPLANE_OFFSET( EPD_5IN83BC_WIDTH, EPD_5IN83BC_HEIGHT ) );
}

epd_api_t setup_epd_5in83bc()
{
   return setup_epd( EPD_5IN83BC_WIDTH, EPD_5IN83BC_HEIGHT, 2,
                     EPD_5IN83BC_Init,
                     EPD_5IN83BC_Clear,
                     epd_5in83bc_display,
                     EPD_5IN83BC_Sleep );
}
