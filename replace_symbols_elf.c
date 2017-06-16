// elf..
#include <elf.h>

// write, getopt..
#include <unistd.h>
#include <getopt.h>

// printf..
#include <stdio.h>

// exit..
#include <stdlib.h>

// assert
#include <assert.h>

// c strings..
#include <string.h>

// for open..
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// utilities
#include "util.h"


// MACROS
#define c_print(x) write(1,x,strlen(x))

// CONST
const int debug = 0;

// Future function implementations:
int readInElfHeader();
int readInSymbolTable();
int readInStringTable();
int readInSectionHeaderTable();

int writeOutElfHeader();
int writeOutSymbolTable();
int writeOutStringTable();
int wrtieOutSectionHeaderTable();

// Helper functions
int runGetOpt(int argc, char **argv, int *objIndex, char **objList,
              int *singleSymbolIndex, char **singleSymbolList,
              int *keepNumSymbolIndex, char **keepNumSymbolList,
              char **singleStrPtr, char **keepNumStrPtr)
{
  int c;
  int digit_optind = 0;
  while (1) {
    int this_option_optind = optind ? optind : 1;
    int option_index = 0;
    static struct option long_options[] = {
      {"object", required_argument, 0, 0},
      {"singlesymbol", required_argument, 0, 1},
      {"keepnumsymbol", required_argument, 0, 2},
      {"singlestr", required_argument, 0, 3},
      {"keepnumstr", required_argument, 0, 4}
    };
    
    c = getopt_long(argc, argv, "o:s:k:", long_options, &option_index);
    if (c == -1) break;

    switch(c) {
      printf("option %s", long_options[option_index].name);
      if (optarg)
        printf(" with arg %s", optarg);
      printf("\n");

    case 0: //object
        objList[(*objIndex)++] = strdup(optarg);
        break;  
    case 'o':
      optind--;
      do {
        objList[(*objIndex)++] = strdup(argv[optind]);
        optind++;
      } while (optind < argc && *argv[optind] != '-');
      break;

    case 1: //single symbol
      singleSymbolList[(*singleSymbolIndex)++] = strdup(optarg);
      break;
    case 's':
      optind--;
      do {
        singleSymbolList[(*singleSymbolIndex)++] = strdup(argv[optind]);
        optind++;
      } while (optind < argc && *argv[optind] != '-');
      break;

    case 2: //multiple symbol requiring numbering
      if (objIndex ==0) {
        printf("***If need to assign numbering to symbol, list object files first!\n");
        perror("Syntax: ./replace-symbols-name -o <obj file> [obj files] --keepnumsymbol=<symbol>");
        exit(1);
      }
      keepNumSymbolList[(*keepNumSymbolIndex)++] = strdup(optarg);
      break;
    case 'k':
      if (objIndex ==0) {
        printf("***If need to assign numbering to symbol, list object files first!\n");
        perror("Syntax: ./replace-symbols-name -o <obj file> [obj files] --keepnumsymbol=<symbol>");
        exit(1);
      }
      optind--;
      do {
        keepNumSymbolList[(*keepNumSymbolIndex)++] = strdup(argv[optind]);
        optind++;
      } while (optind < argc && *argv[optind] != '-');
      break;

    case 3:
      if (*singleStrPtr) {
        free(*singleStrPtr);
        printf("***Only use the flag --singestr=<symbol> once.\n");
        exit(1);
      }
      *singleStrPtr = strdup(optarg);
      break;
    case 4:
      if (*keepNumStrPtr) {
        free(*keepNumStrPtr);
        printf("***Only use the flag --keepnumstr=<symbol> once.\n");
        exit(1);
      }
      *keepNumStrPtr = strdup(optarg);
      break;

    default:
      printf("?? getopt returned character code 0%o ??\n", c);
    }
  }

  if (optind < argc) {
    printf("non-option ARGV-elements: ");
    while (optind < argc)
      printf("%s ", argv[optind++]);
    printf("\n");
    return -1;
  }
  
  return 0;
}

