CC=gcc
CFLAGS=-Wall -pg
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

${OBJ}/network.o: ${SRC}/net/network.c ${SRC}/net/network.h ${SRC}/net/packet.h
	@${MKDIRS}
	@echo "Building $@"
	${CC} ${CFLAGS} -c $< -o $@

${OBJ}/cryptnet.o: ${SRC}/net/cryptnet.c ${SRC}/net/cryptnet.h ${OBJ}/network.o ${OBJ}/packet.o
	@${MKDIRS}
	@echo "Building $@"
	${CC} ${CFLAGS} -c $< -o $@

${OBJ}/packet.o: ${SRC}/net/packet.c ${SRC}/net/packet.h 
	@${MKDIRS}
	@echo "Building $@"
	${CC} ${CFLAGS} -c $< -lgmp -o $@

${BIN}/client: ${SRC}/client.c ${OBJ}/network.o ${OBJ}/packet.o ${OBJ}/elgamal.o ${OBJ}/number.o ${OBJ}/cryptnet.o ${OBJ}/aes.o
	@${MKDIRS}
	@echo "Building $@"
	${CC} ${CFLAGS} $^ -lgmp -lmcrypt -o $@

clean: 
	rm -rf obj/ bin/
