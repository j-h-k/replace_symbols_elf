#!/usr/bin/python3
from __future__ import print_function
import os
import re
import sys
from elftools.elf.elffile import ELFFile
from elftools.elf.sections import Section
from elftools.elf.sections import SymbolTableSection
from builtins import any


def create_dmtcp_h_file_base():
    if os.path.exists('./DMTCP.h'):
        return

    # Open c file
    with open('DMTCP.h', 'w') as fo:

        headers1 = (
            '#ifndef __DMTCP_H_\n'
            '#define __DMTCP_H_\n'
            '#define STATIC_PLUGIN_ID 1\n' ### THIS IS TMP
            '#ifndef EXTERNC\n'
            '# ifdef __cplusplus\n'
            '#  define EXTERNC extern "C"\n'
            '# else // ifdef __cplusplus\n'
            '#  define EXTERNC\n'
            '# endif // ifdef __cplusplus\n'
            '#endif // ifndef EXTERNC\n'
            '#ifndef DMTCP_H\n'
            '# define _GNU_SOURCE\n'
            '# define _XOPEN_SOURCE 600\n'
            '# define _BSD_SOURCE\n'
            '#endif\n'
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
            '#include <sys/stat.h>\n'
            '#include <sys/ptrace.h>\n'
            '#define MAX_NUM_LIBS 100\n'
            '#define SETUP_FPTR(symbol) ({save_regs(); NEXT_FNC_S_DEFAULT(symbol);})\n'
            '#define DELETE_CALL_FRAME() \\\n'
            '  ({asm volatile ("mov %%rax, %%r10\\n\\t" : : : );\\\n'
            '    rest_regs();\\\n'
            '    asm ("pop %%rbp\\n\\t"\\\n'
            '         "jmp *%%r10"\\\n'
            '         :\\\n'
            '         :\\\n'
            '         : ); })\n'
            'EXTERNC void * dmtcp_sdlsym(char *, void *, int, long int *);\n'
            'EXTERNC void dmtcp_initialize_plugin(void) __attribute((weak));\n'
            'EXTERNC pid_t dmtcp_gettid() __attribute((weak));\n'
            'EXTERNC int dmtcp_tkill(int, int) __attribute((weak));\n'
            'EXTERNC int dmtcp_tgkill(int, int, int) __attribute((weak));\n'
            'EXTERNC int open64(const char *path, int flags, ...);\n'
            'EXTERNC FILE * fopen64(const char *path, const char *mode);\n'
            'EXTERNC int __xstat64(int vers, const char *path, struct stat64 *buf);\n'
            'EXTERNC int __lxstat(int vers, const char *path, struct stat *buf);\n'
            'EXTERNC int __lxstat64(int vers, const char *path, struct stat64 *buf);\n'
            'EXTERNC int __register_atfork(void (*prepare)(void), void (*parent)(void), void (*child)(void), void *dso_handle);\n'
        )

        nextfnc = (
            '#define NEXT_FNC_S_DEFAULT(func)\\\n'
            '({\\\n'
            'static __typeof__(&func) _real_ ## func = (__typeof__(&func)) -1;\\\n'
            'if (_real_ ## func == (__typeof__(&func)) -1) {\\\n'
            '  _real_ ## func = (__typeof__(&func)) dmtcp_sdlsym( # func, (void *)&func, STATIC_PLUGIN_ID, func ## addrs);\\\n'
            '}\\\n'
            '_real_ ## func;\\\n'
            '})\n')

        fo.write(headers1 + nextfnc)
        #fo.write('#endif //__DMTCP_H_\n')


def create_dmtcp_h_file(staticid):
    if os.path.exists('./DMTCP' + staticid + '.h'):
        return

    # Open c file
    with open('DMTCP' + staticid + '.h', 'w') as fo:

        headers1 = ('#include "DMTCP.h"\n'
                    '#ifndef __DMTCP' + staticid + '_H_\n'
                    '#define __DMTCP' + staticid + '_H_\n'
                    '#ifdef STATIC_PLUGIN_ID\n'
                    '  #undef STATIC_PLUGIN_ID\n'
                    '#endif\n'
                    '#define STATIC_PLUGIN_ID ' + staticid + '\n')

        fo.write(headers1)


def create_dmtcp_c_file(numheaders):
    with open('dlsym_plt_DMTCP.c', 'w') as fo:
        fo.write('#include "DMTCP.h"\n')
        #for staticid in range(1,numheaders+1):
        #    fo.write('#include "DMTCP'+str(staticid)+'.h"\n')
        fo.write('#ifdef STATIC_PLUGIN_ID\n'
                 '  #undef STATIC_PLUGIN_ID\n'
                 '#endif\n'
                 '#define STATIC_PLUGIN_ID 0\n')


