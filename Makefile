CC=gcc
CFLAGS=-Wall

all: network.o

network.o: network.c network.h
	@echo "Building the Network Library"
	${CC} {CFLAGS} -c $< -o $@

clean: 
	rm -rf *.o a.out