#ifndef AKINATOR_AKINATOR_HEADER_H
#define AKINATOR_AKINATOR_HEADER_H

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

const char FILE_INP[] = "/home/shugaley/proga/projects/1_sem/akinator/tree_preorder_input" ;
const char FILE_OUT[] = "/home/shugaley/proga/projects/1_sem/akinator/tree_preorder_output";


bool Read_TreeAkinator(tree* tree_ak, FILE* ak_input);
char* Dialogue(const char* quest, ...);

//Quest---

tree_elem* Ask_Questions          (tree* tree_ak                );
tree_elem* Answer_LastQuestion    (tree* tree_ak, tree_elem* pos);
tree_elem* Answer_NewElemQuestion (tree* tree_ak, tree_elem* pos);

//Add-----

tree_elem* Add_TreeAkinatorElem     (tree* tree_ak, tree_elem* pos);
tree_elem* Search_TreeAkinatorAnswer(tree* tree_ak, char* string);
bool Swap_Str(char** str_1, char** str_2);

//PrintWay-----

bool Print_WayAnswer   (tree* tree_ak, char* ans               );
bool Print_WayTwoAnswer(tree* tree_ak, char* ans_1, char* ans_2);
inline tree_elem** Create_WayAnswer(tree_elem* pos, size_t maxsize_way, size_t* size_way);
inline bool Output_WayAnswer(tree_elem** way, size_t i_way);
inline bool Print_CharactAnswer(char* charact);

//Creator------

tree_elem* Create_TreeAkinatorElem(tree* tree_ak, char* buffer, size_t* i_sym, tree_elem* pos);
tree_elem* Create_TreeAkinatorHead(tree* tree_ak, char* buffer, size_t* i_sym);
char* Create_String     (char* buffer, size_t* i_sym);
inline size_t Skip_Space(char* buffer, size_t  i_sym);

//Reader-------

char* create_ar_text(FILE* ptr_input);
size_t count_size();

//-----

#endif //AKINATOR_AKINATOR_HEADER_H
