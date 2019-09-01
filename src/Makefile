
CC := gcc
AR := ar
RANLIB := ranlib

CFLAGS ?= -g
CFLAGS += $(addprefix -I,$(wildcard lib/*))
CFLAGS += $(shell pkg-config --cflags MagickWand)
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -Wall -pedantic -I. -DRPI=1 -DUSE_BCM2835_LIB=1
#CFLAGS += -Wall -pedantic -I. -DRPI=1 -DUSE_DEV_LIB=1
LDFLAGS += $(shell pkg-config --libs MagickWand) -L. -lws -Wl,--gc-sections

PRGNAME = wsepd-image
LIBSRCS = $(sort $(wildcard lib/*/*.c))
LIBOBJS = $(LIBSRCS:.c=.o)

PRGS = wsepd-image it8951-image

all: $(PRGS)

define progdeps
$(1): libws.a $(1).o
	$(CC) $(CFLAGS) -o $$@ $(1).o $(LDFLAGS)
endef

$(foreach file,$(PRGS),$(eval $(call progdeps,$(file))))

install: all
	for p in $(PRGS); do install -D -m 0755 $$p $(DESTDIR)/usr/bin/$$p ; done

clean:
	rm -rf $(PRGOBJS) $(LIBOBJS) libws.a $(PRGS)

libws.a: $(LIBOBJS)
	$(AR) rcv $@ $(LIBOBJS)
	$(RANLIB) $@

