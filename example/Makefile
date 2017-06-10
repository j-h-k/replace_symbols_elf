rse=replace_symbols_elf

default:
	rm -f *.o ${rse}
	@echo -e "\n\n\t***Do make in upper directory first***\n\n"
	cp ../${rse} .
	gcc -c main.c file1.c file2.c
	./${rse} -o file1.o file2.o -s foo woo --singlestr=_string
	./${rse} -o file1.o file2.o -k doo --keepnumstr=_string_
	gcc main.o file1.o file2.o
	./a.out

clean:
	rm -f *.o a.out ${rse}
