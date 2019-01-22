/*****************************************************************************
* | File        :   main.c
* | Author      :   SvOlli
* | Function    :   image loading using ImageMagick
*****************************************************************************/

#include <gd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wand/MagickWand.h>

#include "img_load.h"


void help( const char *argv0, int exitcode )
{
   FILE *f = exitcode ? stderr : stdout;

   fprintf( f,
            "%s: convert image to 1 bitplane\n\n"
            "-a\tdon't keep aspect ratio\n"
            "-h\thelp\n"
            "-i\tinput image filename\n"
            "-o\toutput image filename\n"
            "-x\tx-size of image\n"
            "-y\ty-size of image\n"
            , argv0 );

   exit( exitcode );
}


int write4bp( MagickWand *m_wand, PixelWand *p_wand, const char *outfilename )
{
   MagickPixelPacket pix;
   uint16x2_t        imagepos;
   int               i, colors[16];
   gdImagePtr        gdi;

   /* allocate gdlib stuff */
   gdi = gdImageCreate( MagickGetImageWidth( m_wand ),
                        MagickGetImageHeight( m_wand ) );
   for( i = 0; i < 16; ++i )
   {
      colors[i] = gdImageColorAllocate( gdi, 0x11*i, 0x11*i, 0x11*i );
   }
   for( imagepos.y = 0; imagepos.y < gdi->sy; ++imagepos.y )
   {
      for( imagepos.x = 0; imagepos.x < gdi->sx; ++imagepos.x )
      {
         MagickGetImagePixelColor( m_wand, imagepos.x, imagepos.y, p_wand );
         float bright = PixelGetRed( p_wand );
         int index = (int)(15.999*bright);
         gdImageSetPixel( gdi, imagepos.x, imagepos.y, colors[index] );
      } 
   }
   gdImageFile( gdi, outfilename );

   /* clean up gdlib stuff */
   gdImageDestroy( gdi );

   return 0;
}


int main( int argc, char *argv[] )
{
   MagickWand        *m_wand = NULL;
   PixelWand         *p_wand = NULL;
   int               opt;
   img_load_t        load_cfg = IMG_LOAD_ASPECT | IMG_LOAD_GREYSCALE;
   char              *infilename = NULL;
   char              *outfilename = NULL;
   uint16x2_t        dispsize = {0,0};

   if( argc == 1 )
   {
      help( argv[0], 0 );
   }

   while( (opt = getopt( argc, argv, "ahi:o:x:y:" )) != -1 )
   {
      switch( opt )
      {
      case 'a':
         load_cfg &= ~IMG_LOAD_ASPECT;
         break;
      case 'h':
         help( argv[0], 0 );
         break;
      case 'i':
         infilename = optarg;
         break;
      case 'o':
         outfilename = optarg;
         break;
      case 'x':
         dispsize.x = strtol( optarg, 0, 0 );
         break;
      case 'y':
         dispsize.y = strtol( optarg, 0, 0 );
         break;
      default:
         break;
      }
   }
   
   /* sanity checks */
   if( !infilename || !outfilename || !dispsize.x || ! dispsize.y )
   {
      fprintf( stderr, "parameters -i, -o, -x, -y must be set\n" );
      return 1;
   }

   /* setup ImageMagick stuff */
   MagickWandGenesis();
   m_wand = NewMagickWand();
   p_wand = NewPixelWand();

   if( img_load( m_wand, p_wand, infilename, dispsize, load_cfg ) )
   {
      fprintf( stderr, "image load failed\n" );
      return 1;
   }

   write4bp( m_wand, p_wand, outfilename );

   /* clean up ImageMagick stuff */
   if( m_wand )
   {
      m_wand = DestroyMagickWand( m_wand );
   }
   if( p_wand )
   {
      p_wand = DestroyPixelWand( p_wand );
   }
   MagickWandTerminus();

   return 0;
}
