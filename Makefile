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

# Warrnings
CFLAGS += -Wall -Wextra -Wwrite-strings -Werror -Wshadow -Wpedantic -Wdouble-promotion -Wformat-security -Wformat-signedness -Wunsafe-loop-optimizations -Wunused-macros -Wbad-function-cast -Wcast-qual -Wcast-align -Wcast-align=strict -Wconversion -Warith-conversion -Wenum-compare -Wjump-misses-init -Wlogical-op -Waggregate-return -Wstrict-prototypes -Wold-style-definition -Wmissing-prototypes -Wmissing-declarations -Wpacked -Wredundant-decls -Wnested-externs -Winline -Winvalid-pch -Wstack-protector

# Debug options
CFLAGS += -g

# Static analysers
CFLAGS += -fanalyzer -Wanalyzer-too-complex -fdiagnostics-generate-patch -fdiagnostics-path-format=inline-events -fstack-protector -fsanitize=address -fno-omit-frame-pointer

# Flag for shared library
CFLAGS += -fPIC


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
