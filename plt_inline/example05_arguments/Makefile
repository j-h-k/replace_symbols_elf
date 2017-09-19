FILE=inlineasm
CFLAGS=-g -O0

default:
	gcc ${CFLAGS} -o ${FILE} ${FILE}.c

run: default
	./${FILE}

check:
	./${FILE}

vi:
	vim ${FILE}.c

gdb:
	gdb ./${FILE}

clean:
	rm -f ${FILE} a.out
