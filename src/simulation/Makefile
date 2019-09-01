
PRGS = sim1bp sim4bp

CC := gcc
AR := ar
RANLIB := ranlib

CFLAGS += $(shell pkg-config --cflags MagickWand gdlib)
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -Wall -pedantic
#CFLAGS += -Os
CFLAGS += -g
CFLAGS += -I../lib/misc
LDFLAGS += $(shell pkg-config --libs MagickWand gdlib) -L. -lws -Wl,--gc-sections

all: $(PRGS)

clean:
	rm -f *.a *.o $(PRGS)

libws.a: ../lib/misc/img_load.o
	$(AR) rcv $@ $^

define progdeps
$(1): libws.a $(1).o
	$(CC) $(CFLAGS) -o $$@ $(1).o $(LDFLAGS)
endef

$(foreach file,$(PRGS),$(eval $(call progdeps,$(file))))

