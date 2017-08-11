rse=replace_symbols_elf

default: pre files rse py_lib link writeaddrs

pre:
	make clean -C ../
	make -C ../

files:
	python3 elf.py -cfile symbols.to.find
	gcc -c -g *_DMTCP.c main.c
	g++ -c -g *.cpp
	g++ -c -g mallocwrappers.cpp -o mallocwrappers.tmp.o

rse: 
	rm -rf ${rse}
	cp ../${rse} .
	./${rse} -o mallocwrappers.o -k malloc free calloc realloc valloc posix_memalign memalign --keepnumstr=_wrap__dmtcp_ -c dlsym --completestr=dmtcp_dlsym
	./${rse} -o main.o -s malloc free calloc realloc valloc posix_memalign memalign

py_lib: ${rse}
	python3 elf.py -lib 0 mallocwrappers.o

link:
	g++ -v -g -static mallocwrappers.o main.o *_DMTCP.o -o softcode 

writeaddrs:
	@echo -n "\n\tPython Program\n"
	python3 elf.py softcode symbols.to.find

vi:
	vim elf.py

check:
	./softcode

clean:
	rm -f *.o a.out *.addr
	rm -rf addrs *.nz
	rm -f DMTCP.h *_DMTCP.c
	rm -f softcode*
	rm -f ${rse}
	make clean -C ../

elf:
	readelf -s softcode | grep dmtcp
	readelf -s softcode2 | grep dmtcp
