CC      = gcc
CFLAGS  = -Wall -Wextra -O2

all: test-znz test-rsa test-rsa-extended
test-znz: znz.o test-znz.o
	$(CC) $(CFLAGS) -o $@ $^

test-znz.o: test-znz.c znz.h
	$(CC) $(CFLAGS) -c test-znz.c
znz.o: znz.c znz.h
	$(CC) $(CFLAGS) -c znz.c

test-rsa: znz.o rsa.o test-rsa.o
	$(CC) $(CFLAGS) -o $@ $^

test-rsa.o: test-rsa.c rsa.h znz.h
	$(CC) $(CFLAGS) -c test-rsa.c

rsa.o: rsa.c rsa.h znz.h
	$(CC) $(CFLAGS) -c rsa.c

test-rsa-extended: znz.o rsa.o test-rsa-extended.o
	$(CC) $(CFLAGS) -o $@ $^

test-rsa-extended.o: test-rsa-extended.c rsa.h znz.h
	$(CC) $(CFLAGS) -c test-rsa-extended.c


clean:
	rm -f *.o test-znz test-rsa
