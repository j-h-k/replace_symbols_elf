rse=replace_symbols_elf

default: pre libdmtcpa generate_cfile applypatch compile

pre:
	make clean -C ../
	make -C ../
	cp ../${rse} .

libdmtcpa:
	make -C ./clean_src
	# copy LIBTEST.a (which is libdmtcp.a)
	cp ./clean_src/LIBTEST.a .

generate_cfile:
	rm -f dlsym_plt_DMTCP.c 
	# generate dmtcp plt and dlsym
	python3 elf.py -cfile symbols.to.find

patch:
	diff -c dlsym_plt_DMTCP.c BACKUP_dlsym_plt_DMTCP.c > dlsym_plt_DMTCP.c.patch

applypatch:
	# apply the patch
	patch -p0 <dlsym_plt_DMTCP.c.patch

compile:
	# now compile
	gcc -c -g dlsym_plt_DMTCP.c main.c
	
link:
	#LD_LIBRARY_PATH=$$HOME/replace_symbols_elf/example_libdmtcp2/src/lib g++ -g -static -Wl,-u,dmtcp_initialize main.o dlsym_plt_DMTCP.o LIBTEST.a  ./libs/libdmtcpinternal.a  ./libs/libsyscallsreal.a ./libs/libjalib.a ./libs/restore_libc.o -pthread -ldl 
	g++ -g -static -static-libgcc -Wl,-u,dmtcp_initialize main.o dlsym_plt_DMTCP.o LIBTEST.a  ./libs/libdmtcpinternal.a  ./libs/libsyscallsreal.a ./libs/libjalib.a ./libs/restore_libc.o -ldl $$HOME/replace_symbols_elf/example_libdmtcp2/src/lib/libpthread.a $$HOME/replace_symbols_elf/example_libdmtcp2/src/lib/libc.a

clean:
	rm -rf *.o dlsym_plt_DMTCP.c DMTCP.h SYMBOLS.sym a.out replace_symbols_elf LIBTEST.a
	rm -rf *.orig *.rej
