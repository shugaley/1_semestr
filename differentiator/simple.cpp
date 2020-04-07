#include "diff_header.h"

//bool change = false;

#define L pos->left
#define R pos->right

extern FILE* outtex;

void Simplify_tree(tree_elem* pos)
{
    if(!pos || is_end(pos)) return;

    Simplify_tree(pos->left );
    Simplify_tree(pos->right);

    if(pos->data.mode == MODE_COMMAND)
    {
        Comment_Latex(outtex);
        Print_Tree(pos, outtex);
        fprintf(outtex, "\n\n");
    }

    if(pos->data.mode == MODE_OPERATOR)

        if(L && R && L->data.mode == MODE_COMMAND && R->data.mode != MODE_COMMAND)
        {
            Comment_Latex(outtex);
            Print_Tree(L, outtex);
            fprintf(outtex, "\n\n");
            Print_Tree(R, outtex);
            fprintf(outtex, "\n\n");
        }

        switch(pos->data.oper)
        {
            case '+' :
                if(is_zero(L))
                {
                    pos->data = R->data;
                    L = R->left;
                    R = R->right;
                    break;
                }

                if(is_zero(R))
                {
                    pos->data = L->data;
                    R = L->right;
                    L = L->left;
                    break;
                }

                if(is_num(R) && is_num(L))
                {
                    pos->data.mode   = MODE_NUMBER;
                    pos->data.number = L->data.number + R->data.number;
                    R = nullptr;
                    L = nullptr;
                    break;
                }

            case '*' :
                if(is_zero(L) || is_zero(R))
                {
                    if(is_zero(L))
                        pos->data = L->data;
                    else
                        pos->data = R->data;

                    L = nullptr;
                    R = nullptr;
                    break;
                }

                if(is_one(L))
                {
                    pos->data = R->data;
                    L = R->left;
                    R = R->right;
                    break;
                }

                if(is_one(R))
                {
                    pos->data = L->data;
                    R = L->right;
                    L = L->left;
                    break;
                }

                if(is_num(R) && is_num(L))
                {
                    pos->data.mode   = MODE_NUMBER;
                    pos->data.number = R->data.number * L->data.number;
                    R = nullptr;
                    L = nullptr;
                    break;
                }

            case '/' :
                if(is_zero(L))
                {
                    pos->data = L->data;
                    L = nullptr;
                    R = nullptr;
                    break;
                }

                if(is_one(R))
                {
                    pos->data = L->data;
                    R = L->right;
                    L = L->left;
                    break;
                }

                if(is_num(R) && is_num(L))
                {
                    pos->data.mode   = MODE_NUMBER;
                    pos->data.number = L->data.number / R->data.number;
                    R = nullptr;
                    L = nullptr;
                    break;
                }

            case '-' :
                if(is_zero(R))
                {
                    pos->data = L->data;
                    R = L->right;
                    L = L->left;
                    break;
                }

                if(is_num(R) && is_num(L))
                {
                    pos->data.mode   = MODE_NUMBER;
                    pos->data.number = L->data.number - R->data.number;
                    R = nullptr;
                    L = nullptr;
                    break;
                }
        }
}

#undef L
#undef R

bool is_zero(tree_elem* pos)
{
    assert(pos);

    if(pos->data.mode == MODE_NUMBER && pos->data.number == 0)
        return true;
    else
        return false;
}


bool is_one(tree_elem* pos)
{
    assert(pos);

    if(pos->data.mode == MODE_NUMBER && pos->data.number == 1)
        return true;
    else
        return false;
}


bool is_num(tree_elem* pos)
{
    assert(pos);

    if(pos->data.mode == MODE_NUMBER)
        return true;
    else
        return false;
}