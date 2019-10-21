#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cassert>
#include <sys/stat.h>


int assembler(struct LINE* lines_text, char* bytecode);

char WhichCommand(char* str_command);
char WhichCommandReg(char* str_command);

bool DeleteComm(char* str);

int FindParams(char* str);

//Reader---------------

struct LINE* create_all(FILE* ptr_input);

char* create_ar_text(FILE* pnt_input, size_t* size);
struct LINE* create_struct_lines(char* text, size_t nlines, size_t size);

size_t count_size();
size_t count_symbol(const char* text, size_t size, char symbol);

//--------------------------

struct LINE
{
    int length;
    char* ptrline;
};
