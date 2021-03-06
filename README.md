# wsepd-image #

A small tool to load an image to a waveshare e-paper display on RaspberryPi.
It started with just supporting the
[7.5inch](https://www.waveshare.com/wiki/7.5inch_e-Paper_HAT) version. After
that, the idea came up to support more than just one. And with a couple of
tricks, it was possible to support this as well. After an SDK update by
WaveShare some of those tricks were not needed anymore, and the files could
be taken unchanged. This lead to a full reorganization of the code.

On the Raspberry Pi you also have to make sure that SPI is enabled by setting
```
dtparam=spi=on
```
in `/boot/config.txt`. The line is already there, but commented out. You can
also use the `raspi-config` utility to enable it (in main menu select 5, and
then option P4).

## Building ##

```
apt-get install libmagickwand-dev
dpkg-buildpackage
dpkg -i ../wsepd-image_*.deb
```

## Supported Displays ##

| Type     | Tested by  | Comment                                            |
| -------- | ---------- | -------------------------------------------------- |
| 1in54    | (untested) |                                                    |
| 1in54_V2 | (untested) |                                                    |
| 1in54b   | (untested) |                                                    |
| 1in54c   | (untested) |                                                    |
| 2in13    | Author     |                                                    |
| 2in13_V2 | (untested) |                                                    |
| 2in13bc  | (untested) |                                                    |
| 2in13d   | (untested) |                                                    |
| 2in7     | (untested) |                                                    |
| 2in7b    | Author     |                                                    |
| 2in9     | (untested) |                                                    |
| 2in9bc   | (untested) |                                                    |
| 2in9d    | (untested) |                                                    |
| 4in2     | (untested) |                                                    |
| 4in2bc   | (untested) |                                                    |
| 5in83    | (untested) |                                                    |
| 5in83bc  | (untested) |                                                    |
| 7in5     | Author     |                                                    |
| 7in5bc   | (untested) |                                                    |
| it8951   | Author     | separate tool: it8951-image, 4 bit greyscale       |

### Bi-color Displays ###

There are displays capable of displaying a second color (red or yellow,
depending on the model). These are handled differently the it might be
expected. Images are always converted to a monochrome bitplane. It is possible
to add a secondary image that will be displayed using the "other color". Think
of it as a watermark image.

Also it seems like you can switch to the single bitplane driver to get a
faster update. Note: this has been only tested on a "2.7b" display using the
"2.7" driver.

### IT8951 Displays ###

There are displays available using an IT8951 controller. For those a separate
tool `it8951-image` has been written. Since this controller can report the
size of a display, no manual selection of the display is necessary.

## Supported Platforms ##

All platforms the Waveshare SDK supports.

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
