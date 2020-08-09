ifndef V
	QUIET_CXX      = @echo '  ' CXX '      ' $@;
	QUIET_BUILT_IN = @echo '  ' BUILTIN '  ' $@;
	QUIET_CLEAN    = @echo '  ' CLEAN '    ' $<;
	QUIET_AR       = @echo '  ' AR '       ' $@;
endif

CXX = g++
AR = ar
EXT = cc

BINDIR = bin
SRCDIR = googletest/googletest/src
TARGET = gtest

# Init empty
CFLAGS =
LDFLAGS =

# include directory
CFLAGS += -Igoogletest/googletest/include
CFLAGS += -Igoogletest/googletest

SRC ?= $(wildcard ${SRCDIR}/*.${EXT})
OBJ ?= $(SRC:${SRCDIR}/%.${EXT}=${BINDIR}/%.o)

all : lib

# Compile static library
lib : ${BINDIR}/lib${TARGET}.a
${BINDIR}/lib${TARGET}.a : ${OBJ}
	${QUIET_AR}${AR} rcs $@ $^

# Compile object files
${BINDIR}/%.o : ${SRCDIR}/%.${EXT}
	@ if [ ! -d ${BINDIR} ]; then mkdir ${BINDIR}; fi
	${QUIET_CXX}${CXX} -c $< -o $@ ${CFLAGS}


clean : ${BINDIR}
	${QUIET_CLEAN}rm -rf $<

-include $(OBJ:%.o=%.h)
