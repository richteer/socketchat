CC=gcc
CFLAGS=-Wall

all: network.o

tests: test_number.c number.h number.c
	@echo "Building test_number"
	${CC} ${CFLAGS} test_number.c number.c -lgmp

test_eg: test_eg.c elgamal.h elgamal.c
	@echo "Building test_eg"
	${CC} ${CFLAGS} test_eg.c elgamal.c -lgmp

network.o: network.c network.h
	@echo "Building the Network Library"
	${CC} ${CFLAGS} -c $< -o $@

clean: 
	rm -rf *.o a.out
