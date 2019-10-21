#include "header_cpu.h"

bool main_CPU(char* bytecode, CPU* processor)
{
    assert(bytecode);
    assert(processor);

    int pc = 0;
    while(bytecode[pc] != 90)
    {

        WhichCommandCPU (bytecode[pc]);

        WhichCommandRegCPU (bytecode[pc]);

    }
}


void WhichCommandCPU (char bytecode)
{
    switch(bytecode[pc])
    {
        #define  DEF_CMD(name, num, code) \
        {\
            case num: \
                code; \
                break; \
        }

        #define NON_REG_MOD

        #include "commands.h"

        #undef DEF_CMD
    }
}


void WhichCommandRegCPU (char bytecode)
{
    switch(bytecode[pc])
    {
        #define  DEF_CMDR(name, num, code) \
        {\
            case num: \
                code; \
                break; \
        }

        #define REG_MOD

        #include "commands.h"

        #undef DEF_CMD
    }
}
