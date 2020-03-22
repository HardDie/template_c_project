ifndef V
	QUIET_CC       = @echo '  ' CC '       ' $@;
	QUIET_BUILT_IN = @echo '  ' BUILTIN '  ' $@;
	QUIET_CLEAN    = @echo '  ' CLEAN '    ' $<;
endif

CC = gcc
BINPATH = bin
TARGET = ${BINPATH}/out_binary
EXT = c

CFLAGS =
CFLAGS += -pedantic
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wwrite-strings
CFLAGS += -Werror
CFLAGS += -MD

CFLAGS += -g
CFLAGS += -fsanitize=address
CFLAGS += -fno-omit-frame-pointer

LDFLAGS =
LDFLAGS += -pthread

SRC ?= $(wildcard *.${EXT})
OBJ ?= $(SRC:%.${EXT}=${BINPATH}/%.o)

all : ${TARGET}

${TARGET} : ${OBJ}
	${QUIET_BUILT_IN}${CC} $^ -o $@ ${CFLAGS} ${LDFLAGS}

${BINPATH}/%.o : %.${EXT}
	@ if [ ! -d ${BINPATH} ]; then mkdir ${BINPATH}; fi
	${QUIET_CC}${CC} -c $< -o $@ ${CFLAGS}

clean : ${BINPATH}
	${QUIET_CLEAN}rm -rf $<

-include $(OBJ:%.o=%.h)
