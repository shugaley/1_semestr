#include "diff_header.h"

tree_elem* Create_TreeEquation(tree* tree_eq, FILE* inp_diff)
{
    assert(tree_eq  );
    assert(inp_diff );

    char* buffer = create_ar_text(inp_diff);

    assert(buffer);

    size_t i_sym = 0;
    tree_elem* pos = nullptr;
    Create_TreeEquationElem(tree_eq, buffer, &i_sym, pos);

    free(buffer);

    assert     (tree_eq);
    assert_tree(tree_eq);
    assert     (inp_diff );
}


tree_elem* Create_TreeEquationElem(tree* tree_eq, char* buffer, size_t* i_sym, tree_elem* pos)
{
    assert(tree_eq);
    assert(buffer   );

    if(*i_sym == 0)
        pos =  Create_TreeEquationHead(tree_eq, buffer, i_sym);

    *i_sym = Skip_Space(buffer, *i_sym);

    if(buffer[*i_sym] == '{')
    {
        (*i_sym)++;
         *i_sym = Skip_Space(buffer, *i_sym);
        char* string = Create_String(buffer, i_sym);

        if      (!pos->left )
        {
            pos->left  = Add_TreeElem(tree_eq, string, 'L', pos);
            pos = pos->left;
            Create_TreeEquationElem(tree_eq, buffer, i_sym, pos);
        }

        else if (!pos->right)
        {
            pos->right = Add_TreeElem(tree_eq, string, 'R', pos);
            pos = pos->right;
            Create_TreeEquationElem(tree_eq, buffer, i_sym, pos);
        }
    }

    if(buffer[*i_sym] == '}')
    {
        (*i_sym)++;
         *i_sym = Skip_Space(buffer, *i_sym);
        pos = pos->parent;
        Create_TreeEquationElem(tree_eq, buffer, i_sym, pos);
    }
}



tree_elem* Create_TreeEquationHead(tree* tree_ak, char* buffer, size_t* i_sym)
{
    assert     (tree_ak);
    assert     (buffer );
    assert     (i_sym  );

    Create_Tree(tree_ak);

    (*i_sym) = Skip_Space(buffer, *i_sym);

    data_t new_elem = Create_TreeEquationNewElem(buffer, i_sym);
    tree_elem* pos = Add_TreeElem(tree_ak, new_elem, 'L', tree_ak->head);

    assert     (tree_ak);
    assert_tree(tree_ak);
    assert     (buffer );
    assert     (i_sym  );
    assert     (pos    );

    return pos;
}



data_t Create_TreeEquationNewElem(char* buffer, size_t* i_sym)
{
    assert(buffer);
    assert(i_sym );

    data_t new_elem = {};

    switch(Which_Elem(buffer, i_sym, &data))
    {
        case TYPE_NUMBER   : return nullptr;

        case TYPE_VAR      : return nullptr;

        case TYPE_OPERATOR
        {
            switch(data)
            {
                case '+' : ;
                case '*' : ;
            }
        }

        case TYPE_COMMAND :
        {
            switch(data)
            {
            }
        }

        default: fprintf(stderr, "Error Create_TreeDiffElem %zu", i_sym);
    }
}




int Which_Elem(char* buffer, size_t* i_sym, data_t* new_data)
{
    assert(buffer);
    assert(i_sym );

    if(isdigit())



inline size_t Skip_Space(char* buffer, size_t i_sym)
{
    assert(buffer);

    while(buffer[i_sym] && (isgraph(buffer[i_sym]) == 0))
        (i_sym)++;

    assert(buffer);

    return i_sym;
}



  /*while(buffer[*i_sym])
    {
        (*i_sym) = Skip_Space(buffer, *i_sym);

        int data = 0;
        switch(Which_Elem(buffer, i_sym, &data))
        {
            case TYPE_NUMBER   : return nullptr;

            case TYPE_VAR      : return nullptr;

            case TYPE_OPERATOR :
            {
                switch(data)
                {
                    case '+' : ;
                    case '*' : ;
                }
            }

            case TYPE_COMMAND :
            {
                switch(data)
                {
                }
            }

            default: fprintf(stderr, "Error Create_TreeDiffElem %zu", i_sym);
        }
    }*/
