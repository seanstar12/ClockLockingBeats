CC=~/lib/android-18-ndk-toolchain/bin/arm-linux-androideabi-gcc
CFLAGS?=-Wall -g -D_GNU_SOURCE
TARGETS=oc-me

all::	$(TARGETS)

oc-me: oc-me.c
	$(CC) -o oc-me oc-me.c $(CFLAGS)

clean:
	rm -f *~ *.o $(TARGETS)