def finally_write_dmtcp_dlsym():
    fo = open('dlsym_plt_DMTCP.c', 'a')
    # dmtcp_dlsym
    dmtcp_dlsym = 'void * dmtcp_sdlsym(char *str, void *fptr, int pl_id, long int* addrs)'
    fo.write(dmtcp_dlsym)

    opencurl(fo)
    staticvars = (
        '  char filename[200] = {0};\n'
        '  strcat(filename, "./addrs/"); strcat(filename, str); strcat(filename, "__dmtcp.addr");\n'
    )
    fo.write(staticvars)

    fn = """
  if ((pl_id == 0 && addrs[0] == 0) || (pl_id > 0 && addrs[pl_id-1] == 0)) {
    int numOfWrappers = 0;
    char *string = malloc(sizeof(char)*1000);
    int fd = open(filename, O_RDONLY);
    char *token;
    if (fd == -1) { printf("*** *** NO FILE for %s\\n", str); exit(1); }
    read(fd, string, sizeof(char)*1000);
    while ((token = strsep(&string, ",")) != NULL)
      if (token[0] != '\\0') {
        addrs[numOfWrappers++] = strtol(token, NULL, 16);
      }
    free(string);
    close(fd);
  }
  while (pl_id < MAX_NUM_LIBS)
  {
    if (strcmp(str, "dmtcp_initialize_plugin") == 0) return 0; //THIS IS TEMPORARY HACK
    if (addrs[pl_id] != 0)
      return (void *)addrs[pl_id];
    ++pl_id;
  }
  exit(1);
}
    """
    #fn = fn.format(symbolToFind)
    fo.write(fn)

    fo.close()


def finally_write_h_file(staticid):
    with open('DMTCP' + staticid + '.h', 'a') as fo:
        fo.write('#endif //__DMTCP' + staticid + '_H_\n')


def opencurl(f):
    if not f.closed:
        f.write('{\n')


def closecurl(f):
    if not f.closed:
        f.write('}\n')


# FOR EACH SYMBOL
def append_addrs_h_file(symbolToFind, staticid):
    fo = open('DMTCP' + staticid + '.h', 'a')

    fo.write('extern long int ' + symbolToFind + 'addrs[100];\n')

    fo.close()


# FOR EACH SYMBOL
def append_dmtcp_plt(symbolToFind):

    # Open c file
    fo = open('dlsym_plt_DMTCP.c', 'a')

    # long int <symbol>addrs[100]
    addrs = 'long int ' + symbolToFind + 'addrs[MAX_NUM_LIBS];\n'
    fo.write(addrs)

    # <symbol>__dmtcp_plt
    dmtcp_plt = 'void {0}__dmtcp_plt();\n'.format(symbolToFind)
    fo.write(dmtcp_plt[:-2])

    opencurl(fo)
    fo.write('  ')
    #fo.write('void * __fptr = (void *) NEXT_FNC_S_DEFAULT('+symbolToFind+');\n')
    fo.write('SETUP_FPTR(' + symbolToFind + ');\n')

    fo.write('  ')
    fo.write('DELETE_CALL_FRAME();\n')

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
                    string = symbol.name  #.decode("utf-8")
                    listToWrite.append(string[:string.index('_wrap__dmtcp_')])

    print(object_file, listToWrite)
    return listToWrite


def append_all_library_wrappers_dmtcp(lib_plugin_id, l_object_files):
    print(l_object_files)
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
    print(l_lines)
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
                string = (
                    '%s %s' % (
                        symbol.name,  #.decode("utf-8"),
                        format_hex(symbol['st_value'])))
                if symbolToFind in str(symbol.name):
                    if symbolToFind == symbol.name:  #.decode("utf-8"):
                        actualFunc = string
                    listToWrite.append(string)
            break

    # Regular expression to match only dmtcp wrappers
    listToWrite = [
        x for x in listToWrite
        if re.search(symbolToFind + r'_wrap__dmtcp_\d+', x) != None
        and x.find(symbolToFind) == 0
    ]

    # If no symbolToFind... Exit
    if len(listToWrite) < 1:
        print("*** *** No symbols found for: " + symbolToFind +
              "_wrap__dmtcp_*")
        sys.stdout.flush()
        #sys.exit(1)

    # Sort list of strings of address and symbol name
    listToWrite.sort()
    listToWrite += [actualFunc]
    print(listToWrite)
    old_listToWrite = listToWrite

    # Remove the name portion since sorted
    listToWrite = [x.split(' ', 1)[1] for x in listToWrite]

    # Put in 0 (NULL) hole library that don't have symbol
    with open('all_library_wrappers_dmtcp.nz', 'r') as f:
        l_lines = f.readlines()
        for ind, line in enumerate(l_lines):
            if symbolToFind + "_wrap__dmtcp_" + str(
                    ind +
                    1) not in old_listToWrite[ind] or symbolToFind not in line:
                listToWrite.insert(ind, '0')

    # mkdir
    if not os.path.exists('./addrs'):
        os.mkdir('addrs')
    cwd = os.getcwd() + r'/addrs/'

    # Open file, filename will be: symbolToFind + '__dmtcp_*.addr'
    fileToWrite = cwd + symbolToFind + r'__dmtcp.addr'
    write_to_file(fileToWrite, listToWrite)
    print(listToWrite)
    print("\tThe addresses directly above has been written out to : " +
          fileToWrite + "\n\n")


