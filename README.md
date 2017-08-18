# replace_symbols_elf 

#### Please do the following for lastest implementation for DMTCP:
  
$> cd ./example\_libdmtcp\<HIGHEST VALUE\>/  
$> make  

### Takes as command line arguments:
-o \<objfile\> [more objfiles]  
\-\-singlesymbol=\<symbol\>   or -s \<symbol\> [more symbols]  with  [\-\-singlestr=\<symbol\>]  
\-\-keepnumsymbol=\<symbol\>  or -k \<symbol\> [more symbols]  with  [\-\-keepnumstr=\<symbol\>]  
\-\-completesymbol=\<symbol\> or -c \<symbol\> [more symbols]  with [\-\-completestr=\<sybmol\>]  
___
#### -s and --singlesymbol do the same thing:
if the given symbol is **foo** will change to **foo__dmtcp_plt** for all given object files.  
remember, **\-s** takes more than 1 symbol (i.e. **\-s foo doo hoo** is valid)  

#### -k and --keepnumsymbol do the same thing:
if given only one object file and the given symbol is **foo** will change the symbol to **foo__dmtcp_1**
if given n number of object files and the given symbol is **foo**, the first object file's **foo** will be **foo__dmtcp_1**, and the second object file's **foo** will be **foo__dmtcp_2**, etc until n.

#### -c and --completesymbol:
if given symbol is **foo** will replace with given \-\-completestr=**\<symbol\>**  


#### REMEMBER
\-\-singlestr and \-\-keepnumstr and \-\-compeltestr can only be used once per program execution.  
However, an abundant amount of (\-\-singlesymbol, \-s) or (\-\-keepnumsymbol, \-k) or (\-\-completesymbol, \-c) may be supplied.  

___
#### --singlestr and --keepnumstr
Use if you want to change defaults of the string appended:  

Long Flags | String Appended to Symbol  
---------- | -------------------------  
no \-\-singlestr | \<symbol\>\_\_dmtcp\_plt  
\-\-singlestr=\<str\> | \<symbol\>\<str\>  
no \-\-keepnumstr  | \<symbol\>\_\_dmtcp\_*  
\-\-keepnumstr=\<str\> | \<symbol\>\<str\>*  

_The \* in the table is [0-9]+_
___

