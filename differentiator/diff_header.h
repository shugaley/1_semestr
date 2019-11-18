#ifndef DIFFERENTIATOR_DIFF_H
#define DIFFERENTIATOR_DIFF_H

#include "tree_header.h"

#define tree_library

#ifndef tree_library
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cassert>
#include <sys/stat.h>
#include <cmath>
#include <cstdarg>
#endif


enum MODE
{
    MODE_NUMBER   = 1,
    MODE_VAR      = 2,
    MODE_OPERATOR = 3,
    MODE_COMMAND  = 4,
};

const char FILE_INP_INORDER[] = "/home/shugaley/proga/projects/1_sem/akinator/tree_inorder_input"  ;
const char FILE_OUT_INORDER[] = "/home/shugaley/proga/projects/1_sem/akinator/tree_inorder_output" ;


tree_elem* Create_TreeEquation    (tree* tree_diff, FILE* inp_diff);
tree_elem* Create_TreeEquationElem(tree* tree_ak, char* buffer, size_t* i_sym, tree_elem* pos);
tree_elem* Create_TreeEquationHead(tree* tree_ak, char* buffer, size_t* i_sym);

data_t Create_TreeEquationNewElem(char* buffer, size_t* i_sym                  );
int    Which_Elem                (char* buffer, size_t* i_sym, data_t* new_data);

inline size_t Skip_Space(char* buffer, size_t i_sym);

//Reader-------

char* create_ar_text(FILE* ptr_input);
size_t count_size();

#endif //DIFFERENTIATOR_DIFF_H
