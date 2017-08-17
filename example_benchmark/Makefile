rse=replace_symbols_elf

default: clean pre libdmtcpa #generate_cfile compile

pre: clean
	make clean -C ../
	make -C ../
	cp ../${rse} .

libdmtcpa: pre
	make -C ./clean_src
	# copy LIBTEST.a (which is libdmtcp.a)
	cp ./clean_src/LIBTEST.a .

generate_cfile:
	rm -f dlsym_plt_DMTCP.c 
	# generate dmtcp plt and dlsym
	python3 elf.py -cfile symbols.to.find

compile:
	# now compile
	gcc -c -g dlsym_plt_DMTCP.c main.c
	
vi:
	vi ../${rse}.c

clean:
	make clean -C ../
	make clean -C ./clean_src/
	rm -rf *.o dlsym_plt_DMTCP.c DMTCP.h SYMBOLS.sym a.out replace_symbols_elf *.a
	rm -rf *.orig *.rej
