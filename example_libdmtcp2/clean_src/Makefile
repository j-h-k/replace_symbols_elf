dmtcpdir=$$HOME/dmtcp/src

default:
	rm -f *.o LIBTEST.a
	#make -j -C $$HOME/dmtcp/src/
	cp ${dmtcpdir}/alarm.o ${dmtcpdir}/ckptserializer.o ${dmtcpdir}/coordinatorapi.o ${dmtcpdir}/dmtcp_dlsym.o ${dmtcpdir}/dmtcpplugin.o ${dmtcpdir}/dmtcpworker.o ${dmtcpdir}/glibcsystem.o ${dmtcpdir}/miscwrappers.o ${dmtcpdir}/plugininfo.o ${dmtcpdir}/pluginmanager.o ${dmtcpdir}/siginfo.o ${dmtcpdir}/signalwrappers.o ${dmtcpdir}/syslogwrappers.o ${dmtcpdir}/terminal.o ${dmtcpdir}/threadlist.o ${dmtcpdir}/threadsync.o ${dmtcpdir}/threadwrappers.o ${dmtcpdir}/writeckpt.o ${dmtcpdir}/execwrappers.o ${dmtcpdir}/popen.o ./clean_object_files/
	cp clean_object_files/*.o .

	/home/kimjae95/replace_symbols_elf/example_libdmtcp2/replace_symbols_elf \
	-o alarm.o ckptserializer.o coordinatorapi.o dmtcp_dlsym.o dmtcpplugin.o dmtcpworker.o glibcsystem.o miscwrappers.o plugininfo.o pluginmanager.o siginfo.o signalwrappers.o syslogwrappers.o terminal.o threadlist.o threadsync.o threadwrappers.o writeckpt.o execwrappers.o popen.o \
	-s calloc malloc free __libc_memalign realloc mmap mmap64 mremap munmap dlopen dlclose getpid getppid kill tcgetpgrp tcsetpgrp getpgrp setpgrp getpgid setpgid getsid setsid setgid setuid wait waitpid waitid wait3 wait4 ioctl fcntl socket connect bind listen accept accept4 setsockopt getsockopt socketpair fexecve execve execv execvp execvpe execl execlp execle system popen pclose signal sigaction sigvec sigset sigblock sigsetmask siggetmask sigprocmask sigsuspend sighold sigignore __sigpause sigpause sigrelse sigwait sigwaitinfo sigtimedwait fork __clone open open64 fopen fopen64 openat openat64 opendir mkstemp close fclose closedir dup dup2 dup3 __xstat __xstat64 __lxstat __lxstat64 readlink exit syscall unsetenv ptsname_r ttyname_r getpt posix_openpt openlog closelog shmget shmat shmdt shmctl semget semctl semop semtimedop msgget msgctl msgsnd msgrcv mq_open mq_close mq_timedsend mq_timedreceive mq_notify read write select poll pthread_create pthread_exit pthread_tryjoin_np pthread_timedjoin_np pthread_sigmask pthread_getspecific pthread_mutex_lock pthread_mutex_trylock pthread_mutex_unlock pthread_rwlock_unlock pthread_rwlock_rdlock pthread_rwlock_tryrdlock pthread_rwlock_wrlock pthread_rwlock_trywrlock pthread_cond_broadcast pthread_cond_destroy pthread_cond_init pthread_cond_signal pthread_cond_timedwait pthread_cond_wait __xpg_sigpause \
	--singlestr=_wrap__dmtcp_1 --only_def #--verbose

	nm ./signalwrappers.o | grep sigpause

#dmtcp should have called _real___sigpause instead of '_real__sigpause'
	/home/kimjae95/replace_symbols_elf/example_libdmtcp2/replace_symbols_elf \
	-o signalwrappers.o \
	-c _real__sigpause \
	--completestr=__sigpause --only_undef

#signal.h in glibc causes the sigpause symbol to be replaced by __xpg_sigpause
	/home/kimjae95/replace_symbols_elf/example_libdmtcp2/replace_symbols_elf \
	-o signalwrappers.o \
	-c _real_sigpause \
	--completestr=__xpg_sigpause --only_undef

	/home/kimjae95/replace_symbols_elf/example_libdmtcp2/replace_symbols_elf \
	-o threadlist.o \
	-c _real_clone \
	--completestr=clone --only_undef


	nm ./signalwrappers.o | grep sigpause

	ar cru LIBTEST.a *.o
	#rm -f *.o

clean:
	rm -f *.o LIBTEST.a ./clean_object_files/*.o
