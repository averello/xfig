CC = gcc
CFLAGS = -Wall -g3 -pedantic -std=c99 -I${INC} 
LDFLAGS = 
BIN = bin
INC = include
OBJ = obj
SRC = src
MKDIR = mkdir

LIB = lib
MKDIR = mkdir

.PHONY: all directories compileall runall clean cleanall

# +-----------+
# | Cible all |
# +-----------+

all: directories compileall

# +-------------+
# | Cible test1 |
# +-------------+

TEST1 = 
test1: directories ${BIN}/${TEST1}
	@echo "**** Testing ${TEST1}"
	@${BIN}/${TEST5}
	@echo "---- end of ${TEST1}"

# +-------------------+
# | Cible directories |
# +-------------------+

directories: ${OBJ} ${BIN}

${OBJ}:
	${MKDIR} -p ${OBJ}
${BIN}:
	${MKDIR} -p ${BIN}

# +------------------------------+
# | Cibles pour compiler avec -c |
# +------------------------------+

${OBJ}/%.o : ${SRC}/%.c
	$(CC) -c -o $@ $< ${CFLAGS}

${BIN}/% : ${OBJ}/%.o
	${CC} -o $@ $< ${LDFLAGS}

# +------------------+
# | Cible compileall |
# +------------------+

compileall: 

# +--------------+
# | Cible runall |
# +--------------+

runall: compileall

# +-------------+
# | Cible clean |
# +-------------+

clean:
	rm -f ${OBJ}/* ${BIN}/*

# +----------------+
# | Cible cleanall |
# +----------------+

cleanall: clean
	rm -f ${OBJ}/* ${BIN}/*;
	rmdir ${OBJ} ${BIN}
	rm -f ${INC}/*~ ${SRC}/*~ *~

