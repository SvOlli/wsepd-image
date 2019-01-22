
CC := gcc
AR := ar
RANLIB := ranlib

CFLAGS += $(shell pkg-config --cflags MagickWand gdlib)
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -Wall -pedantic
#CFLAGS += -Os
CFLAGS += -g
CFLAGS += -I..
LDFLAGS += $(shell pkg-config --libs MagickWand gdlib) -L. -lws -Wl,--gc-sections

all: sim1bp sim4bp

clean:
	rm -f *.a *.o sim1bp

libws.a: ../img_load.o
	$(AR) rcv $@ $^

sim1bp: libws.a sim1bp.o
	$(CC) $(CFLAGS) -o $@ sim1bp.o $(LDFLAGS)

sim4bp: libws.a sim4bp.o
	$(CC) $(CFLAGS) -o $@ sim4bp.o $(LDFLAGS)

