#!/bin/sh

bcm2835url="http://www.airspayce.com/mikem/bcm2835/"

getgit()
{
   local url="${1}"
   local dir="${2}"
   if [ -d "${dir}" ]; then
      echo "updating ${dir}"
      (cd "${dir}";git pull)
   else
      echo "getting ${dir}"
      git clone "${url}" "${dir}"
   fi
   echo
}

cd "$(dirname "${0}")"

mkdir -p extern

getgit git://github.com/waveshare/e-Paper.git extern/e-Paper
getgit git://github.com/waveshare/IT8951.git  extern/IT8951

downloadurl="$(wget -O - "${bcm2835url}" | grep "${bcm2835url}" | sed 's,.*"\('"${bcm2835url}"'[^"]*\)".*,\1,')"
wget --referer="${bcm2835url}" -c -P extern "${downloadurl}"
cd extern
tar xf "${downloadurl##*/}"


