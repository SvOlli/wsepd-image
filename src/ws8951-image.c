#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include <IT8951.h>
#include <types.h>

extern IT8951DevInfo gstI80DevInfo;

int main( int argc, char *argv[] )
{
   uint16x2_t dispsize;

#if USE_BCM2835_LIB
   if( geteuid() )
   {
      fprintf( stderr, "this program must have root access. sorry.\n" );
      return 1;
   }
#endif

   if( IT8951_Init() )
   {
      fprintf( stderr, "IT8951_Init error!\n" );
      return 1;
   }
   dispsize.x = gstI80DevInfo.usPanelW;
   dispsize.y = gstI80DevInfo.usPanelH;
   printf( "dispsize = %dx%d\n", dispsize.x, dispsize.y );

   IT8951_Cancel();

   return 0;
}

