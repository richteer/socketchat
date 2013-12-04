CC=gcc
CFLAGS=-Wall

all: network.o tests

tests: test_number.c number.h number.c
	@echo "Building test_number"
	${CC} ${CFLAGS} test_number.c number.c -lgmp
<<<<<<< HEAD
=======

test_eg: test_eg.c elgamal.h elgamal.c
	@echo "Building test_eg"
	${CC} ${CFLAGS} test_eg.c elgamal.c -lgmp
>>>>>>> ba0b9110222de7ce999d5c4513f3163ba5d4993a

network.o: network.c network.h
	@echo "Building the Network Library"
	${CC} ${CFLAGS} -c $< -o $@

client: client.c
	@echo "Building the client"
	${CC} ${CFLAGS} $< -o $@

clean: 
	rm -rf *.o a.out client
