dmtcpdir=$$HOME/dmtcp/src
dmtcppiddir=$$HOME/dmtcp/src/plugin

COF=clean_object_files

LIBDMTCP_OBJS=${dmtcpdir}/alarm.o ${dmtcpdir}/ckptserializer.o ${dmtcpdir}/coordinatorapi.o ${dmtcpdir}/dmtcp_dlsym.o ${dmtcpdir}/dmtcpplugin.o ${dmtcpdir}/dmtcpworker.o ${dmtcpdir}/glibcsystem.o ${dmtcpdir}/miscwrappers.o ${dmtcpdir}/plugininfo.o ${dmtcpdir}/pluginmanager.o ${dmtcpdir}/siginfo.o ${dmtcpdir}/signalwrappers.o ${dmtcpdir}/syslogwrappers.o ${dmtcpdir}/terminal.o ${dmtcpdir}/threadlist.o ${dmtcpdir}/threadsync.o ${dmtcpdir}/threadwrappers.o ${dmtcpdir}/writeckpt.o ${dmtcpdir}/execwrappers.o ${dmtcpdir}/popen.o ${dmtcpdir}/syscallsreal.o ${dmtcpdir}/trampolines.o ${dmtcpdir}/dmtcpmessagetypes.o ${dmtcpdir}/workerstate.o ${dmtcpdir}/dmtcp_dlsym.o ${dmtcpdir}/uniquepid.o ${dmtcpdir}/shareddata.o ${dmtcpdir}/util_exec.o ${dmtcpdir}/util_misc.o ${dmtcpdir}/util_init.o ${dmtcpdir}/jalibinterface.o ${dmtcpdir}/processinfo.o ${dmtcpdir}/procselfmaps.o $(dmtcpdir)/jalib.o $(dmtcpdir)/jassert.o $(dmtcpdir)/jbuffer.o $(dmtcpdir)/jfilesystem.o $(dmtcpdir)/jserialize.o $(dmtcpdir)/jsocket.o $(dmtcpdir)/jtimer.o $(dmtcpdir)/jalloc.o