void printObjectFileNames(int count, char* list[])
{
  printf("The object files to modify are:\n");
  for (int i = 0; i < count; ++i)
    printf("(%d)\t%s\n", i, list[i]);
}

void printSymbolsToChange(int count, char *list[], char *strToAppend, int isSingle)
{
  printf("\n%s\n", isSingle ? 
                  "Single Symbols planned on changing:" : 
                  "Keep Number Symbols planned on changing:");
  for (int i = 0; i < count; ++i) {
    char str[100] = {0};
    strcat(str, list[i]);
    strcat(str, " --> ");
    strcat(str, list[i]);
    if (strToAppend) {
      if (isSingle) strcat(str, strToAppend);
      else {
        strcat(str, strToAppend);
        strcat(str, "*");
      }
    }
    else {
      if (isSingle) strcat(str, "__dmtcp_plt");
      else strcat(str, "__dmtcp_*");
    }
    printf("(%d)\t%s\n", i, str);
  }
}

int checkAndFindElfFile(char *objFileName, Elf64_Ehdr* ehdr)
{

   read_metadata(objFileName, (char *)ehdr, sizeof(Elf64_Ehdr), 0);
  
   if (ehdr->e_ident[EI_MAG0] != 0x7f && ehdr->e_ident[EI_MAG1] != 'E' &&    // CHECK IF ELF
      ehdr->e_ident[EI_MAG2] != 'L'  && ehdr->e_ident[EI_MAG3] != 'F') {
      printf("Not an ELF executable\n");
      return -1;
   }
//  printf("\n");
  switch(ehdr->e_type) {
  case ET_EXEC:
     printf("WARNING: The ELf type is that of an executable. (%s)\n", objFileName);
    break;
  case ET_REL:
    printf("SUCCESS: The ELF type is that of an relocatable. (%s)\n", objFileName);
    break;
  default:
    printf("ERROR: The ELF type is that NOT of an EXEC nor REL. (%s)\n", objFileName);
    return -1;
  }
  return 0;
}

int findSymtabAndStrtabAndShdr(char *objFileName, Elf64_Ehdr ehdr, Elf64_Shdr **shdr,
                                Elf64_Shdr **symtab, Elf64_Shdr **strtab)
{
  unsigned long shoff = ehdr.e_shoff;  // Section header table offset
  unsigned long shnum = ehdr.e_shnum;  // Section header num entries
  *shdr = malloc(sizeof(Elf64_Shdr) * ehdr.e_shnum);  // Copy of section header table entries
  read_metadata(objFileName, (char *)*shdr, (shnum)*sizeof(Elf64_Shdr), shoff); // read in section headers

  Elf64_Shdr * hdr = *shdr;
  int idx;

  // Go through the section table entries
  for (idx = 0; idx < shnum; idx++, hdr++) {
    switch (hdr->sh_type) {
    case SHT_SYMTAB:
      *symtab = hdr;
      if (debug) printf("symtab: size=%lu offset=%p\n", hdr->sh_size, (void *)hdr->sh_offset);
      *strtab = *shdr + hdr->sh_link;
      if (debug) printf("strtab: size=%lu offset=%p\n", (*strtab)->sh_size, (void *)(*strtab)->sh_offset);
      assert((*strtab)->sh_type == SHT_STRTAB);
      break;
    }
  }
  if (*symtab == NULL || *strtab == NULL) return -1;
  if (debug) printf("%p %p %s\n",*symtab,*strtab, "Found Symbol table and String Table");
  return 0;
}

