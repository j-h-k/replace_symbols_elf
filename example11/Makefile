rse=replace_symbols_elf

default: pre files ${rse} py_lib link writeaddrs

pre:
	make clean -C ../
	make -C ../

files:
	python3 elf.py -cfile symbols.to.find
	gcc -c -g sleep*.c open*.c *_DMTCP.c dmtcp1.c

${rse}: ${rse}
	rm -f ${rse}
	@echo -n "\n\n\t***Do make in upper directory first***\n\n"
	cp ../${rse} .
	./${rse} -o sleep1.o sleep2.o sleep3.o -k sleep --keepnumstr=_wrap__dmtcp_ -c dlsym --completestr=dmtcp_dlsym
	./${rse} -o open1.o open3.o -k open --keepnumstr=_wrap__dmtcp_ -c dlsym --completestr=dmtcp_dlsym
	./${rse} -o dmtcp1.o -c sleep --completestr=sleep__dmtcp_plt
	./${rse} -o dmtcp1.o -c open --completestr=open__dmtcp_plt

py_lib: ${rse}
	python3 elf.py -lib 2 sleep3.o open3.o
	python3 elf.py -lib 0 sleep1.o open1.o
	python3 elf.py -lib 1 sleep2.o 

link: sleep1.o sleep2.o sleep3.o dmtcp1.o 
	gcc -v -g -static *_DMTCP.o sleep2.o sleep1.o sleep3.o sleep11.o open3.o open1.o dmtcp1.o -o softcode 

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
