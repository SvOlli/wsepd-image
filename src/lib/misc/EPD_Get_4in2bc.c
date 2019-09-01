/*****************************************************************************
* | File        :   EPD_Get_4in2bc.c
* | Author      :   SvOlli
* | Function    :   Electronic paper driver wrapper
*****************************************************************************/

#include "EPD_4in2bc.h"
#include "EPD_Get.h"

static void epd_4in2bc_display( uint8_t *image )
{
   EPD_4IN2BC_Display( image, image + EPD_BITPLANE_OFFSET( EPD_4IN2BC_WIDTH, EPD_4IN2BC_HEIGHT ) );
}

epd_api_t setup_epd_4in2bc()
{
   return setup_epd( EPD_4IN2BC_WIDTH, EPD_4IN2BC_HEIGHT, 2,
                     EPD_4IN2BC_Init,
                     EPD_4IN2BC_Clear,
                     epd_4in2bc_display,
                     EPD_4IN2BC_Sleep );
}
