rse=replace_symbols_elf

default: pre files ${rse} link writeaddrs

pre:
	make clean -C ../
	make -C ../

files:
	#python3 elf.py -cfile sleep "unsigned int" "unsigned int seconds" "seconds" 3
	python3 elf.py -cfile cfile
	gcc -c -g sleep*.c *_DMTCP.c dmtcp1.c

${rse}: ${rse}
	rm -f ${rse}
	@echo -n "\n\n\t***Do make in upper directory first***\n\n"
	cp ../${rse} .
	./${rse} -o sleep1.o sleep2.o sleep3.o -k sleep --keepnumstr=_wrap__dmtcp_ -c dlsym --completestr=dmtcp_dlsym
	./${rse} -o dmtcp1.o -c sleep --completestr=sleep__dmtcp_plt

link: sleep1.o sleep2.o sleep3.o dmtcp1.o 
	gcc -v -g -static *_DMTCP.o sleep1.o sleep2.o sleep3.o sleep11.o dmtcp1.o -o softcode 
	gcc -g -static sleep1.o sleep2.o sleep3.o sleep11.o *_DMTCP.o dmtcp1.o -o softcode2

writeaddrs:
	@echo -n "\n\tPython Program\n"
	python3 elf.py softcode sleep

vi:
	vim elf.py

check:
	./softcode

clean:
	rm -f *.o a.out *.addr
	rm -rf addrs
	rm -f DMTCP.h *_DMTCP.c
	rm -f softcode*
	rm -f ${rse}
	make clean -C ../

elf:
	readelf -s softcode | grep dmtcp
	readelf -s softcode2 | grep dmtcp
