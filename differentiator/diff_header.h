#ifndef DIFFERENTIATOR_DIFF_H
#define DIFFERENTIATOR_DIFF_H

#include "tree_header.h"
#include "DSL.h"

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

const char FILE_INP_INORDER[] = "/home/shugaley/proga/projects/1_sem/differentiator/input2"  ;
const char FILE_OUT_INORDER[] = "/home/shugaley/proga/projects/1_sem/differentiator/tree_inorder_output" ;
const char DOT[]              = "/home/shugaley/proga/projects/1_sem/differentiator/dot_out.dot"         ;
const char FILE_OUT_TEX[]     = "/home/shugaley/proga/projects/1_sem/differentiator/outtex.tex"          ;

//#define outtex stderr

tree Differentiate(tree* tree_eq);

tree_elem* Create_TreeDiffElem(tree_elem* pos);
tree_elem* Add_TreeDiffElem   (tree_data new_data, tree_elem* pos_left, tree_elem* pos_right);
tree_data  Create_TreeDiffNewData(int mode, int num_value, char* str_value);

int Which_com(char* com_name);
tree_elem* Copy(tree_elem* pos);

//simple--------

void Simplify_tree(tree_elem* pos);

//Equation_creator--------

tree_elem* Create_TreeEquation     (tree* tree_eq, FILE* inp_diff);
tree_elem* Create_TreeEquationElem (tree* tree_eq, char* buffer, size_t* i_sym, tree_elem* pos);
tree_elem* Create_TreeEquationHead (tree* tree_eq, char* buffer, size_t* i_sym);
data_t  Create_TreeEquationNewElem (               char* buffer, size_t* i_sym);
void       Create_TreeDiffElem$    (tree* tree_eq, tree_data new_elem,          tree_elem* pos);
inline size_t Skip_Space(char* buffer, size_t i_sym);


//Equation_creator_rec----------------------

tree_elem* Create_TreeEquationRec(tree* tree_eq, FILE* inp_diff);
inline const char* Skip_SpaceRec(const char* buffer);
bool Swap_Elem(tree_elem** str_1, tree_elem** str_2);
char* Create_word(FILE* out);


//Get-------------

//G::=E'\0'
tree_elem* GetG(const char* str);

//E::=T{[+-]T}+
tree_elem* GetE();

//T::=P{[*/]}*
tree_elem* GetT();

//P::='('E')'| N | Func(E) | Id
tree_elem* GetP();

tree_elem* GetPow();

//N::=['0'-'9']+
tree_elem* GetN();

//Id::=[a-z]+
tree_elem* GetId();

//
tree_elem* GetFunc();



//Latex----------
void Latex      (tree* tree_name, FILE* outtex);
void Latex_begin(                 FILE* outtex);
void Latex_end  (                 FILE* outtex);
void Print_Tree   (tree_elem* pos, FILE* out);
void Print_TreeMul(tree_elem* pos, FILE* out);
void Comment_Latex(FILE* out);


//bool-------

bool is_end          (tree_elem* pos);
bool is_$            (tree_elem* pos);
bool is_zero         (tree_elem* pos);
bool is_one          (tree_elem* pos);
bool is_high_priority(tree_elem* pos);
bool is_num          (tree_elem* pos);

//Reader-------

char* create_ar_text(FILE* ptr_input);
size_t count_size();

#endif //DIFFERENTIATOR_DIFF_H
