CC=gcc
CFLAGS=-Wall

all: network.o

tests: test_number.c number.h number.c
	@echo "Building test_number"
	${CC} ${CFlAGS} test_number.c number.c -lgmp

network.o: network.c network.h
	@echo "Building the Network Library"
	${CC} ${CFLAGS} -c $< -o $@

clean: 
	rm -rf *.o a.out
