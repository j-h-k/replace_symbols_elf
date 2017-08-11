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

    headers1 = ('#ifndef __DMTCP_H_\n'
               '#define __DMTCP_H_\n'
               '#define STATIC_PLUGIN_ID 0\n'
               '#ifndef EXTERNC\n'
               '# ifdef __cplusplus\n'
               '#  define EXTERNC extern "C"\n'
               '# else // ifdef __cplusplus\n'
               '#  define EXTERNC\n'
               '# endif // ifdef __cplusplus\n'
               '#endif // ifndef EXTERNC\n'
               'EXTERNC void * dmtcp_sdlsym(char *, void *, int, long int *);\n')

    headers2 = ('#define _GNU_SOURCE\n#define _XOPEN_SOURCE 600\nstatic int plugin_id = 0;\n'
               '#define _BSD_SOURCE\n'
               '#include <stdio.h>\n'
               '#include <fcntl.h>\n'
               '#include <sys/types.h>\n'
               '#include <sys/uio.h>\n'
               '#include <unistd.h>\n'
               '#include <stdlib.h>\n'
               '#include <stdlib.h>\n'
               '#include <string.h>\n'
               '#include <malloc.h>\n'
               '#include <signal.h>\n'
               '#include <pthread.h>\n'
               '#include <features.h>\n'
               '#include <syslog.h>\n'
               '#include <sys/types.h>\n#include <sys/time.h>\n#include <sys/resource.h>\n#include <sys/wait.h>\n'
               '#include <dirent.h>\n'
               '#include <poll.h>\n'
               '#include <sys/stat.h>\n'
               '#include <mqueue.h>\n'
               '#include <sys/types.h>\n'
               '#include <sys/ipc.h>\n'
               '#include <sys/msg.h>\n'
               '#include <sys/sem.h>\n'
               '#include <sys/shm.h>\n'
               '#include <sys/socket.h>\n'
               '#include <sys/ioctl.h>\n'
               '#include <sys/mman.h>\n'
               '#define SETUP_FPTR(symbol) void * __fptr = (void *) NEXT_FNC_S_DEFAULT(symbol)\n'
               '#define DELETE_CALL_FRAME() \\\n'
               '  asm ("mov %%rbp, %%r11\\n\\t" \\\n' 
               '        "sub %%rsp, %%r11\\n\\t" \\\n'
               '        "add %%r11, %%rsp\\n\\t" \\\n'
               '        "pop %%rbp\\n\\t" \\\n'
               '        "jmp *%0" \\\n'
               '        : \\\n'
               '        : "a" (__fptr) \\\n'
               '        : )\n')

    nextfnc = ('#define NEXT_FNC_S_DEFAULT(func)\\\n'
               '({\\\n'
               'static __typeof__(&func) _real_ ## func = (__typeof__(&func)) -1;\\\n'
               'if (_real_ ## func == (__typeof__(&func)) -1) {\\\n'
               '  _real_ ## func = (__typeof__(&func)) dmtcp_sdlsym( # func, (void *)&func, STATIC_PLUGIN_ID, func ## addrs);\\\n'
               '}\\\n'
               '_real_ ## func;\\\n'
               '})\n')

    fo.write(headers1 + headers2 + nextfnc)

    # Close c file
    fo.close()

def create_dmtcp_c_file():
    fo = open('dlsym_plt_DMTCP.c', 'w')
    header = '#include "DMTCP.h"\n'
    fo.write(header)
    fo.close()

