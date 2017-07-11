#!/usr/bin/python3
from __future__ import print_function
import os
import re
import sys
from elftools.elf.elffile import ELFFile
from elftools.elf.sections import Section
from elftools.elf.sections import SymbolTableSection


def create_dmtcp_h_file():
    if os.path.exists('./DMTCP.h'):
        return

    # Open c file
    fo = open('DMTCP.h', 'w')

    headers = ('#include <stdio.h>\n'
               '#include <fcntl.h>\n'
               '#include <sys/types.h>\n'
               '#include <sys/uio.h>\n'
               '#include <unistd.h>\n'
               '#include <stdlib.h>\n'
               '#include <stdlib.h>\n'
               '#include <string.h>\n'
               'static int plugin_id;\n')

    nextfnc = ('#define NEXT_FNC(func)\\\n'
               '({\\\n'
               'static __typeof__(&func) _real_ ## func = (__typeof__(&func)) -1;\\\n'
               'if (_real_ ## func == (__typeof__(&func)) -1) {\\\n'
               '  _real_ ## func = (__typeof__(&func)) func ## __dmtcp_dlsym( # func, &func, plugin_id);\\\n'
               '}\\\n'
               '_real_ ## func;\\\n'
               '})\n')

    fo.write(headers + nextfnc)

    # Close c file
    fo.close()


def opencurl(f):
    if not f.closed:
        f.write('{\n')


def closecurl(f):
    if not f.closed:
        f.write('}\n')


def create_dmtcp_c_file(symbolToFind, returntype, argumenttypes, firstcallarg, numSearchOrder):
    # list of arguments
    l_args = [returntype, argumenttypes, symbolToFind, firstcallargs]

    # Open c file
    fo = open(symbolToFind + '__DMTCP.c', 'w')

    # Write to c file, the c code
    header = '#include "DMTCP.h"\n'
    addrs = 'static long int ' + symbolToFind  + 'addrs[100] ={0};\n'
    typedef = 'typedef {0[0]} func({0[1]});\n'.format(l_args)
    decl = 'extern {0[0]} {0[2]}({0[1]});\n'.format(l_args)
    dmtcp_plt = '{0} {2}__dmtcp_plt({1});\n'.format(returntype, argumenttypes, symbolToFind)
    debug = '#define debug 0\n'
    fo.write(header + addrs + typedef + decl + dmtcp_plt + debug)

    # dmtcp_dlsym
    dmtcp_dlsym = 'void * {}__dmtcp_dlsym(char *str, void *fptr, int num)'.format(symbolToFind)
    fo.write(dmtcp_dlsym)

    opencurl(fo)
    staticvars = ('\tstatic int initialized = 0;\n'
                  '\tstatic int counter = 0;\n'
                  '\tstatic int numOfWrappers = 0;\n'
                  '\tchar *filename = "./addrs/'+symbolToFind+'__dmtcp.addr";\n'
                  '\tvoid *caller = __builtin_return_address(0);\n')
    fo.write(staticvars)
    #fo.write('printf("\\n%p\\n", __builtin_return_address(0));\n')

    fo.write('\tif (!initialized) ')

    opencurl(fo)
    fn = """    char *string = malloc(sizeof(char)*1000);
    int fd = open(filename, O_RDONLY);
    char *token;
    if (fd == -1) {{ printf("*** *** NO FILE\\n"); exit(1); }}
    read(fd, string, sizeof(char)*1000);
    while ((token = strsep(&string, ",")) != NULL)
      if (token[0] != '\\0') {{
        {0}addrs[numOfWrappers++] = strtol(token, NULL, 16);
        if (debug) printf("\\t%%ld\\n", {0}addrs[numOfWrappers-1]);
      }}
    free(string);
    initialized = 1;
  }}
  return (void *) {0}addrs[num];
  /*for (int i = 0; i < numOfWrappers; ++i) {{
    if (caller < (void *) {0}addrs[i])
      return (void *) {0}addrs[i];
  }}
  return (void *) {0}addrs[0];*/
    """
    fn = fn.format(symbolToFind)
    fo.write(fn)
    closecurl(fo)

    # <symbol>__dmtcp_plt
    fo.write(dmtcp_plt[:-2])

    opencurl(fo)
    fo.write('  NEXT_FNC('+symbolToFind+')('+firstcallargs+');\n'
             '  return {}addrs[0];\n'.format(symbolToFind))
    closecurl(fo) 
    
    # Close c file
    fo.close()

# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


def format_hex(addr, fieldsize=None):
    fieldsize = 16
    field = '%' + '0%sx' % fieldsize
    return field % addr


def write_to_file(filename, listToWrite):
    # Open file
    fo = open(filename, 'w')

    # Write to file
    for addrAndSymbol in listToWrite:
        fo.write(addrAndSymbol + ',')

    # Close file
    fo.close()


def process_file(filename, symbolToFind):
    actualFunc = ""
    listToWrite = []
    print('Processing file: ', filename)
    print('\tfor symbol: ', symbolToFind)
    with open(filename, 'rb') as f:
        elffile = ELFFile(f)
        for section in elffile.iter_sections():
            if not isinstance(section, SymbolTableSection):
                continue
            if section['sh_entsize'] == 0:
                print('No Symbol Table!!!')
                continue
            for nsym, symbol in enumerate(section.iter_symbols()):
                string = ('%s %s' % (
                    format_hex(symbol['st_value']),
                    symbol.name.decode("utf-8")
                ))
                if symbolToFind in str(symbol.name):
                    if symbolToFind == symbol.name.decode("utf-8"):
                        actualFunc = string
                    listToWrite.append(string)

    # Regular expression to match only dmtcp wrappers
    listToWrite = [x for x in listToWrite if re.search(
        symbolToFind + r'_wrap__dmtcp_\d+', x) != None]

    # If no symbolToFind... Exit
    if len(listToWrite) < 1:
        print ("*** *** No symbols found for: " + symbolToFind + "__dmtcp_*")
        sys.stdout.flush()
        sys.exit(1)

    # Sort list of strings of address and symbol name
    listToWrite.sort()
    listToWrite += [actualFunc]
    print (listToWrite)

    # Remove the name portion since sorted
    listToWrite = [x.split(' ', 1)[0] for x in listToWrite]

    # mkdir
    if not os.path.exists('./addrs'):
        os.mkdir('addrs')
    cwd = os.getcwd() + r'/addrs/'

    # Open file, filename will be: symbolToFind + '__dmtcp_*.addr'
    fileToWrite = cwd + symbolToFind + r'__dmtcp.addr'
    write_to_file(fileToWrite, listToWrite)
    print (listToWrite)
    print ("\tThe addresses directly above has been written out to : " + fileToWrite + "\n\n")


if __name__ == '__main__':
    if sys.argv[1] == '-cfile' and len(sys.argv) == 7 and int(sys.argv[6]):
        create_dmtcp_h_file()
        returntype = sys.argv[3]
        argumenttypes = sys.argv[4]
        firstcallargs = sys.argv[5]
        numSearchOrder = sys.argv[6]
        create_dmtcp_c_file(sys.argv[2], returntype, argumenttypes, firstcallargs, numSearchOrder)

    elif sys.argv[1] != None and sys.argv[2] != None and len(sys.argv) == 3:
        process_file(sys.argv[1], sys.argv[2])

    else:
        print ("***WRONG SYNTAX FOR CALLING elf.py")
