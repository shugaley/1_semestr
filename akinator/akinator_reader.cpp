#include "akinator_header.h"

char* create_ar_text(FILE* ptr_input)
{

    assert(ptr_input);

    size_t size = count_size();
    char* text = (char*)calloc(size + 1, sizeof(text[0]));
    size = fread(text, sizeof(text[0]), size, ptr_input) + 1;
    text = (char*)realloc(text, size + 1);

    return text;
}


size_t count_size()
{
    struct stat struct_text = {};
    if (stat(FILE_INP, &struct_text))
    {
        perror("Failure structure of file creation");
        abort();
    }

    size_t size = struct_text.st_size;

    return size;
}
