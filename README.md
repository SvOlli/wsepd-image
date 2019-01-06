# wsepd-image #

A small tool to load an image to a waveshare e-paper display on RaspberryPi.
It started with just supporting the
[7.5inch](https://www.waveshare.com/wiki/7.5inch_e-Paper_HAT) version. After
that, the idea came up to support more than just one. And with a couple of
tricks, it was possible to support this as well.

[wiringPi](http://wiringpi.com/) has been used as a backend, because there
are ports of it available for may other single board computers as well. On
the Raspberry Pi you also have to make sure that SPI is enabled by setting
```
dtparam=spi=on
```
in `/boot/config.txt`. The line is already there, but commented out. You can
also use the `raspi-config` utility to enable it (in main menu select 5, and
then option P4).

## Supported Displays ##

| Type   | Tested     |
| ------ | ---------- |
| 1in54  | (untested) |
| 1in54b | (untested) |
| 2in13  | Author     |
| 2in13b | (untested) |
| 2in13d | (untested) |
| 2in7   | (untested) |
| 2in7b  | Author     |
| 2in9   | (untested) |
| 2in9b  | (untested) |
| 4in2   | (untested) |
| 4in2b  | (untested) |
| 5in83  | (untested) |
| 5in83b | (untested) |
| 7in5   | Author     |
| 7in5b  | (untested) |

## Supported Platforms ##

The software has been written using a Raspberry Pi 3B+ and a Raspberry Pi Zero
W. Since wiringPi is used as a backend, this software might work with other
compatible backends such as [WiringOP](https://github.com/zhaolei/WiringOP) or
[gpio\_lib\_c](https://github.com/TinkerBoard/gpio_lib_c). Also note that a
Raspberry Pi is configured by default to allow access to GPIO without the need
for being root, while other implementations leave of this feature most of the
time.

But there also is a downside to Raspbian: the package of wiringPi is
suboptimal. Everything is just thrown into one big package called "wiringpi",
where it should be something like three packages: one containing the "gpio"
utility, one containing the runtime library and one containing everything
needed to compile your code (headers, link libraries, etc.). So if you're
porting this code to another platform you will most likely need to adjust
`debian/control` to match the packages needed in the `Build-Depends:` and
`Depends:` fields. There is a tool `debian/adjust-control.sh`, but this is far
from working in any configuration.

## Bi-color Displays ##

There are displays capable of displaying a second color (red or yellow,
depending on the model). These are handled differently the it might be
expected. Images are always converted to a monochrome bitplane. It is possible
to add a secondary image that will be displayed using the "other color". Think
of it as a watermark image.

Also it seems like you can switch to the single bitplane driver to get a
faster update. Note: this has been only tested on a "2.7b" display using the
"2.7" driver.

## Building ##

```
apt-get install libmagickwand-dev
dpkg-buildpackage
dpkg -i ../e-image_*.deb
```

## License ##

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documnetation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to  whom the Software is
furished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.


