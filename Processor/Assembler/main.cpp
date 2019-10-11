#define _CRT_SECURE_NO_WARNINGS

#include "assembler.cpp"

int main()
{
    size_t nlines = 0;
    struct LINE* lines_text = create_all(&nlines);

    char* bytecode = (char*)calloc(nlines * 2, sizeof(bytecode[0]));

    int pc = assembler(lines_text, nlines, bytecode);

    FILE* ptr_output = fopen(TEXT_OUTPUT, "wb");
    fwrite(bytecode, sizeof(bytecode[0]), pc, ptr_output);
    fclose(ptr_output);

    free(lines_text);
    free(bytecode);

    return 0;
}
