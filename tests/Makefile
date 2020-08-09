ifndef V
	QUIET_CXX      = @echo '  ' CXX '      ' $@;
	QUIET_BUILT_IN = @echo '  ' BUILTIN '  ' $@;
	QUIET_CLEAN    = @echo '  ' CLEAN '    ' $<;
	QUIET_AR       = @echo '  ' AR '       ' $@;
endif

CXX = g++
AR = ar
EXT = c

BINDIR = bin
SRCDIR = src
TARGET = test

# Init empty
CFLAGS =
LDFLAGS =

# Warrnings
CFLAGS += -Wall -Wextra -Wwrite-strings -Werror -Wshadow -Wpedantic -Wdouble-promotion -Wformat-security -Wformat-signedness -Wunsafe-loop-optimizations -Wunused-macros -Wcast-qual -Wcast-align -Wcast-align=strict -Wconversion -Warith-conversion -Wenum-compare -Wlogical-op -Wmissing-declarations -Wpacked -Wredundant-decls -Winline -Winvalid-pch -Wstack-protector

# Debug options
CFLAGS += -g

# Static analysers
CFLAGS += -fanalyzer -fdiagnostics-generate-patch -fdiagnostics-path-format=inline-events -fstack-protector -fsanitize=address -fno-omit-frame-pointer

# include directory
CFLAGS += -Igtest/googletest/googletest/include
CFLAGS += -I../include

LDFLAGS += -pthread
LDFLAGS += -Lgtest/bin -lgtest

TEST_SRC ?= $(wildcard ${SRCDIR}/*.${EXT})
TEST_OBJ ?= $(TEST_SRC:${SRCDIR}/%.${EXT}=${BINDIR}/%.o)

PROJECT_SRC ?= ../${SRCDIR}/test_func.c
PROJECT_OBJ ?= $(PROJECT_SRC:../${SRCDIR}/%.${EXT}=${BINDIR}/%.o)

SRC := ${TEST_SRC} ${PROJECT_SRC}
OBJ := ${TEST_OBJ} ${PROJECT_OBJ}

# Compile binary file
all : libgtest ${BINDIR}/${TARGET} run
${BINDIR}/${TARGET} : ${OBJ}
	${QUIET_BUILT_IN}${CXX} $^ -o $@ ${CFLAGS} ${LDFLAGS}

# Compile object files
${BINDIR}/%.o : ${SRCDIR}/%.${EXT}
	@mkdir -p ${BINDIR}
	${QUIET_CXX}${CXX} -c $< -o $@ ${CFLAGS}

${BINDIR}/%.o : ../${SRCDIR}/%.${EXT}
	@mkdir -p ${BINDIR}
	${QUIET_CXX}${CXX} -c $< -o $@ ${CFLAGS}

.PHONY: libgtest
libgtest:
	make -C gtest

.PHONY: run
run :
	@echo Running a test...
	@./${BINDIR}/${TARGET}

.PHONY: clean
clean : ${BINDIR}
	${QUIET_CLEAN}rm -rf $<
	@make -C gtest clean

-include $(OBJ:%.o=%.h)
