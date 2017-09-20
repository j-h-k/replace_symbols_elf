FILE=inlineasm
CFLAGS=-g -O0

default:
	gcc ${CFLAGS} -o ${FILE} save_rest_regs.s ${FILE}.c

run: default
	./${FILE}

check:
	./${FILE}

test:
	gcc ${CFLAGS} save_rest_regs.s main.c

vi:
	vim ${FILE}.c

gdb:
	gdb ./${FILE}

clean:
	rm -f ${FILE} a.out