int loopSymbolTableForSymbol(int index, char **list,
                                    Elf64_Sym *symtab_ent, unsigned int symtab_size,
                                    char *strtab_ent, int isSingle)
{
	if (!index) return 0;
  Elf64_Sym * sym = NULL;

  printf("\t%s\n", isSingle ? "Single Symbols" : "Keep Number Symbols");
  for (int i = 0; i < index; ++i) {
    int found = 0;
    for (sym = symtab_ent; (char *)sym < (char *)symtab_ent + symtab_size; sym++) {
      if (sym->st_name != 0) {
        char *symtab_symbol = strtab_ent + sym->st_name;
        if (strcmp(symtab_symbol, list[i]) == 0) {
          printf("\t\tsymbol: %s  |  ", strtab_ent + sym->st_name);
          printf("sym->st_value: %p\n", (void *)sym->st_value);
          found = 1;
        }
      }
    }
    if (!found) {
      printf("\t\t***Could not find: %s\n", list[i]);
      if (!isSingle) { 
        printf("\t\tKeep Number Symbol : (%s) was NOT FOUND. [ERROR]\n", list[i]);
        return -1;
      }
    }
  }
  return 0;
}

int checkIfSymbolsExist(char *objFileName, int singleSymbolIndex, char **singleSymbolList, 
                        int keepNumSymbolIndex, char **keepNumSymbolList,
                        Elf64_Shdr *symtab, Elf64_Shdr *strtab)
{
  Elf64_Sym * sym = NULL;
  Elf64_Sym * symtab_ent = NULL;
  char *strtab_ent = NULL;

  symtab_ent = malloc(symtab->sh_size);
  if (debug) printf("symtab: size=%lu offset=%p\n", symtab->sh_size, (void *)symtab->sh_offset);
  read_metadata(objFileName, (char *)symtab_ent, symtab->sh_size, symtab->sh_offset);
  strtab_ent = malloc(strtab->sh_size);
  if (debug) printf("strtab: size=%lu offset=%p\n", strtab->sh_size, (void *)strtab->sh_offset);
  read_metadata(objFileName, strtab_ent, strtab->sh_size, strtab->sh_offset);

  unsigned int symtab_size = symtab->sh_size;

  printf("In file %s symbols checked:\n", objFileName);
  loopSymbolTableForSymbol(singleSymbolIndex, singleSymbolList, 
                          symtab_ent, symtab_size, strtab_ent, 1);

  if (loopSymbolTableForSymbol(keepNumSymbolIndex, keepNumSymbolList, 
                              symtab_ent, symtab_size, strtab_ent, 0) == -1) {
    return -1;
  }
  return 0;
}

int calculateBytesNeeded(int index, char **list, char *strToAppend, int isSingle)
{
  int numberOfSymbols = index;
  char strNum[100] ={0};
  sprintf(strNum, "%d", index);
  int result = 0;

  for (int i = 0; i < numberOfSymbols; ++i) {
    result += strlen(list[i]);
    if (strToAppend)
      result += (isSingle ? strlen(strToAppend) : strlen(strNum)) + 1;
    else {
      result += strlen("__dmtcp") 
                + (isSingle ? strlen("_plt") + 1 : strlen("_") + strlen(strNum) + 1);
    }
  }

  // align on 64 bytes..
  result = (result + 63) & -64; 

  return result;
}

