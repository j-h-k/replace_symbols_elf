# replace_symbols_elf

### Takes as command line arguments:
-o <objfile> [more objfiles]  
-s <symbol> [more symbols]    
-k <symbol> [more symbols]  
--singlesymbol=<symbol>  
--keepnumsymbol=<symbol>  
--singlestr=<symbol>
--keepnumstr=<symbol>

#### -s and --singlesymbol do the same thing:
if the given symbol is **foo** will change to **foo__dmtcp_plt** for all given object files.      

#### -k and --keepnumsymbol do the same thing:
if given only one object file and the given symbol is **foo** will change the symbol **to foo__dmtcp_1**  
if given n number of object files and the given symbol **foo**, the first object file on the arguments will be **foo__dmtcp_1**,
and in the second object file **foo** will be **foo__dmtcp_2**, etc until n.

#### --singlestr and --keepnumstr
Use if you want to change defaults of the string appended:
| Long Flags         | String Appended to Symbol  |
| ------------------ |:--------------------------:|
| no --singlestr     | <symbol>\_\_dmtcp\_plt        |
| --singlestr=<str>  | <symbol><str>              |
| no --keepnumstr    | <symbol>\_\_dmtcp\_*          |
| --keepnumstr=<str> | <symbol><str>*             |

**The \* in the table is [0-9]+**
