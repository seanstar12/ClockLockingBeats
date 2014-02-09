CC=~/lib/android-18-ndk-toolchain/bin/arm-linux-androideabi-gcc
CFLAGS?=-Wall -g -D_GNU_SOURCE
TARGETS=collatz-kit

all::	$(TARGETS)

collatz-kit:	collatz-kit.c
	$(CC) -o collatz-kit collatz-kit.c $(CFLAGS)

clean:
	rm -f *~ *.o $(TARGETS)

