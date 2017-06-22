rse=replace_symbols_elf

default: pre files ${rse} link writeaddrs

pre:
	make clean -C ../
	make -C ../

files:
	python3 elf.py -cfile sleep "unsigned int" "unsigned int seconds" "seconds"
	gcc -c -g sleep1.c *__DMTCP.c dmtcp1.c

${rse}: ${rse}
	rm -f ${rse}
	@echo -n "\n\n\t***Do make in upper directory first***\n\n"
	cp ../${rse} .
	./${rse} -o sleep1.o -k sleep --keepnumstr=_wrap__dmtcp_ -c dlsym --completestr=sleep__dmtcp_dlsym
	./${rse} -o dmtcp1.o -c sleep --completestr=sleep__dmtcp_plt

link: sleep1.o dmtcp1.o 
	gcc -g -static sleep1.o *__DMTCP.o dmtcp1.o -o softcode 

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
	rm -f DMTCP.h *__DMTCP.c
	rm -f softcode
	rm -f ${rse}
	make clean -C ../
