#include "tree_header.h"


void Akinator_Dot (tree* tree_name)
{
    assert(tree_name);

    FILE *file_dot = fopen("/home/shugaley/proga/projects/1_sem/akinator/dot_out", "w");
    assert(file_dot);

    fprintf(file_dot, "digraph {\n");
    fprintf(file_dot, "\tnode[shape = \"octagon\", color = \"#191970\", fontsize = 12, "
                      "style = \"filled\", fillcolor = \"#87CEFA\"];\n"
                      "\tedge[color = \"#191970\", fontsize = 14];\n");

    Create_Tree_Dot (tree_name->head, file_dot);

    fprintf(file_dot, "}");

    assert(file_dot);
    fclose(file_dot);

    system("dot -Tjpg -o /home/shugaley/proga/projects/1_sem/akinator/tree.jpg "
           "/home/shugaley/proga/projects/1_sem/akinator/dot_out");
}

void Create_Tree_Dot (tree_elem* pos, FILE* file_dot)
{
    if (pos->left != nullptr) {
        fprintf (file_dot, "\n\t\t\"%s\"[shape = \"ellipse\", color=\"#191970\", "
                           "style=\"filled\", fillcolor = \"#E0FFFF\"];\n"
                          "\t\t\"%s\"->\"%s\"[label = \"Yes\"];\n", pos->data, pos->data, (pos->left)->data);

        Create_Tree_Dot (pos->left, file_dot);
    }

    if (pos->right != nullptr) {
        fprintf (file_dot, "\n\t\t\"%s\"[shape = \"egg\", color=\"#191970\", "
                           "style=\"filled\", fillcolor = \"#E0FFFF\"];\n"
                          "\t\t\"%s\"->\"%s\"[label = \"No\"];\n", pos->data, pos->data, (pos->right)->data);

        Create_Tree_Dot (pos->right, file_dot);
    }
}