default:

	rm -f *.o LIBDMTCP.a LIBDMTCP_PID.a

	cp ${LIBDMTCP_OBJS} ./${COF}/

	cp ./${COF}/*.o .

	# Finding the wrappers
	#../replace_symbols_elf \
	#-o alarm.o ckptserializer.o coordinatorapi.o dmtcp_dlsym.o dmtcpplugin.o dmtcpworker.o glibcsystem.o miscwrappers.o plugininfo.o pluginmanager.o siginfo.o signalwrappers.o syslogwrappers.o terminal.o threadlist.o threadsync.o threadwrappers.o writeckpt.o execwrappers.o popen.o syscallsreal.o trampolines.o dmtcpmessagetypes.o workerstate.o dmtcp_dlsym.o uniquepid.o shareddata.o util_exec.o util_misc.o util_init.o jalibinterface.o processinfo.o procselfmaps.o jalib.o jassert.o jbuffer.o jfilesystem.o jserialize.o jsocket.o jtimer.o jalloc.o \
	#-s calloc malloc free __libc_memalign realloc mmap mmap64 mremap munmap dlopen dlclose getpid getppid kill tcgetpgrp tcsetpgrp getpgrp setpgrp getpgid setpgid getsid setsid setgid setuid wait waitpid waitid wait3 wait4 ioctl fcntl socket connect bind listen accept accept4 setsockopt getsockopt socketpair fexecve execve execv execvp execvpe execl execlp execle system popen pclose signal sigaction sigvec sigset sigblock sigsetmask siggetmask sigprocmask sigsuspend sighold sigignore __sigpause sigpause sigrelse sigwait sigwaitinfo sigtimedwait fork __clone open open64 fopen fopen64 openat openat64 opendir mkstemp close fclose closedir dup dup2 dup3 __xstat __xstat64 __lxstat __lxstat64 readlink exit syscall unsetenv ptsname_r ttyname_r getpt posix_openpt openlog closelog shmget shmat shmdt shmctl semget semctl semop semtimedop msgget msgctl msgsnd msgrcv mq_open mq_close mq_timedsend mq_timedreceive mq_notify read write select poll pthread_create pthread_exit pthread_tryjoin_np pthread_timedjoin_np pthread_sigmask pthread_getspecific pthread_mutex_lock pthread_mutex_trylock pthread_mutex_unlock pthread_rwlock_unlock pthread_rwlock_rdlock pthread_rwlock_tryrdlock pthread_rwlock_wrlock pthread_rwlock_trywrlock pthread_cond_broadcast pthread_cond_destroy pthread_cond_init pthread_cond_signal pthread_cond_timedwait pthread_cond_wait __xpg_sigpause \
	#--singlestr=_wrap__dmtcp_1 --only_def #--verbose
	../replace_symbols_elf \
	-o alarm.o ckptserializer.o coordinatorapi.o dmtcp_dlsym.o dmtcpplugin.o dmtcpworker.o glibcsystem.o miscwrappers.o plugininfo.o pluginmanager.o siginfo.o signalwrappers.o syslogwrappers.o terminal.o threadlist.o threadsync.o threadwrappers.o writeckpt.o execwrappers.o popen.o syscallsreal.o trampolines.o dmtcpmessagetypes.o workerstate.o dmtcp_dlsym.o uniquepid.o shareddata.o util_exec.o util_misc.o util_init.o jalibinterface.o processinfo.o procselfmaps.o jalib.o jassert.o jbuffer.o jfilesystem.o jserialize.o jsocket.o jtimer.o jalloc.o \
	-s $$(cat dmtcp.wrapper.sym) __sigpause __xpg_sigpause \
	--singlestr=_wrap__dmtcp_1 --only_def #--verbose

	# Replacing the calls
	#../replace_symbols_elf \
	#-o alarm.o ckptserializer.o coordinatorapi.o dmtcp_dlsym.o dmtcpplugin.o dmtcpworker.o glibcsystem.o miscwrappers.o plugininfo.o pluginmanager.o siginfo.o signalwrappers.o syslogwrappers.o terminal.o threadlist.o threadsync.o threadwrappers.o writeckpt.o execwrappers.o popen.o syscallsreal.o trampolines.o dmtcpmessagetypes.o workerstate.o dmtcp_dlsym.o uniquepid.o shareddata.o util_exec.o util_misc.o util_init.o jalibinterface.o processinfo.o procselfmaps.o jalib.o jassert.o jbuffer.o jfilesystem.o jserialize.o jsocket.o jtimer.o jalloc.o \
	#-s calloc malloc free __libc_memalign realloc mmap mmap64 mremap munmap getpid getppid kill tcgetpgrp tcsetpgrp getpgrp setpgrp getpgid setpgid getsid setsid setgid setuid wait waitpid waitid wait3 wait4 ioctl fcntl socket connect bind listen accept accept4 setsockopt getsockopt socketpair fexecve execve execv execvp execvpe execl execlp execle system popen pclose signal sigaction sigvec sigset sigblock sigsetmask siggetmask sigprocmask sigsuspend sighold sigignore __sigpause sigpause sigrelse sigwait sigwaitinfo sigtimedwait fork open open64 fopen fopen64 openat openat64 opendir mkstemp close fclose closedir dup dup2 dup3 __xstat __xstat64 __lxstat __lxstat64 readlink exit syscall unsetenv ptsname_r ttyname_r getpt posix_openpt openlog closelog shmget shmat shmdt shmctl semget semctl semop semtimedop msgget msgctl msgsnd msgrcv mq_open mq_close mq_timedsend mq_timedreceive mq_notify read write select poll pthread_create pthread_exit pthread_tryjoin_np pthread_timedjoin_np pthread_sigmask pthread_getspecific pthread_mutex_lock pthread_mutex_trylock pthread_mutex_unlock pthread_rwlock_unlock pthread_rwlock_rdlock pthread_rwlock_tryrdlock pthread_rwlock_wrlock pthread_rwlock_trywrlock pthread_cond_broadcast pthread_cond_destroy pthread_cond_init pthread_cond_signal pthread_cond_timedwait pthread_cond_wait \
	#--singlestr=__dmtcp_plt --only_undef #--verbose
	../replace_symbols_elf \
	-o alarm.o ckptserializer.o coordinatorapi.o dmtcp_dlsym.o dmtcpplugin.o dmtcpworker.o glibcsystem.o miscwrappers.o plugininfo.o pluginmanager.o siginfo.o signalwrappers.o syslogwrappers.o terminal.o threadlist.o threadsync.o threadwrappers.o writeckpt.o execwrappers.o popen.o syscallsreal.o trampolines.o dmtcpmessagetypes.o workerstate.o dmtcp_dlsym.o uniquepid.o shareddata.o util_exec.o util_misc.o util_init.o jalibinterface.o processinfo.o procselfmaps.o jalib.o jassert.o jbuffer.o jfilesystem.o jserialize.o jsocket.o jtimer.o jalloc.o \
	-s $$(cat dmtcp.wrapper.sym) __sigpause __ xpg_sigpause \
	--singlestr=__dmtcp_plt --only_undef #--verbose

	### nm ./signalwrappers.o | grep sigpause

#dmtcp should have called _real___sigpause instead of '_real__sigpause'
	../replace_symbols_elf \
	-o signalwrappers.o \
	-c _real__sigpause \
	--completestr=__sigpause --only_undef

#signal.h in glibc causes the sigpause symbol to be replaced by __xpg_sigpause
	../replace_symbols_elf \
	-o signalwrappers.o \
	-c _real_sigpause \
	--completestr=__xpg_sigpause --only_undef

	../replace_symbols_elf \
	-o threadlist.o \
	-c _real_clone \
	--completestr=clone --only_undef

	### nm ./signalwrappers.o | grep sigpause

	../replace_symbols_elf \
	-o alarm.o ckptserializer.o coordinatorapi.o dmtcp_dlsym.o dmtcpplugin.o dmtcpworker.o glibcsystem.o miscwrappers.o plugininfo.o pluginmanager.o siginfo.o signalwrappers.o syslogwrappers.o terminal.o threadlist.o threadsync.o threadwrappers.o writeckpt.o execwrappers.o popen.o syscallsreal.o trampolines.o dmtcpmessagetypes.o workerstate.o dmtcp_dlsym.o uniquepid.o shareddata.o util_exec.o util_misc.o util_init.o jalibinterface.o processinfo.o procselfmaps.o jalib.o jassert.o jbuffer.o jfilesystem.o jserialize.o jsocket.o jtimer.o jalloc.o \
        -f _real_ \
        --startwithstr=_s1

	../replace_symbols_elf \
	-o alarm.o ckptserializer.o coordinatorapi.o dmtcp_dlsym.o dmtcpplugin.o dmtcpworker.o glibcsystem.o miscwrappers.o plugininfo.o pluginmanager.o siginfo.o signalwrappers.o syslogwrappers.o terminal.o threadlist.o threadsync.o threadwrappers.o writeckpt.o execwrappers.o popen.o syscallsreal.o trampolines.o dmtcpmessagetypes.o workerstate.o dmtcp_dlsym.o uniquepid.o shareddata.o util_exec.o util_misc.o util_init.o jalibinterface.o processinfo.o procselfmaps.o jalib.o jassert.o jbuffer.o jfilesystem.o jserialize.o jsocket.o jtimer.o jalloc.o \
	-s dmtcp_gettid dmtcp_tkill dmtcp_tgkill \
	--singlestr=_s1

	ar cru LIBDMTCP.a *.o
	cp *.o ${COF}_MOD/
	rm -f *.o

## +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

## +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

## +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

## +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#make libdmtcp_pid.a now
# NOT CURRENTLY::
# NOT CURRENTLY::	cp ${dmtcppiddir}/pid.o ${dmtcppiddir}/pid_filewrappers.o ${dmtcppiddir}/pid_miscwrappers.o ${dmtcppiddir}/pid_syscallsreal.o ${dmtcppiddir}/pidwrappers.o ${dmtcppiddir}/sched_wrappers.o ${dmtcppiddir}/virtualpidtable.o ${dmtcppiddir}/pid_mutexwrappers.o  ./${COF}_libdmtcp_pid/
# NOT CURRENTLY::
# NOT CURRENTLY::	cp ./${COF}_libdmtcp_pid/*.o .
# NOT CURRENTLY::	
# NOT CURRENTLY::	../replace_symbols_elf \
# NOT CURRENTLY::	-o pid.o pid_filewrappers.o pid_miscwrappers.o pid_syscallsreal.o pidwrappers.o sched_wrappers.o virtualpidtable.o pid_mutexwrappers.o \
# NOT CURRENTLY::	-s calloc malloc free __libc_memalign realloc mmap mmap64 mremap munmap dlopen dlclose getpid getppid kill tcgetpgrp tcsetpgrp getpgrp setpgrp getpgid setpgid getsid setsid setgid setuid wait waitpid waitid wait3 wait4 ioctl fcntl socket connect bind listen accept accept4 setsockopt getsockopt socketpair fexecve execve execv execvp execvpe execl execlp execle system popen pclose signal sigaction sigvec sigset sigblock sigsetmask siggetmask sigprocmask sigsuspend sighold sigignore __sigpause sigpause sigrelse sigwait sigwaitinfo sigtimedwait fork __clone open open64 fopen fopen64 openat openat64 opendir mkstemp close fclose closedir dup dup2 dup3 __xstat __xstat64 __lxstat __lxstat64 readlink exit syscall unsetenv ptsname_r ttyname_r getpt posix_openpt openlog closelog shmget shmat shmdt shmctl semget semctl semop semtimedop msgget msgctl msgsnd msgrcv mq_open mq_close mq_timedsend mq_timedreceive mq_notify read write select poll pthread_create pthread_exit pthread_tryjoin_np pthread_timedjoin_np pthread_sigmask pthread_getspecific pthread_mutex_lock pthread_mutex_trylock pthread_mutex_unlock pthread_rwlock_unlock pthread_rwlock_rdlock pthread_rwlock_tryrdlock pthread_rwlock_wrlock pthread_rwlock_trywrlock pthread_cond_broadcast pthread_cond_destroy pthread_cond_init pthread_cond_signal pthread_cond_timedwait pthread_cond_wait __xpg_sigpause __register_atfork \
# NOT CURRENTLY::	--singlestr=_wrap__dmtcp_1 --only_def #--verbose
# NOT CURRENTLY::
# NOT CURRENTLY::# try START WITH rse
# NOT CURRENTLY::
# NOT CURRENTLY::	readelf -s pid_syscallsreal.o | grep _real_*
# NOT CURRENTLY::
# NOT CURRENTLY::	../replace_symbols_elf \
# NOT CURRENTLY::        -o pid.o pid_syscallsreal.o pid_filewrappers.o pid_miscwrappers.o pidwrappers.o sched_wrappers.o virtualpidtable.o pid_mutexwrappers.o \
# NOT CURRENTLY::        -f _real_ \
# NOT CURRENTLY::        --startwithstr=_s1
# NOT CURRENTLY::
# NOT CURRENTLY::	readelf -s pid_syscallsreal.o | grep _real_*
# NOT CURRENTLY::
# NOT CURRENTLY::	../replace_symbols_elf \
# NOT CURRENTLY::        -o pid.o pid_syscallsreal.o pid_filewrappers.o pid_miscwrappers.o pidwrappers.o sched_wrappers.o virtualpidtable.o pid_mutexwrappers.o \
# NOT CURRENTLY::        -s dmtcp_gettid dmtcp_tkill dmtcp_tgkill \
# NOT CURRENTLY::        --singlestr=_s1
# NOT CURRENTLY::
# NOT CURRENTLY::	ar cru LIBDMTCP_PID.a *.o
# NOT CURRENTLY::	cp *.o ${COF}_libdmtcp_pid_MOD/
# NOT CURRENTLY::	rm -f *.o
# NOT CURRENTLY::

clean:
	rm -f *.o LIBDMTCP.a LIBDMTCP_PID.a #./${COF}/*.o ./${COF}_libdmtcp_pid/*.o
	rm -f ./${COF}_MOD/*.o ./${COF}_libdmtcp_pid_MOD/*.o
	mkdir -p ${COF}/ ${COF}_MOD/
	mkdir -p ${COF}_libdmtcp_pid/ ${COF}_libdmtcp_pid_MOD/
