#include "diff_header.h"

void Latex(tree* tree_name)
{
    assert(tree_name);

    FILE* outtex = fopen(FILE_OUT_TEX, "wb");

    fprintf(outtex, "\\documentclass{article}\n"
                    "\n"
                    "\\title{diff}\n"
                    "\n"
                    "\\author{I}\n"
                    "\n"
                    "\\begin{document}\n"
                    "\n\n\n"
                    "\\maketitle\n"
                    "$");

    Comment_Latex(outtex);

    Print_Tree(tree_name->head, outtex);

    fprintf(outtex, "$\n"
                    "\n"
                    "\\end{document}");

    assert(outtex);
    fclose(outtex);
}


void Print_Tree(tree_elem* pos, FILE* out)
{
    if(!pos) return;

    if (pos->data.mode == MODE_OPERATOR)
        switch(pos->data.oper)
        {
            case '*':
                Print_TreeMul(pos->left , out);
                Print_TreeMul(pos->right, out);

                return;

            case '/':
                fprintf(out, "\\frac{");
                Print_Tree(pos->left, out);

                fprintf(out, "}{");

                Print_Tree(pos->right, out);
                fprintf(out, "}");

                return;

            case '^':
                if(is_end(pos->left)) Print_Tree(pos->left, out);

                else
                {
                    fprintf(out, "(");
                    Print_Tree(pos->left, out);
                    fprintf(out, ")");
                }

                fprintf(out, "^{");
                Print_Tree(pos->right, out);
                fprintf(out, "}");

                return;

            default:
                break;
        }

    //if(!is_$(pos->left))
    Print_Tree(pos->left, out);

    switch(pos->data.mode)
    {
        case MODE_NUMBER   : fprintf(out, "%d", pos->data.number); break;

        case MODE_VAR      : fprintf(out, "%c", pos->data.var   ); break;

        case MODE_OPERATOR : //if(!is_$(pos))
                             fprintf(out, "%c", pos->data.oper  ); break;

        case MODE_COMMAND  :

            if(is_end(pos->right)) fprintf(out, "\\%s", pos->data.com);

            else
            {
                fprintf(out, "\\%s", pos->data.com);
                fprintf(out, "(");
                Print_Tree(pos->right, out);
                fprintf(out, ")");
            }

            return;

        default:
            printf("Error mode %d", pos->data.mode);
            abort();
    }

    Print_Tree(pos->right, out);
}



void Print_TreeMul(tree_elem* pos, FILE* out)
{
    assert(pos);
    assert(out);

    if(is_end(pos)) Print_Tree(pos, out);

    else if (is_high_priority(pos)) Print_Tree(pos, out);

    else
    {
        fprintf(out, "(");
        Print_Tree(pos, out);
        fprintf(out, ")");
    }
}



void Comment_Latex(FILE* out)
{
    assert(out);

    const char* comment[5];
    comment[0] = "Yasno:";
    comment[1] = "Ponatno:";
    comment[2] = "Otsyda sledyet:";
    comment[3] = "Nyjno bolshe proizvodnax:";
    comment[4] = "Smotrite kak ymey:";

    fprintf(out, "%s\n", comment[rand() % 5]);
    fprintf(out, "\n\n");
}




bool is_end(tree_elem* pos)
{
    assert(pos);

    if(is_$(pos) || (!pos->left && !pos->right))
        return true;
    else
        return false;
}



bool is_$(tree_elem* pos)
{
    assert(pos);

    if(pos->data.oper == '$')
        return true;
    else
        return false;
}



bool is_high_priority(tree_elem* pos)
{
    assert(pos);

    if((pos->data.mode == MODE_OPERATOR && (pos->data.oper == '*' ||
                                           pos->data.oper == '/'  ||
                                           pos->data.oper == '^'    )) ||
        pos->data.mode == MODE_COMMAND)
        return true;
    else
        return false;
}
