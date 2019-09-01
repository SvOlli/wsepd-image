/*****************************************************************************
* | File        :   img_load.c
* | Author      :   SvOlli
* | Function    :   check for sane environment
*****************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

static struct timespec measure_start_time;

int check_permissions()
{
#if USE_BCM2835_LIB
   if( geteuid() )
   {
      fprintf( stderr, "need to be run as root\n" );
      return 1;
   }
#endif
   return 0;
}

void measure_start()
{
   clock_gettime( CLOCK_MONOTONIC, &measure_start_time );
}

void measure_end( int show, const char *message )
{
   struct timespec measure_end_time;
   clock_gettime( CLOCK_MONOTONIC, &measure_end_time );

   if( !show )
   {
      return;
   }
   else
   {
      time_t secs  = measure_end_time.tv_sec  - measure_start_time.tv_sec;
      long   nsecs = measure_end_time.tv_nsec - measure_start_time.tv_nsec;
      if( nsecs < 0 )
      {
         nsecs += 1000000000;
         secs--;
      }
      printf( "%s: %ld.%03lds\n", message, secs, nsecs/1000000 );
   }
}
