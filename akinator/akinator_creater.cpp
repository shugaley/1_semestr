#include "akinator_header.h"

tree_elem* Create_TreeAkinatorElem(tree* tree_ak, char* buffer, size_t* i_sym, tree_elem* pos)
{
    assert(buffer);
    assert(i_sym);

    if(*i_sym == 0)
        pos =  Create_TreeAkinatorHead(tree_ak, buffer, i_sym);

    *i_sym = Skip_Space(buffer, *i_sym);

    if(buffer[*i_sym] == '{')
    {
        (*i_sym)++;
         *i_sym = Skip_Space(buffer, *i_sym);
        char* string = Create_String(buffer, i_sym);

        if      (!pos->left )
        {
            pos->left  = Add_TreeElem(tree_ak, string, 'L', pos);
            pos = pos->left;
            Create_TreeAkinatorElem(tree_ak, buffer, i_sym, pos);
        }

        else if (!pos->right)
        {
            pos->right = Add_TreeElem(tree_ak, string, 'R', pos);
            pos = pos->right;
            Create_TreeAkinatorElem(tree_ak, buffer, i_sym, pos);
        }
    }

    if(buffer[*i_sym] == '}')
    {
        (*i_sym)++;
         *i_sym = Skip_Space(buffer, *i_sym);
        pos = pos->parent;
        Create_TreeAkinatorElem(tree_ak, buffer, i_sym, pos);
    }

    return pos;
}


tree_elem* Create_TreeAkinatorHead(tree* tree_ak, char* buffer, size_t* i_sym)
{
    assert     (tree_ak);
    assert     (buffer );
    assert     (i_sym  );

    Create_Tree(tree_ak);

    while(buffer[*i_sym] != '"')
        (*i_sym)++;

    char* string = Create_String(buffer, i_sym);
    tree_elem* pos = Add_TreeElem(tree_ak, string, 'L', tree_ak->head);

    assert     (tree_ak);
    assert_tree(tree_ak);
    assert     (buffer );
    assert     (i_sym  );
    assert     (string );
    assert     (pos    );

    return pos;
}


char* Create_String(char* buffer, size_t* i_sym)
{
    assert(buffer);
    assert(i_sym );

    char* string = (char*)calloc(MAXSIZE_DATA, sizeof(string[0]));

    size_t n = 0;
    /*for(size_t i = 0; i < *i_sym; i++)
        fprintf(stderr, "%c", buffer[i]);
    fprintf(stderr, "    %zu\n", *i_sym);*/
    sscanf(buffer + *i_sym, "\"%[^\"]\"%n", string, &n);

    *i_sym += n;

    return string;
}


inline size_t Skip_Space(char* buffer, size_t i_sym)
{
    assert(buffer);

    while(buffer[i_sym] && (isgraph(buffer[i_sym]) == 0))
        (i_sym)++;

    assert(buffer);

    return i_sym;
}
