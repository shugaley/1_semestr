#include "diff_header.h"

extern FILE* outtex;

tree Differentiate(tree* tree_eq)
{
    assert(tree_eq);

    tree tree_diff = {};
    tree_diff.head = Create_TreeDiffElem(tree_eq->head);

    assert     (tree_eq);
//  assert_tree(tree_eq);

    return tree_diff;
}



tree_elem* Create_TreeDiffElem(tree_elem* pos)
{
    assert(pos);

    int num_com = 0;
    tree_elem* pos_temp = nullptr;
    switch(pos->data.mode)
    {
        case MODE_NUMBER  : return ADD(NUM);

        case MODE_VAR     : return ADD(VAR);

        case MODE_OPERATOR:

            switch(pos->data.oper)
            {
                case '+' : return PLUS(dL, dR);

                case '-' : return SUB (dL, dR);

                case '*' : return PLUS( MUL(dL, cR), MUL(cL, dR) );

                case '/' : return DIV (SUB (MUL(dL, cR), MUL(cL, dR)),  MUL(cR, cR) );

                case '^' : return MUL (cR, POW (cL, SUB(cR, ADD_NUM(1))) );

                default  : printf("Error operator %c", pos->data.oper); abort();
            }

        case MODE_COMMAND :

            num_com = Which_com(pos->data.com);

            switch(num_com)
            {
                #define DEF_COM(com, num, code) {case num: {code}; break;}

                #include "commands.h"

                #undef DEF_COM

                default: printf ("Error command %s", pos->data.com); abort();
            }

        default: printf ("Error mode %d", pos->data.mode); abort();
    }

}



tree_elem* Add_TreeDiffElem(tree_data new_data, tree_elem* pos_left, tree_elem* pos_right)
{
    tree_elem* new_elem = (tree_elem*)calloc(1, sizeof(new_elem[0]));

    new_elem->data = new_data;

    new_elem->right = pos_right;
    new_elem->left  = pos_left;

    if(pos_right)
        pos_right->parent = new_elem;
    if(pos_left)
        pos_left->parent = new_elem;

    return new_elem;
}



tree_data Create_TreeDiffNewData(int mode, int num_value, char* str_value)
{
    tree_data new_data = {};

    switch(mode)
    {
        case MODE_NUMBER   :
            new_data.mode   = MODE_NUMBER;
            new_data.number = num_value;
            break;

        case MODE_VAR      :
            new_data.mode   = MODE_NUMBER;   // !!! MODE_VAR
            new_data.number = num_value;
            break;

        case MODE_OPERATOR :
            new_data.mode = MODE_OPERATOR;
            new_data.oper = (char)num_value;
            break;

        case MODE_COMMAND :
            new_data.mode = MODE_COMMAND;
            new_data.com  = str_value;
            break;

        default:
            printf("Error mode %d", mode);
            abort();
    }

    return new_data;
}



int Which_com(char* com_name)
{
    #define DEF_COM(com, num, code) {if (!strcmp(com_name, #com)) return num;}

    #include "commands.h"

    #undef DEF_COM
}



tree_elem* Copy(tree_elem* pos)
{
    assert(pos);

    tree_elem* copy_elem = (tree_elem*)calloc(1, sizeof(copy_elem[0]));

    if (pos->data.mode == MODE_COMMAND)
    {
        copy_elem->data.mode = pos->data.mode;
        copy_elem->data.com  = strdup(pos->data.com);
    }

    else
        copy_elem->data = pos->data;

    if(pos->right) copy_elem->right = cR;

    if(pos->left)  copy_elem->left  = cL;

    return copy_elem;
}



