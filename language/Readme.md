# LANGUAGE 

One day i thought that there are no belarussian program language. And I fixed this problem.  

## Description

Input is .txt file that is written in my language. 

* [Tokenization](https://github.com/shugaley/1_semestr/blob/master/language/lang_tokenization.cpp) - splits my language on tokens:
```cpp
enum MODE_TOKEN
{
    MODE_TOKEN_END  = 0,
    MODE_TOKEN_NUM  = 1,
    MODE_TOKEN_OP   = 2,
    MODE_TOKEN_PUNC = 3,
    MODE_TOKEN_ID   = 4,
};
```

* [Front_End](https://github.com/shugaley/1_semestr/blob/master/language/lang_tokenization.cpp) - makes the tree of my language. There are my [tree library](https://github.com/shugaley/1_semestr/tree/master/akinator/tree "My own tree library"). Example: 
![](https://github.com/shugaley/1_semestr/blob/master/language/treefisrt.jpg)

* [Middle_End](https://github.com/shugaley/1_semestr/blob/master/language/lang_middle_end.cpp) - simplifies my tree (
arithmetic expressions and derivatives).

* [Back_End](https://github.com/shugaley/1_semestr/blob/master/language/lang_back_end.cpp) - translate tree to my assembler for my [processsor](https://github.com/shugaley/1_semestr/tree/master/Processor "My own virtual processor") (.txt output file).

* [Front_End_Back](https://github.com/shugaley/1_semestr/blob/master/language/lang_tokenization.cpp) - translate different  [standard](https://docs.google.com/document/d/1i-M6D6Sjlg4CRe6YHWInJ3B3d87_znxn3XpRUEa2Gos/edit "The tree standard of our group") tree to my language.

## Syntax

There is syntax of my great language:

`бацька`⠀⠀⠀ -> main  
`пасеяць`⠀⠀⠀-> int  
`угнаенне`⠀⠀-> get  
`ураджай`⠀⠀⠀-> put  
  
`калi`⠀⠀⠀⠀⠀ -> if  
`iнакш`⠀⠀⠀⠀⠀-> else  
`пакуль`⠀⠀⠀⠀-> while

`гэта`⠀⠀⠀⠀⠀⠀ ->⠀=  
`разам з`⠀⠀⠀⠀  ->⠀+  
`без`⠀⠀⠀⠀⠀⠀ ⠀->⠀-  
`прапалоць`⠀⠀⠀->⠀*  
`скасiць`⠀⠀⠀ ⠀->⠀\  
  
`як`⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀-> ==  
`больш чым`⠀⠀⠀⠀⠀⠀-> >  
`меньш чым`⠀⠀⠀⠀⠀⠀-> <  
`больш-равно чым`⠀⠀-> >=  
`меньш-равно чым`⠀⠀-> <=  

## Examples

There are examples of programs that are written in my language:

* [Square](https://github.com/shugaley/1_semestr/blob/master/language/input-output/lang_input_square) - solves square equation.


* [Factorial](https://github.com/shugaley/1_semestr/blob/master/language/input-output/lang_input_fact) - counts factorial.
