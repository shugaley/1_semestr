#include "header_asm.h"

const char* TEXT_OUTPUT = "/home/shugaley/proga/projects/1_sem/processor/assembler/Output_File";
const char* TEXT_INPUT = "/home/shugaley/proga/projects/1_sem/processor/assembler/Input_File";

int main()
{
    FILE* ptr_input = fopen(TEXT_INPUT, "r");
    struct LINE* lines_text = create_all(ptr_input);
    fclose(ptr_input);

    char* bytecode = (char*)calloc(sizeof(lines_text) * 5, sizeof(bytecode[0]));

    int pc = assembler(lines_text, bytecode);

    FILE* ptr_output = fopen(TEXT_OUTPUT, "wb");
    fwrite(bytecode, sizeof(bytecode[0]), pc, ptr_output);
    fclose(ptr_output);

    free(lines_text);
    free(bytecode);

    return 0;
}
