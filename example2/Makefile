rse=replace_symbols_elf

default: files ${rse} link writeaddrs

files:
	gcc -c TEST.c -o TEST.o
	gcc -c DMTCP.c -o DMTCP.o
	gcc -c foowrap*.c
	python3 elf.py -cfile foo
	gcc -c foo__DMTCP.c

${rse}: 
	rm -f ${rse}
	@echo -n "\n\n\t***Do make in upper directory first***\n\n"
	cp ../${rse} .
	./${rse} -o TEST.o -s foo --singlestr=__dmtcp_plt
	./${rse} -o foowrap1.o foowrap2.o foowrap3.o -s foo --singlestr=__dmtcp_plt
	./${rse} -o foowrap1.o foowrap2.o foowrap3.o -k foo_wrap --keepnumstr=__dmtcp_

link:
	gcc -static foowrap*.o TEST.o DMTCP.o -o hardcoded
	gcc -static foowrap*.o TEST.o foo__DMTCP.o -o softcoded

writeaddrs:
	@echo -n "\n\tPython Program\n"
	python3 elf.py softcoded foo

vi:
	vim elf.py

check:
	./softcoded

clean:
	rm -f *.o a.out *.addr
	rm -rf addrs
	rm -f DMTCP.h *__DMTCP.c
	rm -f hardcoded softcoded
	rm -f ${rse}

