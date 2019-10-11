#define _CRT_SECURE_NO_WARNINGS

#include "Reader.cpp"

int assembler(struct LINE* lines_text, size_t nlines, char* bytecode);

char WhichCommand(char* str_command);
char WhichCommandReg(char* str_command);

bool DeleteComm(struct LINE* lines_text, int nlines);

int FindParams(struct LINE lines_text, char* param);




int assembler(struct LINE* lines_text, size_t nlines, char* bytecode)
{
    assert(bytecode);

    int pc = 0;
    char* str_command = (char*)calloc(4, sizeof(str_command[0]));

    for(size_t i_line = 0; bytecode[pc] != 90; i_line++)
    {
        sscanf(lines_text[i_line].ptrline, "%s", str_command);

        char* param = (char*)calloc(lines_text[i_line].length, sizeof(param[0]));

        if (FindParams(lines_text[i_line], param) < 0)
            bytecode[pc++] = WhichCommandReg(str_command);

        else
        {
            bytecode[pc++] = WhichCommand(str_command);

            if (FindParams(lines_text[i_line], param) > 0)
            {
                size_t i_sym = param - lines_text[i_line].ptrline;

                int value = 0;
                sscanf(param, "%d", &value);
                bytecode[pc++] = (char)value;
            }
        }

        free(param);
    }

    free(str_command);

    return pc;
}


char WhichCommand(char* str_command)
{
    assert(str_command);

    #define CMD(name, num) \
    {\
           if(!strcmp(str_command, #name))\
                return num;\
    }

    #include "Commands.h"

    #undef CMD(name, num)

    return 0;
}


char WhichCommandReg(char* str_command)
{
    assert(str_command);

    #define CMDR(name, num) \
        if(!strcmp(str_command, #name))\
            return num;

    #include "Commands.h"

    #undef CMDR(name, num)

        return 0;
}




bool DeleteComm(struct LINE* lines_text, int nlines)
{
    assert(lines_text);

    char* temp = nullptr;

    for(size_t i_line = 0; i_line < nlines; i_line++)
    {
        temp = strchr(lines_text[i_line].ptrline, ';');

        for(size_t i_sym = (lines_text[i_line].ptrline - temp); i_sym < lines_text[i_line].length; i_sym++)
            lines_text[i_line].ptrline[i_sym] = '\0';
    }

    assert(lines_text);

    return true;
}



//0 - no patams
// >0 - numbers
// <0 - letter

int FindParams(struct LINE lines_text, char* param)
{

    assert(param);

    for(size_t i_sym = 0; i_sym < lines_text.length; i_sym++)
    {

        while(lines_text.ptrline[i_sym] == ' ' && isalpha(lines_text.ptrline[i_sym - 1]))
            i_sym++;

        while(isalnum(lines_text.ptrline[i_sym]))
            i_sym++;

        if(isdigit(lines_text.ptrline[i_sym]))
        {
            param = &lines_text.ptrline[i_sym];
            return 1;
        }

        if(isalpha(lines_text.ptrline[i_sym]))
        {
            param = &lines_text.ptrline[i_sym];
            return -1;
        }

        return 0;

    }

}
