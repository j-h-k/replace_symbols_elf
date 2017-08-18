rse=replace_symbols_elf

default: clean pre libs libdmtcpa generate_cfile compile

pre: clean
	make clean -C ../
	make -C ../
	cp ../${rse} .
	make -C ../src

libs: pre
	make -C ./libs
	cp ./libs/*.a .

libdmtcpa: pre
	make -C ./clean_src
	# copy LIBTEST.a (which is libdmtcp.a)
	cp ./clean_src/LIBTEST.a .

generate_cfile:
	rm -f dlsym_plt_DMTCP.c 
	# generate dmtcp plt and dlsym
	python3 elf.py -cfile symbols.to.find

patch:
	# CREATE A BACKUP_dlsym_plt_DMTCP.c, then run this command
	diff -c dlsym_plt_DMTCP.c BACKUP_dlsym_plt_DMTCP.c > dlsym_plt_DMTCP.c.patch

applypatch:
	# apply the patch
	patch -p0 <dlsym_plt_DMTCP.c.patch

compile:
	# now compile
	gcc -c -g dlsym_plt_DMTCP.c main.c
	
link:
	#LD_LIBRARY_PATH=$$HOME/replace_symbols_elf/example_libdmtcp2/src/lib g++ -g -static -Wl,-u,dmtcp_initialize main.o dlsym_plt_DMTCP.o LIBTEST.a  ./libs/libdmtcpinternal.a  ./libs/libsyscallsreal.a ./libs/libjalib.a ./libs/restore_libc.o -pthread -ldl 
	g++ -g -static -static-libgcc -Wl,-u,dmtcp_initialize main.o dlsym_plt_DMTCP.o LIBTEST.a  ./libs/libdmtcpinternal.a  ./libs/libsyscallsreal.a ./libs/libjalib.a ./libs/restore_libc.o -ldl -lrt ../src/glibc-build/nptl/libpthread.a ../src/glibc-build/libc.a

vi:
	vi ../${rse}.c

clean:
	make clean -C ../
	make clean -C ./clean_src/
	make clean -C ./libs/
	rm -rf *.o dlsym_plt_DMTCP.c DMTCP.h SYMBOLS.sym a.out replace_symbols_elf *.a
	rm -rf *.orig *.rej
