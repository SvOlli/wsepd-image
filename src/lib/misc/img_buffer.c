/*****************************************************************************
* | File        :   img_buffer.c
* | Author      :   SvOlli
* | Function    :   image loading and converting using ImageMagick
*****************************************************************************/

#include "img_load.h"

#include <string.h>


void buffer_clean( uint8_t *buffer, const epd_api_t *epd, uint8_t bitplane )
{
   memset( buffer + (epd->datasize * bitplane), 0xff, epd->datasize );
}


void buffer_invert( uint8_t *buffer, const epd_api_t *epd, uint8_t bitplane )
{
   uint8_t *b = buffer + (epd->datasize * bitplane);
   int i = 0;

   while( i++ < epd->datasize )
   {
      *(b++) ^= 0xff;
   }
}


void buffer_img( uint8_t *buffer, const epd_api_t *epd, uint8_t bitplane,
                 MagickWand *m_wand, PixelWand *p_wand )
{
   uint16x2_t imagesize, imagepos, offset, disppos;
   uint8_t    *linestart;
   MagickPixelPacket pix;

   imagesize.x = MagickGetImageWidth( m_wand );
   imagesize.y = MagickGetImageHeight( m_wand );

   /* get top left corner for image to display */
   offset.x = (epd->dispsize.x - imagesize.x) / 2;
   offset.y = (epd->dispsize.y - imagesize.y) / 2;

   for( imagepos.y = 0; imagepos.y < imagesize.y; ++imagepos.y )
   {
      disppos.y = offset.y + imagepos.y;
      linestart = buffer + (epd->datasize * bitplane) + (epd->linestep * disppos.y);
      for( imagepos.x = 0; imagepos.x < imagesize.x; ++imagepos.x )
      {
         disppos.x = offset.x + imagepos.x;
         uint8_t bitmask = 1 << (~(disppos.x) & 0x7);
         MagickGetImagePixelColor( m_wand, imagepos.x, imagepos.y, p_wand );
         PixelGetMagickColor( p_wand, &pix );
         if( pix.red > 0.1 )
         {
            *(linestart + (disppos.x / 8)) |= bitmask;
         }
         else
         {
            *(linestart + (disppos.x / 8)) &= ~bitmask;
         }
      } 
   }
}