def finally_write_dmtcp_dlsym():
    fo = open('dlsym_plt_DMTCP.c', 'a')
    # dmtcp_dlsym
    dmtcp_dlsym = 'void * dmtcp_sdlsym(char *str, void *fptr, int pl_id, long int* addrs)'
    fo.write(dmtcp_dlsym)

    opencurl(fo)
    staticvars = ('\tchar filename[200] = {0};\n'
                  '\tstrcat(filename, "./addrs/"); strcat(filename, str); strcat(filename, "__dmtcp.addr");\n')
    fo.write(staticvars)

    fo.write('\tif ((pl_id == 0 && addrs[0] == 0) || (pl_id > 0 && addrs[pl_id-1] == 0))')

    opencurl(fo)
    fn = """    int numOfWrappers = 0;
    char *string = malloc(sizeof(char)*1000);
    int fd = open(filename, O_RDONLY);
    char *token;
    if (fd == -1) {{ printf("*** *** NO FILE\\n"); exit(1); }}
    read(fd, string, sizeof(char)*1000);
    while ((token = strsep(&string, ",")) != NULL)
      if (token[0] != '\\0') {{
        addrs[numOfWrappers++] = strtol(token, NULL, 16);
      }}
    free(string);
    //initialized = 1;
  }}
  while (1)
  {{
    if (addrs[pl_id] != 0)
      return (void *)addrs[pl_id];
    ++pl_id;
  }}
  exit(1);
  //return addrs[3];
  //return (void *) addrs[num];
  /*for (int i = 0; i < numOfWrappers; ++i) {{
    if (caller < (void *) {0}addrs[i])
      return (void *) {0}addrs[i];
  }}
  return (void *) {0}addrs[0];*/
    """
    fn = fn.format(symbolToFind)
    fo.write(fn)
    closecurl(fo)

    fo.close()

def finally_write_h_file():
    with open('DMTCP.h', 'a') as fo:
        fo.write('#endif //__DMTCP_H_\n')
    

def opencurl(f):
    if not f.closed:
        f.write('{\n')


def closecurl(f):
    if not f.closed:
        f.write('}\n')


# FOR EACH SYMBOL
def append_addrs_h_file(symbolToFind):
    fo = open('DMTCP.h', 'a')

    fo.write('extern long int ' + symbolToFind +'addrs[100];\n')

    fo.close()
    
# FOR EACH SYMBOL
def append_dmtcp_plt(symbolToFind):

    # Open c file
    fo = open('dlsym_plt_DMTCP.c', 'a')

    # long int <symbol>addrs[100]
    addrs = 'long int ' + symbolToFind  + 'addrs[100];\n'
    fo.write(addrs)

    # <symbol>__dmtcp_plt
    dmtcp_plt = 'void {0}__dmtcp_plt();\n'.format(symbolToFind)
    fo.write(dmtcp_plt[:-2])

    opencurl(fo)
    fo.write('  ')
    #fo.write('void * __fptr = (void *) NEXT_FNC_S_DEFAULT('+symbolToFind+');\n')
    fo.write('SETUP_FPTR('+symbolToFind+');\n')

    fo.write('  ')
    fo.write('DELETE_CALL_FRAME();\n');

    closecurl(fo) 
    
    # Close c file
    fo.close()


# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

# all_library_wrappers_dmtcp.nz

def find_symbols_dmtcp(object_file):
    listToWrite = []
    with open(object_file, 'rb') as f:
        elffile = ELFFile(f)
        for section in elffile.iter_sections():
            if not isinstance(section, SymbolTableSection):
                continue
            if section['sh_entsize'] == 0:
                print('No Symbol Table!!!')
                continue
            for nsym, symbol in enumerate(section.iter_symbols()):
                if '_wrap__dmtcp_' in str(symbol.name):
                    string = symbol.name.decode("utf-8")
                    listToWrite.append(string[:string.index('_wrap__dmtcp_')])

    print ('listToWrite', listToWrite)
    return listToWrite
        

def append_all_library_wrappers_dmtcp(lib_plugin_id, l_object_files):
    print (l_object_files)
    with open('all_library_wrappers_dmtcp.nz', 'a+') as f:
        f.write(lib_plugin_id)
        for object_file in l_object_files:
            l_symbols_found = find_symbols_dmtcp(object_file)
            for sym in l_symbols_found:
                f.write(' ' + sym)
        f.write(' \n')


# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

# ./addrs/<symbol>__dmtcp.addr

