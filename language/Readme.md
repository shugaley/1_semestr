# LANGUAGE 

One day i thought that there are no belarussian program language. And I fixed this problem.  

## Description

Input is .txt file which is written in my language. 

* [Tokenization](https://github.com/shugaley/1_semestr/blob/master/language/lang_tokenization.cpp). - it splits my language on tokens:
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

## Syntax

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
