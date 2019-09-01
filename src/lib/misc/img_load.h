/*****************************************************************************
* | File        :   img_load.h
* | Author      :   SvOlli
* | Function    :   image loading and converting using ImageMagick
*****************************************************************************/

#ifndef __IMG_LOAD_H__
#define __IMG_LOAD_H__ __IMG_LOAD_H__

#include "types.h"
#include <wand/MagickWand.h>

typedef enum {
   IMG_LOAD_NONE       = 0,
   IMG_LOAD_ROTATE_90  = 1 << 0 | 0 << 1,
   IMG_LOAD_ROTATE_180 = 0 << 0 | 1 << 1,
   IMG_LOAD_ROTATE_270 = 1 << 0 | 1 << 1,
   IMG_LOAD_ASPECT     = 1 << 2,
   IMG_LOAD_MONO       = 1 << 3,
   IMG_LOAD_GREYSCALE  = 1 << 4
} img_load_t;

/* calculate imagesize respecting aspect ratio */
uint16x2_t aspect( uint16x2_t display, uint16x2_t image );

/* load an image */
int img_load( MagickWand *m_wand, PixelWand *p_wand, const char *filename,
              uint16x2_t displaysize, img_load_t flags );

/* get greyscale value for image magick pixel */
float magick_greyscale( MagickPixelPacket *pix );

/* erase the buffer of a single bitplane */
void buffer_clean( uint8_t *buffer, const epd_api_t *epd, uint8_t bitplane );

/* invert the buffer of a single bitplane */
void buffer_invert( uint8_t *buffer, const epd_api_t *epd, uint8_t bitplane );

/* convert ImageMagick data to bitplane buffer */
void buffer_img( uint8_t *buffer, const epd_api_t *epd, uint8_t bitplane,
                 MagickWand *m_wand, PixelWand *p_wand );

/* sanity check: is hardware accessable */
int check_permissions();

void measure_start();
void measure_end( int show, const char *message );


#endif
