#ifndef ASSEMBLER_DSL_H
#define ASSEMBLER_DSL_H

#define DPUSH(value) StackPush(&processor->stk_CPU, value)

#define DPOP StackPop(&processor->stk_CPU)

#define PC(what) \
{\
    if((what) == 'c')\
        pc += sizeof(char);\
    if((what) == 'i')\
        pc += sizeof(int);\
}

#define WHICH_REG(pc) processor.registers[bytecode[pc] - 'a']



#endif //ASSEMBLER_DSL_H
