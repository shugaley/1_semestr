#ifndef CPU_HEADER_CPU_H
#define CPU_HEADER_CPU_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <cctype>
#include <cassert>
#include <sys/stat.h>
#include "stack_header.h"

struct CPU
{
    My_stack stk_CPU = {};
    int* registers = nullptr;
};


bool main_CPU(char* bytecode, CPU* processor);

void WhichCommandCPU (char bytecode);
void WhichCommandRegCPU (char bytecode);

//Reader------------------

char* create_ar_text(FILE* ptr_input);
size_t count_size();



#endif //CPU_HEADER_CPU_H
