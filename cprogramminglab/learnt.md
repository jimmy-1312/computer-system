**第一課**
Two main component for running the C command.
(1)Preprocessor Directives 前置處理器指令
(2)Compiler

檔案 —》preprocessor replace content -》compiler compile -》assembler -》linkers link -》final executive file.


When we want to compile our code file, 
(1)Preprocessor will search for all #tags, and then replace them with other contents.
對原始碼進行文字替換、檔案引入或條件篩選的特殊命令
#include <stdio.h>   // 替換成base code of <stdio.h>
#define MAX 100      // 將程式中所有的 MAX 替換為 100

(2)The compiler will compile, seperately for every file.

(3)And then given different compiled file in format "file.s" , 把内容轉成assemble code(注意！！)

(4)Assmblers turn ".s" into ".o", which can be read by computers(二進制)

(4)Linkers link the files and turn them into runnables.


**第二課**
(1 First step: into C code)preprocessor replace all tags with code, so now the files are all with C code.
(2 Second step:into assembly)Compiler create a scope symbol table which record the [var_name,type] for every layer
declaration only record [var_name,type/size], definition record [var_name,type/size,position]
declaration only happen in global scope, every scope have their own scope symbol table
compiler replace the C code into instruction + positions, and then give it to linker, also give the global scope symbol table

So the compiler pass three things: 1. The machine code 2. the global scope table 3. Relocation table(the temp address need to be replaced)
In this step, the function with definitions are already recorded var_name,size and position

(3: into exe) the linker replace the position inside relocation table with real positions.

The final exe can be made.