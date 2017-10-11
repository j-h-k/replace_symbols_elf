rse=replace_symbols_elf
CFLAGS=-g -O0
SDIR=./clean_src/clean_object_files_MOD
SDIR_PID=./clean_src/clean_object_files_libdmtcp_pid_MOD
KFRT=keepForRoundTwo

OBJFILES_LIBDMTCP=${SDIR}/alarm.o ${SDIR}/ckptserializer.o ${SDIR}/coordinatorapi.o ${SDIR}/dmtcp_dlsym.o ${SDIR}/dmtcpplugin.o ${SDIR}/dmtcpworker.o ${SDIR}/glibcsystem.o ${SDIR}/miscwrappers.o ${SDIR}/plugininfo.o ${SDIR}/pluginmanager.o ${SDIR}/siginfo.o ${SDIR}/signalwrappers.o ${SDIR}/syslogwrappers.o ${SDIR}/terminal.o ${SDIR}/threadlist.o ${SDIR}/threadsync.o ${SDIR}/threadwrappers.o ${SDIR}/writeckpt.o ${SDIR}/execwrappers.o ${SDIR}/popen.o

OBJFILES_LIBDMTCP_PID=${SDIR_PID}/pid.o ${SDIR_PID}/pid_filewrappers.o ${SDIR_PID}/pid_miscwrappers.o ${SDIR_PID}/pid_syscallsreal.o ${SDIR_PID}/pidwrappers.o ${SDIR_PID}/sched_wrappers.o ${SDIR_PID}/virtualpidtable.o ${SDIR_PID}/pid_mutexwrappers.o

default: movetodmtcp

configuredmtcp: clean
	(cd ~/dmtcp && ./configure 'CFLAGS=-g3 -O0' 'CXXFLAGS=-g3 -O0')
	make -j -C ~/dmtcp

pre: configuredmtcp
	make clean -C ../
	make -C ../ #make replace symbols elf program
	cp ../${rse} .
	make -C ../src #make modified glibc

libs: pre
	make -C ./libs
	cp ./libs/*.a .

generate_cfile: libs
	rm -f dlsym_plt_DMTCP.c 
	./utilities/get_dmtcp_wrapper_symbols.sh
	# generate dmtcp plt and dlsym
	python3 elf.py -cfile *.sym
	python3 elf.py -hfile *.sym


compile: generate_cfile
	# now compile
	gcc -c ${CFLAGS} dlsym_plt_DMTCP.c main.c
	cp DMTCP.h dlsym_plt_DMTCP.o main.o *.sym ./${KFRT}/

movetodmtcp: compile
	cp DMTCP.h static_dmtcp.h
	cp static_dmtcp.h ~/dmtcp/include/
	cp DMTCP.h ~/dmtcp/include/

# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# ROUND TWO	
configuredmtcpforstatic:
	(cd ~/dmtcp && ./configure --enable-logging 'CFLAGS=-g3 -O0 -DSTATIC_DMTCP=1' 'CXXFLAGS=-g3 -O0 -DSTATIC_DMTCP=1')
	#(cd ~/dmtcp && ./configure 'CFLAGS=-g3 -O0 -DSTATIC_DMTCP=1' 'CXXFLAGS=-g3 -O0 -DSTATIC_DMTCP=1')
	make -j -C ~/dmtcp

libdmtcpa: configuredmtcpforstatic
	cp *.sym ./clean_src
	make -C ./clean_src
	# copy LIBDMTCP.a (which is libdmtcp.a) and LIBDMTCP_PID.a
	cp ./clean_src/*.a .

link: libdmtcpa
	#python3 elf.py -lib 1 ${OBJFILES_LIBDMTCP_PID}
	python3 elf.py -lib 1 ${OBJFILES_LIBDMTCP}
	#g++ ${CFLAGS} -static -static-libgcc -Wl,-u,dmtcp_initialize main.o dlsym_plt_DMTCP.o LIBDMTCP.a  LIBDMTCP_PID.a ./libs/restore_libc.o -ldl -lrt ../src/glibc-build/nptl/libpthread.a ../src/glibc-build/libc.a
	g++ ${CFLAGS} -static -static-libgcc -Wl,-u,dmtcp_initialize -I./${KFRT} save_rest_regs.s ./${KFRT}/main.o ./${KFRT}/dlsym_plt_DMTCP.o -Wl,--whole-archive LIBDMTCP.a -Wl,--no-whole-archive ./libs/restore_libc.o -ldl -lrt ./libpthread.a ./libc.a #../src/glibc-build/libc.a
	python3 elf.py a.out *.sym 


writeaddrs:
	python3 elf.py a.out *.sym 

check:
	~/dmtcp/bin/dmtcp_launch ./a.out

run:
	~/dmtcp/bin/dmtcp_launch --no-gzip -p 7779 ./a.out

restart:
	~/dmtcp/bin/dmtcp_restart  -p 7779 ckpt*.dmtcp

tidy:
	rm -f ckpt*.dmtcp ckpt*.temp


# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# FOR DEVELOPMENT
vi:
	vi ../${rse}.c

gdb:
	gdb --args ~/dmtcp/bin/dmtcp_launch ./a.out
gdb2:
	gdb --args ~/dmtcp/bin/dmtcp_launch -p 7779 ./a.out


# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# OTHER USEFUL
patch:
	# CREATE A BACKUP_dlsym_plt_DMTCP.c, then run this command
	diff -c dlsym_plt_DMTCP.c BACKUP_dlsym_plt_DMTCP.c > dlsym_plt_DMTCP.c.patch

applypatch:
	# apply the patch
	patch -p0 <dlsym_plt_DMTCP.c.patch

# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# CLEAN
clean:
	make clean -C ../
	make clean -C ./clean_src/
	make clean -C ./libs/
	make clean -C ./utilities/
	rm -rf *.o dlsym_plt_DMTCP.c static_dmtcp.h DMTCP*.h SYMBOLS.sym a.out replace_symbols_elf *.a
	rm -rf *.orig *.rej
	rm -rf *.nz ./addrs
	rm -rf *.sym
	rm -f ./${KFRT}/*
	rm -f ~/dmtcp/include/DMTCP.h
	rm -f ckpt*
	rm -f clean_src/*.sym
