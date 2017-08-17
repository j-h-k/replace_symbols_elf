dmtcpdir=$$HOME/dmtcp/src

default:
	rm -f *.o LIBTEST.a
	cp ${dmtcpdir}/alarm.o ${dmtcpdir}/ckptserializer.o ${dmtcpdir}/coordinatorapi.o ${dmtcpdir}/dmtcp_dlsym.o ${dmtcpdir}/dmtcpplugin.o ${dmtcpdir}/dmtcpworker.o ${dmtcpdir}/glibcsystem.o ${dmtcpdir}/miscwrappers.o ${dmtcpdir}/plugininfo.o ${dmtcpdir}/pluginmanager.o ${dmtcpdir}/siginfo.o ${dmtcpdir}/signalwrappers.o ${dmtcpdir}/syslogwrappers.o ${dmtcpdir}/terminal.o ${dmtcpdir}/threadlist.o ${dmtcpdir}/threadsync.o ${dmtcpdir}/threadwrappers.o ${dmtcpdir}/writeckpt.o ${dmtcpdir}/execwrappers.o ${dmtcpdir}/popen.o ./clean_object_files/
	cp clean_object_files/*.o .
	../replace_symbols_elf -o alarm.o ckptserializer.o coordinatorapi.o dmtcp_dlsym.o dmtcpplugin.o dmtcpworker.o glibcsystem.o miscwrappers.o plugininfo.o pluginmanager.o siginfo.o signalwrappers.o syslogwrappers.o terminal.o threadlist.o threadsync.o threadwrappers.o writeckpt.o -s signal sigaction rt_sigaction sigvec sigblock sigsetmask siggetmask sigprocmask rt_sigprocmask sigsuspend sighold sigignore sigrelse __sigpause sigpause pthread_sigmask sigwait sigwaitinfo sigtimedwait fork daemon vfork execve execv execvp execvpe fexecve execl execlp execle system exit close fclose closedir dup2 pipe pipe2 wait waitpid wait3 wait4 waitid syscall popen pclose openlog closelog __clone pthread_create pthread_exit pthread_join pthread_tryjoin_np pthread_timedjoin_np --singlestr=_wrap__dmtcp_1
	../replace_symbols_elf -o execwrappers.o popen.o -s signal sigaction rt_sigaction sigvec sigblock sigsetmask siggetmask sigprocmask rt_sigprocmask sigsuspend sighold sigignore sigrelse __sigpause sigpause pthread_sigmask sigwait sigwaitinfo sigtimedwait fork daemon vfork execve execv execvp execvpe fexecve execl execlp execle system exit close fclose closedir pipe pipe2 wait waitpid wait3 wait4 waitid syscall popen pclose openlog closelog __clone pthread_create pthread_exit pthread_join pthread_tryjoin_np pthread_timedjoin_np --singlestr=_wrap__dmtcp_1
	ar cru LIBTEST.a *.o
	rm -f *.o

clean:
	rm -rf ./clean_object_files
	rm -rf *.o LIBTEST.a
	mkdir -p clean_object_files
