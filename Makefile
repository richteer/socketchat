CC=gcc
CFLAGS=-Wall

all: network.o client test_number test_eg

test_number: test_number.c number.h number.c
	@echo "Building test_number"
	${CC} ${CFLAGS} test_number.c number.c -lgmp

test_eg: test_eg.c elgamal.h elgamal.c
	@echo "Building test_eg"
	${CC} ${CFLAGS} test_eg.c elgamal.c -lgmp

network.o: network.c network.h
	@echo "Building the Network Library"
	${CC} ${CFLAGS} -c $< -o $@

client: client.c network.o
	@echo "Building the client"
	${CC} ${CFLAGS} $^ -o $@

clean: 
	rm -rf *.o a.out client
