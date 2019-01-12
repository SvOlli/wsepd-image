#!/bin/bash

set -x
cd "$(dirname "${0}")"

# find potential libs
libs="$(apt-cache search "libwiring(pi|op)" | sed -e 's, - .*$,,')"

# find correct libraries
devlib="$(echo "${libs}" | grep -- '-dev$')"
rtlib="$(echo "${libs}" | grep -v 'dev')"

# use fallback, if necessary
devlib="${devlib:-wiringpi}"
rtlib="${rtlib:-wiringpi}"

sed control \
    -e "s,\(^Depends:.*\)[a-z]*wiring[a-z0-9]*\(.*\),\1${rtlib}\2," \
    -e "s,\(^Build-Depends:.*\)[a-z]*wiring[-a-z0-9]*\(.*\),\1${devlib}\2," \
    -i
