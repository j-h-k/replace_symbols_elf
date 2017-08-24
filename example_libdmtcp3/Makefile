rse=replace_symbols_elf
CFLAGS=-g -O0
SDIR=./clean_src
OBJFILES=${SDIR}/alarm.o ${SDIR}/ckptserializer.o ${SDIR}/coordinatorapi.o ${SDIR}/dmtcp_dlsym.o ${SDIR}/dmtcpplugin.o ${SDIR}/dmtcpworker.o ${SDIR}/glibcsystem.o ${SDIR}/miscwrappers.o ${SDIR}/plugininfo.o ${SDIR}/pluginmanager.o ${SDIR}/siginfo.o ${SDIR}/signalwrappers.o ${SDIR}/syslogwrappers.o ${SDIR}/terminal.o ${SDIR}/threadlist.o ${SDIR}/threadsync.o ${SDIR}/threadwrappers.o ${SDIR}/writeckpt.o ${SDIR}/execwrappers.o ${SDIR}/popen.o

default: clean pre libs libdmtcpa generate_cfile compile

pre: clean
	make clean -C ../
	make -C ../ #make replace symbols elf program
	cp ../${rse} .
	make -C ../src #make modified glibc

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
	gcc -c ${CFLAGS} dlsym_plt_DMTCP.c main.c
	
link:
	python3 elf.py -lib 0 ${OBJFILES}
	g++ ${CFLAGS} -static -static-libgcc -Wl,-u,dmtcp_initialize main.o dlsym_plt_DMTCP.o LIBTEST.a  ./libs/libdmtcpinternal.a  ./libs/libsyscallsreal.a ./libs/libjalib.a ./libs/restore_libc.o -ldl -lrt ../src/glibc-build/nptl/libpthread.a ../src/glibc-build/libc.a

writeaddrs:
	python3 elf.py a.out symbols.to.find

vi:
	vi ../${rse}.c

clean:
	make clean -C ../
	make clean -C ./clean_src/
	make clean -C ./libs/
	rm -rf *.o dlsym_plt_DMTCP.c DMTCP.h SYMBOLS.sym a.out replace_symbols_elf *.a
	rm -rf *.orig *.rej
	rm -rf *.nz ./addrs