int extendAndFixAfterStrtab(char *objFileName, Elf64_Ehdr *ehdr, Elf64_Shdr **shdr,
                            Elf64_Shdr **symtab, Elf64_Shdr **strtab, int add_space)
{
  Elf64_Off begin_next_section = (*strtab)->sh_offset + (*strtab)->sh_size; 
  Elf64_Off end_of_sections =    (*strtab)->sh_offset + (*strtab)->sh_size;

  ehdr->e_shoff += add_space; // We will be displacing section header table
  (*strtab)->sh_size += add_space;

  if (debug) printf("bns:%p  eos:%p\n", (void *)begin_next_section, (void *)end_of_sections);
  
  // Modify Section Header Table and write back
  int idx = 0;
  Elf64_Shdr *ptr = *shdr;
  for (; idx < ehdr->e_shnum; ++idx, ++ptr)
  {
    if (ptr->sh_offset > (*strtab)->sh_offset) {
      ptr->sh_offset += add_space;
    }
    if (ptr->sh_offset + ptr->sh_size > end_of_sections) {  // End of section header
      end_of_sections = ptr->sh_offset + ptr->sh_size;
    }
    if (debug) printf("bns:%p  eos:%p ptr:%p\n", (void *)begin_next_section, (void *)end_of_sections, ptr);
  }
  if (debug) printf("bns:%p  eos:%p\n", (void *)begin_next_section, (void *)end_of_sections);

  // Displace all sections after strtab by 'add_space'.
  assert(end_of_sections <= ehdr->e_shoff); 
  if (end_of_sections > begin_next_section) {
    char tmpbuf[end_of_sections - begin_next_section];
    read_metadata(objFileName, tmpbuf, sizeof(tmpbuf), begin_next_section);
    write_metadata(objFileName, tmpbuf, sizeof(tmpbuf),
                         begin_next_section + add_space);
  }

  // Write back section headers and ELF header
  write_metadata(objFileName, (char *)*shdr, (ehdr->e_shnum)*sizeof(Elf64_Shdr), ehdr->e_shoff);
  write_metadata(objFileName, (char *)ehdr, sizeof(Elf64_Ehdr), 0);
  
  return 0;
}

int addSymbolsAndUpdateSymtab(char *objFileName, int num, int index, char **list,
                              Elf64_Shdr *symtab, Elf64_Shdr *strtab,
                              unsigned long *prev_strtab_size, char *strToAppend, int isSingle)
{
  if (!index) return 0;
  // From previous function checkIfSymbolsExist(), we know all the symbols exist
  
  int numSymbolsToChange = index;
  unsigned int symtab_size = symtab->sh_size;

  Elf64_Sym *sym = NULL;
  char symtab_buf[symtab->sh_size];
  char strtab_buf[strtab->sh_size];
  char str[100] = {0};
  sprintf(str, "%d", num+1);

  read_metadata(objFileName, symtab_buf, symtab->sh_size, symtab->sh_offset);
  read_metadata(objFileName, strtab_buf, strtab->sh_size, strtab->sh_offset);

  for (int i = 0; i < numSymbolsToChange; ++i) {
    int found = 0;
    for (sym = (void *)symtab_buf; (char *)sym < (char *)symtab_buf + symtab->sh_size; sym++) {
      if (sym->st_name != 0) {

        char *symtab_symbol = strtab_buf + sym->st_name;

        if (strcmp(symtab_symbol, list[i]) == 0) {
          char newString[strlen(list[i]) + (strToAppend ? strlen(strToAppend) : strlen("__dmtcp"))
                        + (strToAppend ?
                            (isSingle ? 1 : strlen(str) + 1) :
                            (isSingle ? strlen("_plt") + 1 : strlen("_") + strlen(str) + 1))
                        ];
          memset(newString, 0, sizeof(newString));

          sym->st_name = *prev_strtab_size;

          // THIS MAKES IT WEAK!
          //sym->st_info = ELF64_ST_INFO(STB_WEAK, STT_NOTYPE);

          strcat(newString, list[i]);
         
          if (strToAppend) {
            strcat(newString, strToAppend);
						if (!isSingle) strcat(newString, str);
          }
          else { 
            strcat(newString, "__dmtcp");
            if (isSingle)
              strcat(newString, "_plt");
            else {
              strcat(newString, "_");
              strcat(newString, str);
            }
          }
          strcat(newString, "\0");
          strncpy((char *) strtab_buf + *prev_strtab_size, newString, sizeof(newString));
          *prev_strtab_size += strlen(newString) + 1;

          if (debug) printf("NEW STRING IS **** %s ****\n", newString);
          found = 1;
        }
      }
    }
    if (debug) printf("strtab->sh_size = %lu : prev = %lu\n", strtab->sh_size, *prev_strtab_size);
    if (!isSingle && !found) {
      printf("***Could not find: %s\n", list[i]);
      return -1;
    }
  }

  for (int i = *prev_strtab_size; i < strtab->sh_size; ++i)
    strtab_buf[i] = '\0';

  write_metadata(objFileName, (char *)symtab_buf, symtab->sh_size, symtab->sh_offset);
  write_metadata(objFileName, (char *)strtab_buf, strtab->sh_size, strtab->sh_offset);
  
  return 0;
}


