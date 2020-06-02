ifndef V
	QUIET_CC       = @echo '  ' CC '       ' $@;
	QUIET_BUILT_IN = @echo '  ' BUILTIN '  ' $@;
	QUIET_CLEAN    = @echo '  ' CLEAN '    ' $<;
	QUIET_AR       = @echo '  ' AR '       ' $@;
endif

CC = gcc
AR = ar
BINPATH = bin
TARGET = ${BINPATH}/out
LIBTARGET = ${BINPATH}/libout
EXT = c

CFLAGS =
CFLAGS += -pedantic
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wwrite-strings
CFLAGS += -Werror
CFLAGS += -MD
CFLAGS += -fPIC

CFLAGS += -g
CFLAGS += -fsanitize=address
CFLAGS += -fno-omit-frame-pointer

LDFLAGS =
LDFLAGS += -pthread

SRC ?= $(wildcard *.${EXT})
OBJ ?= $(SRC:%.${EXT}=${BINPATH}/%.o)

# Compile binary file
all : ${TARGET}
${TARGET} : ${OBJ}
	${QUIET_BUILT_IN}${CC} $^ -o $@ ${CFLAGS} ${LDFLAGS}

# Compile static library
lib : ${LIBTARGET}.a
${LIBTARGET}.a : ${OBJ}
	${QUIET_AR}${AR} rcs $@ $^

# Compile shared library
so : ${LIBTARGET}.so
${LIBTARGET}.so : ${OBJ}
	${QUIET_BUILT_IN}${CC} -shared $^ -o $@ ${CFLAGS} ${LDFLAGS}

# Compile object files
${BINPATH}/%.o : %.${EXT}
	@ if [ ! -d ${BINPATH} ]; then mkdir ${BINPATH}; fi
	${QUIET_CC}${CC} -c $< -o $@ ${CFLAGS}


clean : ${BINPATH}
	${QUIET_CLEAN}rm -rf $<

-include $(OBJ:%.o=%.h)
