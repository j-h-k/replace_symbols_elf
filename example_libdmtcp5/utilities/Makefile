LIB_DIR=lib_sym
GLIBC_DIR=../../src/glibc-build
LIB_A=libc.so
LIB_B=libpthread.so
LIB_C=libdmtcp.so

default:
	./get_lib_symbols.sh ${GLIBC_DIR}/${LIB_A} ${GLIBC_DIR}/nptl/${LIB_B}
	./get_dmtcp_wrapper_symbols.sh

comm:
	@echo '*** *** *** ${LIB_A} vs ${LIB_C}'
	comm -12 ${LIB_DIR}/${LIB_A}.sym ${LIB_DIR}/${LIB_C}.sym
	@echo ''
	@echo '*** *** *** ${LIB_B} vs ${LIB_C}'
	comm -12 ${LIB_DIR}/${LIB_B}.sym ${LIB_DIR}/${LIB_C}.sym

vi:
	vim getsymbols.sh

clean:
	rm -rf *.sym *.o lib_sym

