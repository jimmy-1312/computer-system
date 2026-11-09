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