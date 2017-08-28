rse=replace_symbols_elf
CFLAGS=-g -O0
SDIR=./clean_src/clean_object_files_MOD
SDIR_PID=./clean_src/clean_object_files_libdmtcp_pid_MOD

OBJFILES_LIBDMTCP=${SDIR}/alarm.o ${SDIR}/ckptserializer.o ${SDIR}/coordinatorapi.o ${SDIR}/dmtcp_dlsym.o ${SDIR}/dmtcpplugin.o ${SDIR}/dmtcpworker.o ${SDIR}/glibcsystem.o ${SDIR}/miscwrappers.o ${SDIR}/plugininfo.o ${SDIR}/pluginmanager.o ${SDIR}/siginfo.o ${SDIR}/signalwrappers.o ${SDIR}/syslogwrappers.o ${SDIR}/terminal.o ${SDIR}/threadlist.o ${SDIR}/threadsync.o ${SDIR}/threadwrappers.o ${SDIR}/writeckpt.o ${SDIR}/execwrappers.o ${SDIR}/popen.o

OBJFILES_LIBDMTCP_PID=${SDIR_PID}/pid.o ${SDIR_PID}/pid_filewrappers.o ${SDIR_PID}/pid_miscwrappers.o ${SDIR_PID}/pid_syscallsreal.o ${SDIR_PID}/pidwrappers.o ${SDIR_PID}/sched_wrappers.o ${SDIR_PID}/virtualpidtable.o ${SDIR_PID}/pid_mutexwrappers.o

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
	# copy LIBDMTCP.a (which is libdmtcp.a) and LIBDMTCP_PID.a
	cp ./clean_src/*.a .

generate_cfile:
	rm -f dlsym_plt_DMTCP.c 
	# generate dmtcp plt and dlsym
	python3 elf.py -cfile symbols.to.find.NEWER.dmtcp symbols.to.find.NEWER.pid
	python3 elf.py -hfile symbols.to.find.NEWER.dmtcp symbols.to.find.NEWER.pid

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
	python3 elf.py -lib 1 ${OBJFILES_LIBDMTCP_PID}
	python3 elf.py -lib 2 ${OBJFILES_LIBDMTCP}
	#g++ ${CFLAGS} -static -static-libgcc -Wl,-u,dmtcp_initialize main.o dlsym_plt_DMTCP.o LIBDMTCP.a  LIBDMTCP_PID.a ./libs/libdmtcpinternal.a  ./libs/libsyscallsreal.a ./libs/libjalib.a ./libs/restore_libc.o -ldl -lrt ../src/glibc-build/nptl/libpthread.a ../src/glibc-build/libc.a
	g++ ${CFLAGS} -static -static-libgcc -Wl,-u,dmtcp_initialize main.o dlsym_plt_DMTCP.o LIBDMTCP.a  LIBDMTCP_PID.a ./libs/restore_libc.o -ldl -lrt ../src/glibc-build/nptl/libpthread.a ../src/glibc-build/libc.a

writeaddrs:
	python3 elf.py a.out symbols.to.find.NEWER.dmtcp symbols.to.find.NEWER.pid

vi:
	vi ../${rse}.c

gdb:
	gdb --args ~/dmtcp/bin/dmtcp_launch ./a.out

check:
	~/dmtcp/bin/dmtcp_launch ./a.out

movetodmtcp:
	cp DMTCP*.h ~/dmtcp/include/

clean:
	make clean -C ../
	make clean -C ./clean_src/
	make clean -C ./libs/
	rm -rf *.o dlsym_plt_DMTCP.c DMTCP*.h SYMBOLS.sym a.out replace_symbols_elf *.a
	rm -rf *.orig *.rej
	rm -rf *.nz ./addrs
