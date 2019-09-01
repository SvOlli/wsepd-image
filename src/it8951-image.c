/*****************************************************************************
* | File        :   wsepd-image.c
* | Author      :   SvOlli
* | Function    :   main program for e-paper displays based on IT8951
*****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <wand/MagickWand.h>

#include <IT8951.h>
#include <types.h>
#include <img_load.h>

/* set in library: IT8951.c */
extern IT8951DevInfo gstI80DevInfo;
extern uint8_t *gpFrameBuf;
extern uint32_t gulImgBufAddr;
void IT8951WaitForDisplayReady();
void IT8951HostAreaPackedPixelWrite(IT8951LdImgInfo* pstLdImgInfo,IT8951AreaImgInfo* pstAreaImgInfo);
void IT8951DisplayArea(uint16_t usX, uint16_t usY, uint16_t usW, uint16_t usH, uint16_t usDpyMode);

typedef enum {
   FLAGS_NONE    = 0,
   FLAGS_SHOWTIME = 1 << 0
} flags_t;

void help( const char *argv0, int exitcode )
{
   FILE *f = exitcode ? stderr : stdout;

   fprintf( f,
            "%s: show image on e-paper IT8951 display\n\n"
            "-a\tdon't keep aspect ratio\n"
            "-d #\tdelay between images\n"
            "-e $\te-paper driver to use (mandatory)\n"
            "-h\thelp\n"
            "-i\tinvert image\n"
            "-r #\trotate 90, 180 or 270 degrees\n"
            "-t\tshow time spent to transfer image (without calculations)\n"
            , argv0 );

   exit( exitcode );
}


int main( int argc, char *argv[] )
{
   MagickWand  *m_wand = NULL;
   PixelWand   *p_wand = NULL;
   int         opt;
   int         i;
   img_load_t  load_cfg = IMG_LOAD_ASPECT | IMG_LOAD_GREYSCALE;
   long        delay = 0;
   flags_t     flags = FLAGS_NONE;
   uint16x2_t  dispsize;
   uint16x2_t  imagesize;
   uint16x2_t  imagestart;
   uint16x2_t  imagepos;
   IT8951LdImgInfo stLdImgInfo;
   IT8951AreaImgInfo stAreaImgInfo;

   while( (opt = getopt( argc, argv, "A:C:IR:ad:e:hir:t" )) != -1 )
   {
      switch( opt )
      {
      case 'a':
         load_cfg &= ~IMG_LOAD_ASPECT;
         break;
      case 'd':
         delay = strtol( optarg, 0, 0 );
         break;
      case 'h':
         help( argv[0], 0 );
         break;
      case 'r':
         switch( strtol( optarg, 0, 0 ) % 360 )
         {
         case 0:
            break;
         case 90:
            load_cfg |= IMG_LOAD_ROTATE_90;
            break;
         case 180:
            load_cfg |= IMG_LOAD_ROTATE_180;
            break;
         case 270:
            load_cfg |= IMG_LOAD_ROTATE_270;
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

   if( check_permissions() )
   {
      exit(9);
   }

   measure_start();
   if( IT8951_Init() )
   {
      fprintf( stderr, "IT8951_Init error!\n" );
      return 1;
   }
   measure_end( flags & FLAGS_SHOWTIME, "time to init display" );
   dispsize.x = gstI80DevInfo.usPanelW;
   dispsize.y = gstI80DevInfo.usPanelH;

   /* setup ImageMagick stuff */
   MagickWandGenesis();
   m_wand = NewMagickWand();
   p_wand = NewPixelWand();

   /* TODO: drop "slideshow mode" and just display one image? */
   for( i = optind; i < argc; ++i )
   {
      measure_start();
      if( img_load( m_wand, p_wand, argv[i], dispsize, load_cfg ) )
      {
         continue;
      }
      measure_end( flags & FLAGS_SHOWTIME, "time to load image" );

      if( delay && (i != optind) )
      {
         sleep( delay );
      }

      measure_start();
      EPD_Clear( 0xFF );
      //buffer_img( buffer_1, &epd, 0, m_wand, p_wand );
      imagesize.x = MagickGetImageWidth( m_wand );
      imagesize.y = MagickGetImageHeight( m_wand );
      imagestart.x = (dispsize.x - imagesize.x) / 2;
      imagestart.y = (dispsize.y - imagesize.y) / 2;

      for( imagepos.y = 0; imagepos.y < imagesize.y; ++imagepos.y )
      {
         for( imagepos.x = 0; imagepos.x < imagesize.x; ++imagepos.x )
         {
            MagickGetImagePixelColor( m_wand, imagepos.x, imagepos.y, p_wand );
            float bright = PixelGetRed( p_wand );
            EPD_DrawPixel( imagepos.x + imagestart.x, imagepos.y + imagestart.y, (uint8_t)(bright * 255.999) );
         }
      }
      measure_end( flags & FLAGS_SHOWTIME, "time to convert image" );

      IT8951WaitForDisplayReady();

      measure_start();
      //Setting Load image information
      stLdImgInfo.ulStartFBAddr    = (uint32_t)gpFrameBuf;
      stLdImgInfo.usEndianType     = IT8951_LDIMG_L_ENDIAN;
      stLdImgInfo.usPixelFormat    = IT8951_8BPP;
      stLdImgInfo.usRotate         = IT8951_ROTATE_0;
      stLdImgInfo.ulImgBufBaseAddr = gulImgBufAddr;
      //Set Load Area
      stAreaImgInfo.usX      = 0;
      stAreaImgInfo.usY      = 0;
      stAreaImgInfo.usWidth  = gstI80DevInfo.usPanelW;
      stAreaImgInfo.usHeight = gstI80DevInfo.usPanelH;

      //Load Image from Host to IT8951 Image Buffer
      IT8951HostAreaPackedPixelWrite(&stLdImgInfo, &stAreaImgInfo);//Display function 2
      //Display Area ?V (x,y,w,h) with mode 2 for fast gray clear mode - depends on current waveform
      IT8951DisplayArea(0,0, gstI80DevInfo.usPanelW, gstI80DevInfo.usPanelH, 2);

      measure_end( flags & FLAGS_SHOWTIME, "time to transfer image" );

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

   measure_start();
   IT8951_Cancel();
   measure_end( flags & FLAGS_SHOWTIME, "time to close display" );

   return 0;
}

