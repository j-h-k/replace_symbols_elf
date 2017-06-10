CC=gcc
CFLAGS=-g3 -O0

csn=replace_symbols_elf
util=util
test=TEST
wf=wrapfile
wrapfiles=./wrapfiles/wrapfile
dir_wrapfiles=./wrapfiles

default: ${csn} run

${csn}: ${csn}.o ${util}.o
	${CC} ${CFLAGS} $^ -o $@ 

# For every XYZ.c file, generate XYZ.o.
%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

run: 
	rm -f ${test}.o
	rm -f ${wrapfiles}1.o ${wrapfiles}2.o ${wrapfiles}3.o
	${CC} -c ${test}.c 
	${CC} -c ${wrapfiles}1.c ${wrapfiles}2.c ${wrapfiles}3.c

#	readelf -h ${test}.o
#	readelf -S ${test}.o
#	readelf -s ${test}.o
#
	#same as --keepnumsymbol=foo_wrap 
	./${csn} -o ${wf}1.o ${wf}2.o ${wf}3.o -k foo_wrap 
	#same as --singlesymbol=foo
	./${csn} -o ${test}.o -s foo 

#	readelf -h ${test}.o
#	readelf -S ${test}.o
#	readelf -s ${test}.o

test:
	gcc -c DMTCP.c
	gcc -static DMTCP.o ${wf}1.o ${wf}2.o ${wf}3.o ${test}.o
	gcc DMTCP.o ${wf}1.o ${wf}2.o ${wf}3.o ${test}.o -o dyn_a.out

check: test
	./a.out

clean:
	rm -f ${csn} *.o *a.out
	rm -f ${dir_wrapfiles}/*.o

vi:
	vim ${csn}.c

