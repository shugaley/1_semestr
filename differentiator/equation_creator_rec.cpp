#include "diff_header.h"

tree_elem* Create_TreeEquationRec(tree* tree_eq, FILE* inp_diff)
{
    assert(tree_eq );
    assert(inp_diff);

    char* buffer = create_ar_text(inp_diff);

    assert(buffer);

    tree_eq->head = GetG(buffer);

    free(buffer);

    assert     (tree_eq );
//    assert_tree(tree_eq );
    assert     (inp_diff);

    tree_dot(tree_eq->head);

    return tree_eq->head;
}


const char* str = "";

tree_elem* GetG(const char* buffer)
{
    assert(buffer);

    str = buffer;

    tree_elem* elem = GetE();

    str++;
    assert(*str == '\0');
    str++;

    assert(buffer);
    assert(elem  );

    return elem;
}


tree_elem* GetE()
{
    tree_elem* elem1 = GetT();

    while(*str == '+' || *str == '-')
    {
        char oper = *str;

        str++;

        str = Skip_SpaceRec(str);
        tree_elem* elemR = GetT();

        tree_elem* elem2 = (tree_elem*)calloc(1, sizeof(elem2[0]));
        elem2->data.mode = MODE_OPERATOR;
        elem2->data.oper = oper;

        Swap_Elem(&elem1, &elem2);

        tree_elem* elemL  = elem2;
        tree_elem* elemOp = elem1;

        elemOp->right = elemR;
        elemR->parent = elemOp;

        elemOp->left  = elemL;
        elemL->parent = elemOp;
    }

    return elem1;
}



tree_elem* GetT()
{
    tree_elem* elem1 = GetPow();

    while(*str == '*' || *str == '/')
    {
        char oper = *str;

        str++;

        str = Skip_SpaceRec(str);
        tree_elem* elemR = GetPow();
        str = Skip_SpaceRec(str);

        tree_elem* elem2 = (tree_elem*)calloc(1, sizeof(elem2[0]));
        elem2->data.mode = MODE_OPERATOR;
        elem2->data.oper = oper;

        Swap_Elem(&elem1, &elem2);

        tree_elem* elemL  = elem2;
        tree_elem* elemOp = elem1;

        elemOp->right = elemR;
        elemR->parent = elemOp;

        elemOp->left  = elemL;
        elemL->parent = elemOp;
    }

    return elem1;
}


tree_elem* GetPow()
{
    tree_elem* elem1 = GetP();

    while(*str == '^')
    {
        char oper = *str;

        str++;

        str = Skip_SpaceRec(str);
        tree_elem* elemR = GetP();
        str = Skip_SpaceRec(str);

        tree_elem* elem2 = (tree_elem*)calloc(1, sizeof(elem2[0]));
        elem2->data.mode = MODE_OPERATOR;
        elem2->data.oper = oper;

        Swap_Elem(&elem1, &elem2);

        tree_elem* elemL  = elem2;
        tree_elem* elemOp = elem1;

        elemOp->right = elemR;
        elemR->parent = elemOp;

        elemOp->left  = elemL;
        elemL->parent = elemOp;
    }

    return elem1;
}


tree_elem* GetP()
{
    tree_elem* elem = nullptr;

    if(*str == '(')
    {
        str++;
        str = Skip_SpaceRec(str);

        elem = GetE();
        assert(*str == ')');

        str++;
        str = Skip_SpaceRec(str);
        return elem;
    }

    if(isdigit(*str))
    {
        elem = GetN();

        str = Skip_SpaceRec(str);
        return elem;
    }

    if(isalpha(*str))
    {
        if(isalpha(*(str + 1)))
            elem = GetFunc();
        else
            elem = GetId();

        str++;
        str = Skip_SpaceRec(str);
        return elem;
    }

    return elem;
}


tree_elem* GetN()
{
    tree_elem* val = (tree_elem*)calloc(1, sizeof(val[0]));

    val->data.mode = MODE_NUMBER;
    while(isdigit(*str))
    {
        val->data.number = val->data.number * 10 + (*str - '0');
        str++;
    }

    return val;
}


tree_elem* GetId()
{
    tree_elem* var = (tree_elem*)calloc(1, sizeof(var[0]));

    var->data.mode = MODE_VAR;
    if(*str == 'x')
        var->data.var = 'x';

    return var;
}


tree_elem* GetFunc()
{
    tree_elem* func = (tree_elem*)calloc(1, sizeof(func[0]));
    func->data.com = (char*)calloc(MAXSIZE_DATA, sizeof(func->data.com[0]));

    func->data.mode = MODE_COMMAND;

    int i_sym = 0;
    while(isalpha(*str))
    {
        func->data.com[i_sym++] = *str;
        str++;
    }

    str++;
    str = Skip_SpaceRec(str);
    func->right = GetE();

    return func;
}



bool Swap_Elem(tree_elem** str_1, tree_elem** str_2)
{
    assert(str_1);
    assert(str_2);

    tree_elem* temp = *str_1;
    *str_1 = *str_2;
    *str_2 = temp;

    assert(str_1);
    assert(str_2);

    return true;
}



inline const char* Skip_SpaceRec(const char* buffer)
{
    assert(buffer);

    while(*buffer && (isgraph(*buffer) == 0))
        buffer++;

    return buffer;
}
