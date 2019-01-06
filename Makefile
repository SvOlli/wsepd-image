
CC := gcc
AR := ar
RANLIB := ranlib

CFLAGS += $(shell pkg-config --cflags MagickWand)
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -Wall -pedantic
#CFLAGS += -Os
CFLAGS += -g
LDFLAGS += $(shell pkg-config --libs MagickWand) -L. -lws -lwiringPi -Wl,--gc-sections

PRGNAME = wsepd-image
PRGSRCS = $(sort $(wildcard [a-z]*.c))
PRGOBJS = $(PRGSRCS:.c=.o)
LIBSRCS = $(sort $(wildcard [A-Z]*.c))
LIBOBJS = $(LIBSRCS:.c=.o)

all: $(PRGNAME)

install: all
	install -D -m 0755 $(PRGNAME) $(DESTDIR)/usr/bin/$(PRGNAME)

clean:
	rm -rf $(PRGOBJS) $(LIBOBJS) libws.a $(PRGNAME)

libws.a: $(LIBOBJS)
	$(AR) rcv $@ $(LIBOBJS)

$(PRGNAME): libws.a $(PRGOBJS)
	$(CC) $(CFLAGS) -o $@ $(PRGOBJS) $(LDFLAGS)

