/*****************************************************************************
* | File        :   img_load.c
* | Author      :   SvOlli
* | Function    :   image loading and converting using ImageMagick
*****************************************************************************/

#include "img_load.h"

 
uint16x2_t aspect( uint16x2_t display, uint16x2_t image )
{
   uint16x2_t scaled = { 0, 0 };

   scaled.x = display.x;
   scaled.y = (uint32_t)image.y * display.x / image.x;

   if( scaled.y > display.y )
   {
      scaled.x = (uint32_t)image.x * display.y / image.y;
      scaled.y = display.y;
   }

   return scaled;
}


int img_load( MagickWand *m_wand, PixelWand *p_wand, const char *filename,
              uint16x2_t displaysize, img_load_t flags )
{
   if( MagickReadImage( m_wand, filename ) == MagickFalse )
   {
      return 1;
   }
   if( flags & IMG_LOAD_GREYSCALE )
   {
      uint16x2_t imagepos;
      MagickPixelPacket pix;
      PixelIterator *iterator = NULL;
      PixelWand **p_wands;
      int sy;

      iterator = NewPixelIterator( m_wand );
      sy = MagickGetImageHeight( m_wand );
      for( imagepos.y = 0; imagepos.y < sy; ++imagepos.y )
      {
         size_t sx;
         p_wands = PixelGetNextIteratorRow( iterator, &sx );
         for( imagepos.x = 0; imagepos.x < sx; ++imagepos.x )
         {
            PixelGetMagickColor( p_wands[imagepos.x], &pix );
            float grey = magick_greyscale( &pix );
            pix.red   = grey;
            pix.green = grey;
            pix.blue  = grey;
            PixelSetMagickColor( p_wands[imagepos.x], &pix );
         }
         PixelSyncIterator( iterator );
      }
      iterator = DestroyPixelIterator( iterator );
   }
   if( flags & IMG_LOAD_ASPECT )
   {
      uint16x2_t imagesize;
      if( flags & IMG_LOAD_ROTATE_90 )
      {
         imagesize.y = MagickGetImageWidth( m_wand );
         imagesize.x = MagickGetImageHeight( m_wand );
      }
      else
      {
         imagesize.x = MagickGetImageWidth( m_wand );
         imagesize.y = MagickGetImageHeight( m_wand );
      }
      displaysize = aspect( displaysize, imagesize );
   }
   switch( flags & IMG_LOAD_ROTATE_270 )
   {
   case IMG_LOAD_ROTATE_90:
      MagickRotateImage( m_wand, p_wand, 90.0 );
      break;
   case IMG_LOAD_ROTATE_180:
      MagickRotateImage( m_wand, p_wand, 180.0 );
      break;
   case IMG_LOAD_ROTATE_270:
      MagickRotateImage( m_wand, p_wand, 270.0 );
      break;
   default:
      break;
   }
   MagickResizeImage( m_wand, displaysize.x, displaysize.y, LanczosFilter, 1.0 );
   if( flags & IMG_LOAD_MONO )
   {
      MagickQuantizeImages( m_wand, 2, GRAYColorspace, 8, FloydSteinbergDitherMethod, 1 );
   }
   return 0;
}


float magick_greyscale( MagickPixelPacket *pix )
{
   return 0.299 * pix->red + 0.587 * pix->green + 0.114 * pix->blue;
}
