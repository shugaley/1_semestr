#include <cstdio>
#include <cstdlib>
#include <string>
#include <cctype>
#include <cassert>
#include <sys/stat.h>


int assembler(struct LINE* lines_text, size_t nlines, char* bytecode);

char WhichCommand(char* str_command);
char WhichCommandReg(char* str_command);

bool DeleteComm(struct LINE* lines_text, int nlines);

int FindParams(struct LINE lines_text, char* param);

struct LINE* create_all(size_t* nlines);

char* create_ar_text(FILE* pnt_input, size_t* size);
struct LINE* create_struct_lines(char* text, size_t nlines, size_t size);

size_t count_size();
size_t count_symbol(char* text, size_t size, char symbol);

struct LINE
{
    int length;
    char* ptrline;
};