def faster_process_file(filename, list_of_symbolToFind):
    dictionary = dict()
    actualFunc = ""
    listToWrite = []
    print('Processing file: ', filename)
    print('\tfor symbol: ', list_of_symbolToFind)
    print('\n\n *******\n')
    with open(filename, 'rb') as f:
        elffile = ELFFile(f)
        for section in elffile.iter_sections():
            if not isinstance(section, SymbolTableSection):
                continue
            if section['sh_entsize'] == 0:
                print('No Symbol Table!!!')
                continue
            for nsym, symbol in enumerate(section.iter_symbols()):
                string = (
                    '%s %s' % (
                        symbol.name,  #.decode("utf-8"),
                        format_hex(symbol['st_value'])))
                if "_wrap__dmtcp_" in symbol.name or any(
                        symbol.name == s for s in list_of_symbolToFind):
                    listToWrite.append((symbol.name,
                                        format_hex(symbol['st_value'])))

    listToWrite.sort()
    print(listToWrite)

    if len(listToWrite) < 1:
        sys.exit(1)

    # mkdir
    if not os.path.exists('./addrs'):
        os.mkdir('addrs')
    cwd = os.getcwd() + r'/addrs/'

    num_libs = 0
    with open('all_library_wrappers_dmtcp.nz', 'r') as f:
        lines = f.readlines()
        num_libs = len(lines)
    print(num_libs)

    # CURRENTLY MAKES AN ERROR
#    while len(listToWrite) > 0:
#        tmpl = []
#        real_sym = listToWrite[0]
#        del listToWrite[0]
#        while len(listToWrite) > 0 and "_wrap__dmtcp_" in listToWrite[0][0]:
#            print(listToWrite[0], end=' ')
#            tmpl.append(listToWrite[0])
#            del listToWrite[0]
#        tmpl.append(real_sym)
#        print(tmpl)
#
#        for n in range(num_libs):
#            if tmpl[-len(str(n)):] != str(n):
#                tmpl.insert(n, ('0', '0'))
#        print(tmpl)
#        print("**************************")

#        fileToWrite = cwd + real_sym[0] + r'__dmtcp.addr'
#        write_to_file(fileToWrite, [sym_and_addr[1] for sym_and_addr in tmpl])
    # ALTERNATIVE
    for stf in listToWrite:
        if '_wrap__dmtcp_' in stf[0]:
            continue

        tmpl = [('0', '0') for x in range(num_libs+1)]
        #tmpl = [x for x in listToWrite if stf[0]+'_wrap__dmtcp_' in x[0].strip()]
        tmpl[-1] = stf
        print(tmpl)

        for x in listToWrite:
            if stf[0]+'_wrap__dmtcp_' == x[0].strip()[:len(stf[0]+'_wrap__dmtcp_')]:
                print (x[0].split('_'), int(x[0].split('_')[-1]))
                tmpl[int(x[0].split('_')[-1]) - 1] = x


        print(tmpl)
        print("**************************")
        fileToWrite = cwd + stf[0] + r'__dmtcp.addr'
        write_to_file(fileToWrite, [sym_and_addr[1] for sym_and_addr in tmpl])


    return


# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

if __name__ == '__main__':
    if sys.argv[1] == '-hfile':

        # create DMTCH.h
        create_dmtcp_h_file_base()
        all_syms = dict()
        for filename in sys.argv[2:]:
            with open(filename, 'r') as fo:
                for line in fo:
                    if line.isspace():
                        continue
                    symbolToFind = line.strip()
                    if symbolToFind in all_syms:
                        all_syms[symbolToFind] += 1
                    else:
                        all_syms[symbolToFind] = 1
        for sym in all_syms:
            append_addrs_h_file(sym, '')

        finally_write_h_file('')

    elif sys.argv[1] == '-cfile' and len(sys.argv) > 2:
        # create dmtcp_plt_DMTCP.c
        create_dmtcp_c_file(len(sys.argv) - 2)

        all_syms = dict()
        for filename in sys.argv[2:]:
            with open(filename, 'r') as f:
                for line in f:
                    if line.isspace():
                        continue
                    symbolToFind = line.strip()
                    if symbolToFind in all_syms:
                        all_syms[symbolToFind] += 1
                    else:
                        all_syms[symbolToFind] = 1

        for sym in all_syms:
            append_dmtcp_plt(sym)

        finally_write_dmtcp_dlsym()

    elif sys.argv[1] == '-lib':
        print(str(int(sys.argv[2]) - 1))
        append_all_library_wrappers_dmtcp(
            str(int(sys.argv[2]) - 1), sys.argv[3:])

    elif sys.argv[1] != None and sys.argv[2] != None:
        # sort all_library_wrappers_dmtcp.nz here
        sort_all_library_wrappers_dmtcp()

        list_of_symbolToFind = []
        for stf in sys.argv[2:]:
            with open(stf, 'r') as f:
                l_lines = f.readlines()
                list_of_symbolToFind.extend(
                    [sym.strip() for sym in l_lines if sym.strip() != ''])
        faster_process_file(sys.argv[1], list_of_symbolToFind)

    else:
        print("***WRONG SYNTAX FOR CALLING elf.py")
