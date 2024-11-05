PROJECT_NAME=chomp

BUILD_DIR ?= build
SOURCE_DIR ?= src

CC ?= gcc
CFLAGS += -Wall -Iinclude -std=gnu11

# basic targets
main: game estimate
	${CC} ${CFLAGS} -o ${BUILD_DIR}/${PROJECT_NAME} ${SOURCE_DIR}/main.c ${BUILD_DIR}/game.o ${BUILD_DIR}/estimate.o

mk_build_dir:
	if [ ! -d ${BUILD_DIR} ]; then mkdir ${BUILD_DIR}; fi

clean:
	rm ${BUILD_DIR}/*.o

# specific
game: mk_build_dir
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/game.o ${SOURCE_DIR}/game.c

estimate: mk_build_dir
	${CC} ${CFLAGS} -c -o ${BUILD_DIR}/estimate.o ${SOURCE_DIR}/estimate.c
