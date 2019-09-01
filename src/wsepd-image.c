/*****************************************************************************
* | File        :   wsepd-image.c
* | Author      :   SvOlli
* | Function    :   main program for waveshare e-paper displays
*****************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wand/MagickWand.h>

#include "DEV_Config.h"
#include "EPD_Get.h"
#include "img_load.h"

typedef enum {
   FLAGS_NONE    = 0,
   FLAGS_SHOWTIME = 1 << 0
} flags_t;

void help( const char *argv0, int exitcode )
{
   FILE *f = exitcode ? stderr : stdout;
   const epd_list_t *epds;

   fprintf( f,
            "%s: show image on e-paper display\n\n"
            "-a\tdon't keep aspect ratio\n"
            "-A\tdon't keep aspect ratio on color image\n"
            "-C $\tuse this image as color/watermark image\n"
            "-d #\tdelay between images\n"
            "-e $\te-paper driver to use (mandatory)\n"
            "-h\thelp\n"
            "-i\tinvert image\n"
            "-I\tinvert color image\n"
            "-r #\trotate 90, 180 or 270 degrees\n"
            "-R #\trotate color image 90, 180 or 270 degrees\n"
            "-t\tshow time spent to transfer image (without calculations)\n"
            "\ne-paper drivers supported are:\n"
            , argv0 );

   for( epds = epd_list; epds->setup; ++epds )
   {
      epd_api_t epd = epds->setup();
      fprintf( f, "\t- \"%s\":\t%3dx%3d%s\n", epds->name, epd.dispsize.x, epd.dispsize.y, epds->description );
   }

   exit( exitcode );
}


int main( int argc, char *argv[] )
{
   MagickWand        *m_wand = NULL;
   PixelWand         *p_wand = NULL;
   uint8_t           *buffer_1 = NULL;
   uint8_t           *buffer_2 = NULL;
   int               i;
   int               opt;
   long              delay = 0;
   img_load_t        load_cfg_1 = IMG_LOAD_MONO | IMG_LOAD_ASPECT | IMG_LOAD_GREYSCALE;
   img_load_t        load_cfg_2 = IMG_LOAD_MONO | IMG_LOAD_ASPECT | IMG_LOAD_GREYSCALE;
   bool              invert_1 = false;
   bool              invert_2 = false;
   const char        *filename_2 = NULL;
   const epd_list_t  *epds;
   epd_api_t         epd;
   flags_t           flags = FLAGS_NONE;
   struct timespec   tm1, tm2;

   if( argc == 1 )
   {
      help( argv[0], 0 );
   }

   memset( &epd, 0, sizeof( epd ) );
   while( (opt = getopt( argc, argv, "A:C:IR:ad:e:hir:t" )) != -1 )
   {
      switch( opt )
      {
      case 'A':
         load_cfg_2 &= ~IMG_LOAD_ASPECT;
         break;
      case 'C':
         filename_2 = optarg;
         break;
      case 'I':
         invert_2 = true;
         break;
      case 'R':
         switch( strtol( optarg, 0, 0 ) % 360 )
         {
         case 0:
            break;
         case 90:
            load_cfg_2 |= IMG_LOAD_ROTATE_90;
            break;
         case 180:
            load_cfg_2 |= IMG_LOAD_ROTATE_180;
            break;
         case 270:
            load_cfg_2 |= IMG_LOAD_ROTATE_270;
            break;
         default:
            exit(10);
         }
         break;
      case 'a':
         load_cfg_1 &= ~IMG_LOAD_ASPECT;
         break;
      case 'd':
         delay = strtol( optarg, 0, 0 );
         break;
      case 'e':
         if( epd.datasize )
         {
            fprintf( stderr, "more than one '-e' parameter.\n" );
            exit(11);
         }
         else
         {
            for( epds = epd_list; epds->setup; ++epds )
            {
               if( !strcasecmp( epds->name, optarg ) )
               {
                  epd = epds->setup();
               }
            }
            if( !epd.datasize )
            {
               fprintf( stderr, "unsupported display\n" );
               exit(14);
            }
         }
         break;
      case 'h':
         help( argv[0], 0 );
         break;
      case 'i':
         invert_1 = true;
         break;
      case 'r':
         switch( strtol( optarg, 0, 0 ) % 360 )
         {
         case 0:
            break;
         case 90:
            load_cfg_1 |= IMG_LOAD_ROTATE_90;
            break;
         case 180:
            load_cfg_1 |= IMG_LOAD_ROTATE_180;
            break;
         case 270:
            load_cfg_1 |= IMG_LOAD_ROTATE_270;
            break;
         default:
            exit(10);
         }
         break;
      case 't':
         flags |= FLAGS_SHOWTIME;
         break;
      default:
         break;
      }
   }

   if( !epd.datasize )
   {
      fprintf( stderr, "must specify '-e' parameter.\n" );
      exit(12);
   }

   if( check_permissions() )
   {
      exit(9);
   }

   if( (epd.bitplanes < 2) && filename_2 )
   {
      fprintf( stderr, "hardware does not support color/watermark image.\n" );
      exit(13);
   }

   /* setup buffer_1 for sending to hardware */
   buffer_1 = (uint8_t*)malloc( epd.datasize * epd.bitplanes );

   /* setup hardware stuff */
   DEV_Module_Init();
   epd.init();

   /* setup ImageMagick stuff */
   MagickWandGenesis();
   m_wand = NewMagickWand();
   p_wand = NewPixelWand();

   if( epd.bitplanes > 1 )
   {
      if( filename_2 )
      {
         buffer_2 = (uint8_t*)malloc( epd.datasize );
         buffer_clean( buffer_2, &epd, 0 );
         if( !img_load( m_wand, p_wand, filename_2, epd.dispsize, load_cfg_2 ) )
         {
            buffer_img( buffer_2, &epd, 0, m_wand, p_wand );
            if( invert_2 )
            {
               buffer_invert( buffer_2, &epd, 0 );
            }
         }
      }
      else
      {
         buffer_clean( buffer_1, &epd, 1 );
      }
   }

   /* TODO: drop "slideshow mode" and just display one image? */
   for( i = optind; i < argc; ++i )
   {
      if( img_load( m_wand, p_wand, argv[i], epd.dispsize, load_cfg_1 ) )
      {
         continue;
      }

      if( delay && (i != optind) )
      {
         sleep( delay );
      }

      buffer_clean( buffer_1, &epd, 0 );
      buffer_img( buffer_1, &epd, 0, m_wand, p_wand );
      if( invert_1 )
      {
         buffer_invert( buffer_1, &epd, 0 );
      }
      if( buffer_2 )
      {
         int j;
         uint8_t *d = buffer_1 + epd.datasize;
         const uint8_t *r = buffer_2;
         const uint8_t *b = buffer_1;
         for( j = 0; j < epd.datasize; ++j )
         {
            *(d++) = (*r++) | ~(*b++);
         }
      }

      clock_gettime( CLOCK_MONOTONIC, &tm1 );
      epd.display( buffer_1 );
      clock_gettime( CLOCK_MONOTONIC, &tm2 );
      if( flags & FLAGS_SHOWTIME )
      {
         const char plural[2] = "s";
         time_t secs  = tm2.tv_sec  - tm1.tv_sec;
         long   nsecs = tm2.tv_nsec - tm1.tv_nsec;
         if( nsecs < 0 )
         {
            nsecs += 1000000000;
            secs--;
         }
         printf( "time needed to display buffer%s: %ld.%03ld\n", &plural[epd.bitplanes > 1 ? 0 : 1], secs, nsecs/1000000 );
      }
   }

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

   /* clean up hardware stuff */
   epd.sleep();
   DEV_Module_Exit();
   free( buffer_1 );
   if( buffer_2 )
   {
      free( buffer_2 );
   }

   return 0;
}
