#include "header_cpu.h"

const char* TEXT_INPUT = "/home/shugaley/proga/projects/1_sem/processor/assembler/Output_File";
const int SIZE_OF_REGISTER = 4;

int main()
{
    FILE* ptr_input = fopen(TEXT_INPUT, "rb");
    char* bytecode = create_ar_text(ptr_input);
    fclose(ptr_input);

    CPU processor = {};
    processor.registers = (int*) calloc(SIZE_OF_REGISTER, sizeof(processor.registers[0]));

    printf("Answer is %d", main_CPU(bytecode, &processor));

    free(processor.registers);

    return 0;
}
