#include "akinator_header.h"

bool Read_TreeAkinator(tree* tree_ak, FILE* inp_ak)
{
    assert(tree_ak);
    assert(inp_ak );

    char* buffer = create_ar_text(inp_ak);

    assert(buffer);

    size_t i_sym = 0;
    tree_elem* pos = nullptr;
    Create_TreeAkinatorElem(tree_ak, buffer, &i_sym, pos);

    free(buffer);

    assert     (tree_ak);
    assert_tree(tree_ak);
    assert     (inp_ak );

    return true;
}

//----------------------------
#define ERROR_ANSWER printf("Error answer"); abort();

tree_elem* Ask_Questions(tree* tree_ak)
{
    assert     (tree_ak);
    assert_tree(tree_ak);

    tree_elem* pos = tree_ak->head;

    for(;;)
    {
        if (!pos->right && !pos->left)
            return Answer_LastQuestion(tree_ak, pos);

        char ans = *Dialogue("%s\nда [y] / нет [n]", pos->data);

        /*printf("%s\n", pos->data);
        printf("да [y] / нет [n]\n");
        scan(ans);*/

        switch(ans)
        {
            case 'y':
                pos = pos->left;
                break;
            case 'n':
                pos = pos->right;
                break;
            default:
                ERROR_ANSWER;
        }
    }
}

tree_elem* Answer_LastQuestion(tree* tree_ak, tree_elem* pos)
{
    assert     (tree_ak);
    assert_tree(tree_ak);
    assert     (pos    );

    char ans = *Dialogue("Это %s?\nда [y] / нет [n]", pos->data);

    switch(ans)
    {
        case 'y':
            printf("Хех\n");
            return pos;

        case 'n':
            printf("Ух\n");
            return Answer_NewElemQuestion(tree_ak, pos);

        default:
            ERROR_ANSWER;
    }
}


tree_elem* Answer_NewElemQuestion(tree* tree_ak, tree_elem* pos)
{
    assert     (tree_ak);
    assert_tree(tree_ak);
    assert     (pos    );

    char ans = *Dialogue("Имеете желание добавить свой ответ?\nда [y] / нет [n]");

    switch(ans)
    {
        case 'y':
            printf("OK. Let's do it\n");
            return Add_TreeAkinatorElem(tree_ak, pos);

        case 'n':
            printf("It's your wish\n");
            return pos;

        default:
            ERROR_ANSWER;
    }
}

#undef ERROR_ANSWER

//----------------

tree_elem* Add_TreeAkinatorElem(tree* tree_ak, tree_elem* pos)
{
    assert     (tree_ak);
    assert_tree(tree_ak);
    assert     (pos    );

    char* new_ans = strdup(Dialogue("Что вы хотите вставить?\n"));

    if (Search_TreeAkinatorAnswer(tree_ak, new_ans))
    {
        printf("Вы даун. Он уже существует");
        free(new_ans);
        return pos;
    }

    char* new_quest = strdup(Dialogue("Чем отличается %s и %s?\n", new_ans, pos->data));  // vprintf
    strcat(new_quest, "?");

    Add_TreeElem(tree_ak, new_ans,   'L', pos);
    Add_TreeElem(tree_ak, new_quest, 'R', pos);

    Swap_Str(&pos->data, &pos->right->data);

    pos = pos->left;

    return pos;
}


tree_elem* Search_TreeAkinatorAnswer(tree* tree_ak, char* string)
{
    assert(string);

    return Search_TreeElem(tree_ak->head, string);
}

bool Swap_Str(char** str_1, char** str_2)
{
    assert(str_1);
    assert(str_2);

    char* temp = *str_1;
    *str_1 = *str_2;
    *str_2 = temp;

    assert(str_1);
    assert(str_2);

    return true;
}

//-----------------------


bool Print_WayAnswer(tree* tree_ak, char* ans)
{
    assert     (tree_ak);
    assert_tree(tree_ak);
    assert     (ans    );

    tree_elem* pos = Search_TreeAkinatorAnswer(tree_ak, ans);
    tree_elem* pos_ans = pos;

    size_t size_way = 0;
    tree_elem** way = Create_WayAnswer(pos, tree_ak->size, &size_way);

    printf("%s это: ", pos_ans->data);

    size_t i_way = size_way;
    Output_WayAnswer(way, i_way);

    return true;
}


bool Print_WayTwoAnswer(tree* tree_ak, char* ans_1, char* ans_2)
{
    assert     (tree_ak);
    assert_tree(tree_ak);
    assert     (ans_1  );
    assert     (ans_2  );

    tree_elem* pos_1 = Search_TreeAkinatorAnswer(tree_ak, ans_1);
    tree_elem* pos_2 = Search_TreeAkinatorAnswer(tree_ak, ans_2);

    tree_elem* pos_ans_1 = pos_1;
    tree_elem* pos_ans_2 = pos_2;

    size_t size_way_1 = 0;
    size_t size_way_2 = 0;

    tree_elem** way_1 = Create_WayAnswer(pos_1, tree_ak->size, &size_way_1);
    tree_elem** way_2 = Create_WayAnswer(pos_2, tree_ak->size, &size_way_2);

    size_t i_way_1 = size_way_1;
    size_t i_way_2 = size_way_2;

    printf("Между %s и %s общее то, что они : ", pos_ans_1->data, pos_ans_2->data);
    while( !strcmp(way_1[i_way_1 - 1]->data, way_2[i_way_2 - 1]->data) )
        if(i_way_1 > 0 && i_way_2 > 0)
        {
            if(way_1[i_way_1 - 1] == way_1[i_way_1]->right)
            printf("Не ");

            Print_CharactAnswer(way_1[i_way_1]->data);
            printf(", ");

            i_way_1--;
            i_way_2--;

            printf(" ");
        }

    if(i_way_1 > 0)
    {
        printf("\nНо %s в отличие от этого : ", pos_ans_1->data);
        Output_WayAnswer(way_1, i_way_1);
    }

    if(i_way_2 > 0)
    {
        printf("\nА %s в свою очередь : ", pos_ans_2->data);
        Output_WayAnswer(way_2, i_way_2);
    }

    return true;
}


inline tree_elem** Create_WayAnswer(tree_elem* pos, size_t maxsize_way, size_t* size_way)
{
    assert(pos     );
    assert(size_way);  //

    tree_elem** way = (tree_elem**)calloc(maxsize_way, sizeof(way[0]));

    while(pos)
    {
        way[(*size_way)++] = pos;
        pos = pos->parent;
    }

    (*size_way)--;

    return way;
}


inline bool Output_WayAnswer(tree_elem** way, size_t i_way)
{
    assert(way);

    while(i_way > 0)
    {
        if(way[i_way - 1] == way[i_way]->right)
            printf("Не ");

        Print_CharactAnswer(way[i_way--]->data);

        if(i_way == 0)
            printf(". ");
        else
            printf(", ");
    }

    return true;
}


inline bool Print_CharactAnswer(char* charact)
{
    assert(charact);

    size_t i_sym = 0;
    while( charact[i_sym + 1] )
        printf("%c", charact[i_sym++]);

    return true;
}

//---------------------------------

char* Dialogue(const char* fstr, ...)
{
    static char ans[MAXSIZE_DATA] = {};

    va_list strs;

    va_start(strs, fstr);
    vprintf (fstr, strs);
    va_end(strs);

    scanf("\n%[^\n]", ans);

    return ans;
}
