/*****************************************************************************
* | File        :   uint16x2.h
* | Author      :   SvOlli
* | Function    :   handy typedefs
*****************************************************************************/

#ifndef __TYPES_H__
#define __TYPES_H__ __TYPES_H__

#include <stdint.h>

typedef struct {
   uint16_t    x;
   uint16_t    y;
} uint16x2_t;

typedef struct {
   uint16x2_t dispsize;
   uint32_t   datasize;
   uint16_t   linestep;
   uint8_t    bitplanes;
   uint8_t    (*init)();
   void       (*clear)();
   void       (*display)(uint8_t *image);
   void       (*sleep)();
} epd_api_t;

typedef struct {
   epd_api_t  (*setup)();
   const char *name;
   const char *description;
} epd_list_t;

#endif

