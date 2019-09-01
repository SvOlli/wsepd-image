#!/bin/bash

template()
{
   local name="${1}"
   local NAME="${name^^}"
   local layers="${2}"
   local output="EPD_Get_${name}.c"

   if [ -f "${output}" ]; then
      return
   fi

cat >"${output}" <<EOF
/*****************************************************************************
* | File        :   EPD_Get_${name}.c
* | Author      :   SvOlli
* | Function    :   Electronic paper driver wrapper
*****************************************************************************/

#include "EPD_${name}.h"
#include "EPD_Get.h"

EOF

if [ ${layers} -gt 1 ]; then
disp_function="epd_${name}_display"
cat >>"${output}" <<EOF
static void ${disp_function}( uint8_t *image )
{
   EPD_${name^^}_Display( image, image + EPD_BITPLANE_OFFSET( EPD_${NAME}_WIDTH, EPD_${NAME}_HEIGHT ) );
}

EOF
else
disp_function="EPD_${NAME}_Display"
fi

cat >>"${output}" <<EOF
epd_api_t setup_epd_${name,,}()
{
   return setup_epd( EPD_${NAME}_WIDTH, EPD_${NAME}_HEIGHT, ${layers},
                     EPD_${NAME}_Init,
                     EPD_${NAME}_Clear,
                     ${disp_function},
                     EPD_${NAME}_Sleep );
}
EOF

   echo "${output} generated"
}

template 1in54    1
template 1in54_V2 1
template 1in54b   2
template 1in54c   2
template 2in13    1
template 2in13_V2 1
template 2in13bc  2
template 2in13d   1
template 2in7     1
template 2in7b    2
template 2in9     1
template 2in9bc   2
template 2in9d    1
template 4in2     1
template 4in2bc   2
template 5in83    1
template 5in83bc  2
template 7in5     1
template 7in5bc   2

