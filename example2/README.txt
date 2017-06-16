Step (1)
	Need to install python package: pyelftools
	Please install either Python2.7 and Python3.x

	Will work for either Python 2.7 or Python3.x (x >= 2)

	ex.
		$> pip install pyelftools
			or
		$> pip3 install pyelftools


*** Steps (2) and (3) order doesn't matter

Step (2)
	Run replace_symbols_elf program on the object file necessary
		i.e. 	foo -> foo__dmtcp_plt
			foo_wrap in multiple foowrap*.c files -> foo_wrap__dmtcp_*

Step (3)
	Run:
		$> python elf.py -cfile <symbolname>

	This will generate the <symbolname>__DMTCP.c that will perform the PLT functionality

Step (4)
	Link the object files together (STATICALLY)

Step (5)
	Run:
		$> python elf.py <elf executable> <symbolname>

	This will generate the (.addr) file that will be read at runtime by the cfile generated
	that mimics the PLT functionality