def sort_all_library_wrappers_dmtcp():
    l_lines = []
    with open('all_library_wrappers_dmtcp.nz', 'r') as f:
        l_lines = f.readlines()
        l_lines.sort()
    print (l_lines)
    with open('all_library_wrappers_dmtcp.nz', 'w') as f:
        for line in l_lines:
            f.write(line)

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
                    symbol.name.decode("utf-8"),
                    format_hex(symbol['st_value'])
                ))
                if symbolToFind in str(symbol.name):
                    if symbolToFind == symbol.name.decode("utf-8"):
                        actualFunc = string
                    listToWrite.append(string)

    # Regular expression to match only dmtcp wrappers
    listToWrite = [x for x in listToWrite if re.search(
        symbolToFind + r'_wrap__dmtcp_\d+', x) != None and x.find(symbolToFind) == 0]

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
    listToWrite = [x.split(' ', 1)[1] for x in listToWrite]

    # Put in 0 (NULL) hole library that don't have symbol
    with open('all_library_wrappers_dmtcp.nz', 'r') as f:
        l_lines = f.readlines()
        print ('****************', l_lines)
        for ind, line in enumerate(l_lines):
            print (symbolToFind, ind, line, '****************')
            if symbolToFind not in line:
                listToWrite.insert(ind, '0')

    # mkdir
    if not os.path.exists('./addrs'):
        os.mkdir('addrs')
    cwd = os.getcwd() + r'/addrs/'

    # Open file, filename will be: symbolToFind + '__dmtcp_*.addr'
    fileToWrite = cwd + symbolToFind + r'__dmtcp.addr'
    write_to_file(fileToWrite, listToWrite)
    print (listToWrite)
    print ("\tThe addresses directly above has been written out to : " + fileToWrite + "\n\n")


# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


if __name__ == '__main__':
    if sys.argv[1] == '-cfile':
        # create dmtcp.h
        create_dmtcp_h_file()
        # create dmtcp_plt_DMTCP.c
        create_dmtcp_c_file()

        with open(sys.argv[2], 'r') as f:
            for line in f:
                if line.isspace():
                    continue
                # args for create dmtcp_dlsym.c
                #symbolToFind = line.split('(', 1)[0].split()[-1].strip()
                symbolToFind = line.strip()

                #returntype = line[:line.find(str(symbolToFind))].strip()

                #argumenttypes = line.split('(', 1)[1].rsplit(')', 1)[0].strip()

                #l_firstcallargs = line.split('(', 1)[1].rsplit(')', 1)[0].split(',')

                ###firstcallargs = ''
                ###if symbolToFind == '__clone':
                ###    #int (* fn)(void * arg), void * child_stack, int flags, void * arg, int * parent_tidptr, struct user_desc * newtls, int * child_tidptr
                ###    firstcallargs = 'fn,child_stack,flags,arg,parent_tidptr,newtls,child_tidptr'
                ###elif symbolToFind == 'pthread_create':
                ###    #pthread_t * thread, const pthread_attr_t * attr, void * (* start_routine)(void *), void * arg
                ###    firstcallargs = 'thread,attr,start_routine,arg'
                ###else:
                ###    for type_plus_arg in l_firstcallargs:
                ###        if type_plus_arg == '' or type_plus_arg == 'void':
                ###            break
                ###        s = type_plus_arg.strip().split()[-1]
                ###        s = s.split('[', 1)
                ###        firstcallargs += s[0] + ','
                ###    firstcallargs = firstcallargs[:-1]

                #append_dmtcp_plt(symbolToFind, returntype, argumenttypes, firstcallargs)
                append_dmtcp_plt(symbolToFind)
                append_addrs_h_file(symbolToFind)

            finally_write_dmtcp_dlsym()
            finally_write_h_file()

    elif sys.argv[1] == '-lib':
        append_all_library_wrappers_dmtcp(sys.argv[2], sys.argv[3:])

    elif sys.argv[1] != None and sys.argv[2] != None and len(sys.argv) == 3:
        # sort all_library_wrappers_dmtcp.nz here
        sort_all_library_wrappers_dmtcp()
        with open(sys.argv[2], 'r') as f:
            for l in f:
                process_file(sys.argv[1], l.split('(')[0].split()[-1])

    else:
        print ("***WRONG SYNTAX FOR CALLING elf.py")
