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

    tree_dot(tree_eq->head);

    free(buffer);

    assert     (tree_eq);
    assert_tree(tree_eq);
    assert     (inp_diff );

    return tree_eq->head;
}


tree_elem* Create_TreeEquationElem(tree* tree_eq, char* buffer, size_t* i_sym, tree_elem* pos)
{
    assert(tree_eq);
    assert(buffer );

    if(*i_sym == 0)
        pos =  Create_TreeEquationHead(tree_eq, buffer, i_sym);

    *i_sym = Skip_Space(buffer, *i_sym);

    if(!buffer[*i_sym] || buffer[*i_sym] == '\n')
        return pos;

    data_t new_elem = Create_TreeEquationNewElem(buffer, i_sym);

    if(new_elem.mode == MODE_OPERATOR)
    {
        switch(new_elem.oper)
        {
            case ')':
                //(*i_sym)++;
                *i_sym = Skip_Space(buffer, *i_sym);
                pos = pos->parent;
                Create_TreeEquationElem(tree_eq, buffer, i_sym, pos);

            case '(':
                new_elem.oper = '$';
                break;

            case '$':
                break;

            default:
                //(*i_sym)++;
                *i_sym = Skip_Space(buffer, *i_sym);
                //pos = pos->parent;
                pos->data = new_elem;
                Create_TreeEquationElem(tree_eq, buffer, i_sym, pos);
        }
    }

    if((new_elem.mode == MODE_VAR || new_elem.mode == MODE_NUMBER) && pos->parent)
            pos = pos->parent;

    if(!pos) return pos;

    if      (!pos->left || (pos->left->data.oper == '$' && pos->data.mode != MODE_COMMAND))
    {

        pos->left  = Add_TreeElem(tree_eq, new_elem, 'L', pos);
        pos = pos->left;

        if(new_elem.mode == MODE_COMMAND)
            Create_TreeDiffElem$(tree_eq, new_elem, pos);

        Create_TreeEquationElem(tree_eq, buffer, i_sym, pos);
    }

    else if (!pos->right || pos->right->data.oper == '$')
    {
        pos->right = Add_TreeElem(tree_eq, new_elem, 'R', pos);
        pos = pos->right;

        if(new_elem.mode == MODE_COMMAND)
            Create_TreeDiffElem$(tree_eq, new_elem, pos);

        Create_TreeEquationElem(tree_eq, buffer, i_sym, pos);
    }

    return pos;
}



tree_elem* Create_TreeEquationHead(tree* tree_eq, char* buffer, size_t* i_sym)
{
    assert     (tree_eq);
    assert     (buffer );
    assert     (i_sym  );

    Create_Tree(tree_eq);

    (*i_sym) = Skip_Space(buffer, *i_sym);

    data_t new_elem = Create_TreeEquationNewElem(buffer, i_sym);

    if(new_elem.oper == '(')
        new_elem.oper = '$';

    tree_elem* pos = Add_TreeElem(tree_eq, new_elem, 'L', tree_eq->head);

    assert     (tree_eq);
    assert_tree(tree_eq);
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
    size_t n = 0;

    if (isdigit(buffer[*i_sym]))
    {
        sscanf(&buffer[*i_sym], "%d%n", &new_elem.number, &n);
        (*i_sym) += n;
        new_elem.mode = MODE_NUMBER;
        return new_elem;
    }

    if (isalpha(buffer[*i_sym]))
    {
        if (buffer[*i_sym] == 'x')
        {
            sscanf(&buffer[*i_sym], "%c", &new_elem.var);
            (*i_sym)++;
            new_elem.mode = MODE_VAR;
            return new_elem;
        }

        else
        {
            new_elem.com = (char*)calloc(MAXSIZE_DATA, sizeof(new_elem.com[0]));
            sscanf(&buffer[*i_sym], "%[a-z]%n", new_elem.com, &n);
            (*i_sym) += n;
            new_elem.mode = MODE_COMMAND;
            return new_elem;
        }
    }

    else //if (isalpha(buffer[*i_sym]))
    {
        sscanf(&buffer[*i_sym], "%c", &new_elem.oper);
        (*i_sym)++;
        new_elem.mode = MODE_OPERATOR;
        return new_elem;
    }

    return new_elem;
}


void Create_TreeDiffElem$(tree* tree_eq, tree_data new_elem, tree_elem* pos)
{
    assert(tree_eq);
    assert(pos);

    new_elem.mode = MODE_OPERATOR;
    new_elem.oper = '@';
    Add_TreeElem(tree_eq, new_elem, 'L', pos);
}


inline size_t Skip_Space(char* buffer, size_t i_sym)
{
    assert(buffer);

    while(buffer[i_sym] && (isgraph(buffer[i_sym]) == 0))
        (i_sym)++;

    assert(buffer);

    return i_sym;
}