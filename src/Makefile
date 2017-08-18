default: glibc-2.26 glibc-build

glibc-2.26:
	@echo "UNTAR glibc2.26"
	tar -xvzf glibc-2.26.tar.gz

glibc-build:
	@echo "CREATE glibc-build"
	mkdir -p ./glibc-build
	cd glibc-build; ../glibc-2.26/configure --prefix=$$PWD --enable-static-nss;
	make -j -C ./glibc-build

clean:
	rm -rf glibc-2.26 glibc-build
