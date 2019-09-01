/*****************************************************************************
* | File        :   EPD_Get_7in5b.c
* | Author      :   SvOlli
* | Function    :   Electronic paper driver wrapper
*****************************************************************************/

#include "EPD_7in5bc.h"
#include "EPD_Get.h"

static void epd_7in5bc_display( uint8_t *image )
{
   EPD_7IN5BC_Display( image, image + EPD_BITPLANE_OFFSET( EPD_7IN5BC_WIDTH, EPD_7IN5BC_HEIGHT ) );
}

epd_api_t setup_epd_7in5bc()
{
   return setup_epd( EPD_7IN5BC_WIDTH, EPD_7IN5BC_HEIGHT, 2,
                     EPD_7IN5BC_Init,
                     EPD_7IN5BC_Clear,
                     epd_7in5bc_display,
                     EPD_7IN5BC_Sleep );
}

