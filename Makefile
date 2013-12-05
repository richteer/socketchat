CC=gcc
CFLAGS=-Wall
SRC=src
OBJ=obj
BIN=bin
MKDIRS=mkdir -p ${OBJ} ${BIN}

all: ${BIN}/client

tests: ${BIN}/test_number ${BIN}/test_eg ${BIN}/test_aes

${BIN}/test_number: ${SRC}/test_number.c ${OBJ}/number.o
	@${MKDIRS}
	@echo "Building $@"
	${CC} ${CFLAGS} $^ -lgmp -o $@

${BIN}/test_eg: ${SRC}/test_eg.c ${OBJ}/elgamal.o ${OBJ}/number.o
	@${MKDIRS}
	@echo "Building $@"
	${CC} ${CFLAGS} $^ -lgmp -o $@

${BIN}/test_aes: ${SRC}/test_aes.c ${OBJ}/aes.o
	@${MKDIRS}
	@echo "Building $@"
	${CC} ${CFLAGS} $^ -lmcrypt -o $@

${OBJ}/elgamal.o: ${SRC}/crypto/elgamal.c ${SRC}/crypto/elgamal.h
	@${MKDIRS}
	@echo "Building $@"
	${CC} ${CFLAGS} -c $< -lgmp -o $@

${OBJ}/aes.o: ${SRC}/crypto/aes.c ${SRC}/crypto/aes.h
	@${MKDIRS}
	@echo "Building $@"
	${CC} ${CFLAGS} -c $< -o $@

${OBJ}/number.o: ${SRC}/crypto/number.c ${SRC}/crypto/number.h
	@${MKDIRS}
	@echo "Building $@"
	${CC} ${CFLAGS} -c $< -lgmp -o $@

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
