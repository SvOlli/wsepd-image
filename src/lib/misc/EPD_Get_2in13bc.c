/*****************************************************************************
* | File        :   EPD_Get_2in13bc.c
* | Author      :   SvOlli
* | Function    :   Electronic paper driver wrapper
*****************************************************************************/

#include "EPD_2in13bc.h"
#include "EPD_Get.h"

static void epd_2in13bc_display( uint8_t *image )
{
   EPD_2IN13BC_Display( image, image + EPD_BITPLANE_OFFSET( EPD_2IN13BC_WIDTH, EPD_2IN13BC_HEIGHT ) );
}

epd_api_t setup_epd_2in13bc()
{
   return setup_epd( EPD_2IN13BC_WIDTH, EPD_2IN13BC_HEIGHT, 2,
                     EPD_2IN13BC_Init,
                     EPD_2IN13BC_Clear,
                     epd_2in13bc_display,
                     EPD_2IN13BC_Sleep );
}
