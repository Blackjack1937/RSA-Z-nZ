CC      = gcc
CFLAGS  = -Wall -Wextra -O2

# Default target: build all
all: test_mybigint test-znz test-rsa test-rsa-extended f128-demo f128-zech-demo

###############################################################################
# (1) Multi-Precision inside src/Z-nZ/multi-precision
###############################################################################
test_mybigint: src/Z-nZ/multi-precision/mybigint.o \
               src/Z-nZ/multi-precision/test_mybigint.o
	$(CC) $(CFLAGS) -o $@ $^

src/Z-nZ/multi-precision/mybigint.o: src/Z-nZ/multi-precision/mybigint.c \
                                     src/Z-nZ/multi-precision/mybigint.h
	$(CC) $(CFLAGS) -c $< -o $@

src/Z-nZ/multi-precision/test_mybigint.o: src/Z-nZ/multi-precision/test_mybigint.c \
                                          src/Z-nZ/multi-precision/mybigint.h
	$(CC) $(CFLAGS) -c $< -o $@

###############################################################################
# (2) 64-bit Z/nZ: znz + rsa + test programs
###############################################################################
test-znz: src/Z-nZ/znz.o src/Z-nZ/test-znz.o
	$(CC) $(CFLAGS) -o $@ $^

test-rsa: src/Z-nZ/znz.o src/Z-nZ/rsa.o src/Z-nZ/test-rsa.o
	$(CC) $(CFLAGS) -o $@ $^

test-rsa-extended: src/Z-nZ/znz.o src/Z-nZ/rsa.o src/Z-nZ/test-rsa-extended.o
	$(CC) $(CFLAGS) -o $@ $^

# Build znz
src/Z-nZ/znz.o: src/Z-nZ/znz.c src/Z-nZ/znz.h
	$(CC) $(CFLAGS) -c $< -o $@

# Build rsa
src/Z-nZ/rsa.o: src/Z-nZ/rsa.c src/Z-nZ/rsa.h src/Z-nZ/znz.h
	$(CC) $(CFLAGS) -c $< -o $@

# Build test-znz
src/Z-nZ/test-znz.o: src/Z-nZ/test-znz.c src/Z-nZ/znz.h
	$(CC) $(CFLAGS) -c $< -o $@

# Build test-rsa
src/Z-nZ/test-rsa.o: src/Z-nZ/test-rsa.c src/Z-nZ/rsa.h src/Z-nZ/znz.h
	$(CC) $(CFLAGS) -c $< -o $@

# Build test-rsa-extended
src/Z-nZ/test-rsa-extended.o: src/Z-nZ/test-rsa-extended.c \
                              src/Z-nZ/rsa.h src/Z-nZ/znz.h
	$(CC) $(CFLAGS) -c $< -o $@

###############################################################################
# (3) Galois Field F128 in src/Galois
###############################################################################
f128-demo: src/Galois/f128.o src/Galois/f128-demo.o
	$(CC) $(CFLAGS) -o $@ $^

f128-zech-demo: src/Galois/f128.o src/Galois/f128-zech.o src/Galois/f128-zech-demo.o
	$(CC) $(CFLAGS) -o $@ $^

# Build f128
src/Galois/f128.o: src/Galois/f128.c src/Galois/f128.h
	$(CC) $(CFLAGS) -c $< -o $@

# Build f128-demo
src/Galois/f128-demo.o: src/Galois/f128-demo.c src/Galois/f128.h
	$(CC) $(CFLAGS) -c $< -o $@

# Build f128-zech
src/Galois/f128-zech.o: src/Galois/f128-zech.c src/Galois/f128.h
	$(CC) $(CFLAGS) -c $< -o $@

# Build f128-zech-demo
src/Galois/f128-zech-demo.o: src/Galois/f128-zech-demo.c src/Galois/f128.h
	$(CC) $(CFLAGS) -c $< -o $@

###############################################################################
# Clean
###############################################################################
clean:
	rm -f src/Z-nZ/multi-precision/*.o \
	      src/Z-nZ/*.o \
	      src/Galois/*.o \
	      test_mybigint test-znz test-rsa test-rsa-extended f128-demo f128-zech-demo
