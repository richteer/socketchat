CC=gcc
CFLAGS=-Wall
SRC=src
OBJ=obj
BIN=bin
MKDIRS=mkdir -p ${OBJ} ${BIN}

all: ${BIN}/client

tests: ${BIN}/test_number

${BIN}/test_number: ${SRC}/test_number.c ${SRC}/crypto/number.h ${SRC}/crypto/number.c
	@${MKDIRS}
	@echo "Building $@r"
	${CC} ${CFLAGS} test_number.c number.c -lgmp -o $@

${OBJ}/number.o: ${SRC}/crypto/number.c ${SRC}/crypto/number.h
	@${MKDIRS}
	@echo "Building $@"
	${CC} ${CFLAGS} $< -lgmp -o $@

${BIN}/test_eg: ${SRC}/test_eg.c ${SRC}/crypto/elgamal.h ${SRC}/crypto/elgamal.c
	@${MKDIRS}
	@echo "Building $@"
	${CC} ${CFLAGS} test_eg.c elgamal.c -lgmp

${OBJ}/network.o: ${SRC}/net/network.c ${SRC}/net/network.h
	@${MKDIRS}
	@echo "Building $@"
	${CC} ${CFLAGS} -c $< -o $@

${BIN}/client: ${SRC}/client.c ${OBJ}/network.o
	@${MKDIRS}
	@echo "Building $@"
	${CC} ${CFLAGS} $^ -o $@

clean: 
	rm -rf obj/ bin/