// Main
int main(int argc, char **argv)
{
  int objIndex = 0;
  char** objList = malloc(100 * sizeof(char *));

  int singleSymbolIndex = 0;
  char **singleSymbolList = malloc(100 * sizeof(char *));      // Symbols to add "__dmtcp_plt" to
  char *singleStr = NULL;

  int keepNumSymbolIndex = 0;
  char **keepNumSymbolList = malloc(100 * sizeof(char *));    // Symbols to add "__dmtcp_*" to, where * is 0 to n
  char *keepNumStr = NULL;
  
  Elf64_Shdr * shdr = NULL;
  Elf64_Shdr * symtab = NULL;
  Elf64_Shdr * strtab = NULL;
  unsigned long prev_strtab_size = 0;

  printf("\n\n%s\n\n", "+++++++++++++++++++++++++++++++++ Started replace-symbols-name Program");

  if (argc < 4) {
    //perror("Syntax: ./change-symbol-names <obj file> symbol [othersymbols]");
    perror("Syntax: ./replace-symbols-name [-o | -s | --singlesymbol | --keepnumsymbol]");
    exit(1);
  }

  // Parse the arguments!
  assert(runGetOpt(argc, argv, &objIndex, objList, 
                  &singleSymbolIndex, singleSymbolList,
                  &keepNumSymbolIndex, keepNumSymbolList,
                  &singleStr, &keepNumStr) != -1);

  // Let user know which object files are going to change
  printObjectFileNames(objIndex, objList);

  // Let user know which symbols are going to change
  assert(singleSymbolIndex + keepNumSymbolIndex > 0);
  if (singleSymbolIndex) 
    printSymbolsToChange(singleSymbolIndex, singleSymbolList, singleStr, 1);
  if (keepNumSymbolIndex) 
    printSymbolsToChange(keepNumSymbolIndex, keepNumSymbolList, keepNumStr, 0);
  printf("\n\n");



  for (int i = 0; i < objIndex; ++i) {
    Elf64_Ehdr ehdr;

    // Check if file is valid and read in the ELF header
    assert(checkAndFindElfFile(objList[i], &ehdr) != -1);

    // Find symbol table and string table
    //   - shdr = malloc(); <-- on heap
    assert(findSymtabAndStrtabAndShdr(objList[i], ehdr, &shdr, &symtab, &strtab) != -1);
    prev_strtab_size = strtab->sh_size;

    // Check if the symbols exist first..
    assert(checkIfSymbolsExist(objList[i], singleSymbolIndex, singleSymbolList, 
                              keepNumSymbolIndex, keepNumSymbolList, symtab, strtab) != -1);

    // Extend the string table and whatever follows after.. 
    // Fix Elf header and Section header Table
    int add_space = calculateBytesNeeded(singleSymbolIndex, singleSymbolList, singleStr, 1)
                    + calculateBytesNeeded(keepNumSymbolIndex, keepNumSymbolList, keepNumStr, 0);
    assert(extendAndFixAfterStrtab(objList[i], &ehdr, &shdr, &symtab, &strtab, add_space) != -1);

    // Add dmtcp symbol name(s) and update symtab
    assert(addSymbolsAndUpdateSymtab(objList[i], i, singleSymbolIndex, singleSymbolList, 
                                    symtab, strtab, &prev_strtab_size, singleStr, 1) != -1);
    assert(addSymbolsAndUpdateSymtab(objList[i], i, keepNumSymbolIndex, keepNumSymbolList, 
                                    symtab, strtab, &prev_strtab_size, keepNumStr, 0) != -1);

    free(shdr);
  }
  free(singleSymbolList);
  free(keepNumSymbolList);

  printf("\n\n%s\n\n", "Finished replace-symbols-name Program +++++++++++++++++++++++++++++++++");
}
