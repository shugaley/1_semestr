#include "diff_header.h"

FILE* outtex = fopen(FILE_OUT_TEX, "wb");

int main()
{
    FILE* diff_input = fopen(FILE_INP_INORDER, "r");
    tree tree_eq = {};
    Create_TreeEquationRec(&tree_eq, diff_input);
    tree_dot(tree_eq.head);
    fclose(diff_input);

    Latex_begin(outtex);
    Latex(&tree_eq, outtex);

    tree tree_diff = Differentiate(&tree_eq);
    tree_dot(tree_diff.head);
    Latex(&tree_diff, outtex);

    Simplify_tree(tree_diff.head);
    tree_dot(tree_diff.head);
    Latex(&tree_diff, outtex);

    Latex_end(outtex);

    return 0;
}