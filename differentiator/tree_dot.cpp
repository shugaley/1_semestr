#include "diff_header.h"

void print_mode(tree_elem* pos, FILE* dot_out)
{
    assert(pos);
    assert(dot_out);

    switch ((pos->data).mode)
    {
        case MODE_COMMAND:     fprintf(dot_out, "[label = \"%s\", shape = \"ellipse\", "
                                           "color=\"#006400\", style=\"filled\", "
                                           "fillcolor = \"#32CD32\"]", (pos->data).com);
                          break;

        case MODE_OPERATOR:   fprintf(dot_out, "[label = \"%c\", shape = \"ellipse\", "
                                           "color=\"#FFD700\", style=\"filled\", "
                                           "fillcolor = \"#F0E68C\"]", (pos->data).oper);
                          break;

        case MODE_VAR:    fprintf(dot_out, "[label = \"%c\", shape = \"ellipse\", "
                                           "color=\"#8B008B\", style=\"filled\", "
                                           "fillcolor = \"#9932CC\"]", (pos->data).var);
                          break;

        case MODE_NUMBER: fprintf(dot_out, "[label = \"%d\", shape = \"ellipse\", "
                                           "color=\"#8B0000\", style=\"filled\", "
                                           "fillcolor = \"#FFA07A\"]", (pos->data).number);
                          break;

        default:          fprintf(dot_out, "\"error\"");
                          break;
    }

    assert(pos);
    assert(dot_out);
}


int tmp = 0;
void create_tree(tree_elem* pos, FILE* dot_out)
{
    assert(dot_out);
    assert(pos);

    fprintf(dot_out, "\t\they%d", tmp);
    print_mode(pos, dot_out);
    fprintf(dot_out, ";\n");

    int iskan = tmp;

    if (pos->left != nullptr) {
        fprintf(dot_out, "\t\they%d", iskan);

        fprintf(dot_out, "->");

        fprintf(dot_out, "hey%d;\n", ++tmp);

        create_tree(pos->left, dot_out);
    }

    if (pos->right != nullptr) {
        fprintf(dot_out, "\t\they%d", iskan);

        fprintf(dot_out, "->");

        fprintf(dot_out, "hey%d;\n", ++tmp);

        create_tree(pos->right, dot_out);
    }

    assert(pos);
    assert(dot_out);
}

void tree_dot(tree_elem* nameTree)
{

    FILE *file_dot = fopen(DOT, "wb");
    assert(file_dot);

    fprintf(file_dot, "digraph {\n");
    fprintf(file_dot, "\tnode[color = \"#000000\", fontsize = 20];\n"
                      "\tedge[color = \"#000000\", fontsize = 20];\n");

    create_tree(nameTree, file_dot);

    fprintf(file_dot, "}");

    assert(file_dot);
    fclose(file_dot);

    system("dot -Tjpg -o /home/shugaley/proga/projects/1_sem/differentiator/tree.jpg"
           " /home/shugaley/proga/projects/1_sem/differentiator/dot_out.dot");

}