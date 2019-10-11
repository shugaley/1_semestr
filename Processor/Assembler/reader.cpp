#include "Header.h"

struct LINE* create_all(size_t* nlines);

char* create_ar_text(FILE* pnt_input, size_t* size);
struct LINE* create_struct_lines(char* text, size_t nlines, size_t size);

size_t count_size();
size_t count_symbol(char* text, size_t size, char symbol);

struct LINE
{
    int length;
    char* ptrline;
};




struct LINE* create_all(size_t* nlines)
{

    FILE* ptr_input = fopen(TEXT_INPUT, "r");

    size_t size = count_size();

    char* text = create_ar_text(ptr_input, &size);

    fclose(ptr_input);

    *nlines = count_symbol(text, size, '\n');

    struct LINE* lines = create_struct_lines(text, *nlines, size);

    return lines;
}


char* create_ar_text(FILE* ptr_input, size_t* size)
{

    assert(ptr_input != 0);

    char* text = (char*)calloc(*size + 1, sizeof(text[0]));
    *size = fread(text, sizeof(text[0]), *size, ptr_input) + 1;
    text = (char*)realloc(text, *size + 1);

    return text;
}



struct LINE* create_struct_lines(char* text, size_t nlines, size_t size)
{

    assert(text != NULL);

    if (nlines == 0)
        nlines = count_symbol(text, size, '\n');


    struct LINE* lines = (struct LINE*)calloc(nlines + 1, sizeof(lines[0]));

    int line = 0, i = 0;

    lines[line].ptrline = &text[i];

    for (line = 1; line < nlines; line++)								   //line - ñ÷åò÷èê ñòðîê
    {

        while (text[i] && text[i] != '\n')
            i++;

        text[i] = '\0';
        i++;

        lines[line].ptrline = &text[i];
        lines[line - 1].length = (int) (lines[line].ptrline - lines[line - 1].ptrline);
    }

    text[i] = '\0';

    return lines;
}



size_t count_size()
{
    struct stat struct_text = {};
    if (stat(TEXT_INPUT, &struct_text))
    {
        perror("Failure structure of file creation");
        abort();
    }

    size_t size = struct_text.st_size;

    return size;
}



size_t count_symbol(char* text, size_t size, char symbol)
{

    assert(text != NULL);

    int nlines = 0;

    int i = 0;
    for (i; i < size; i++)									//i - счетчик символов
        if (!text[i] || text[i] == symbol)
            nlines++;

    return (text[i - 1] != symbol) ? nlines : ++nlines;
}
