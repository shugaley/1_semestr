#include "header_ass.h"

enum FindParams
{
    NO_PARAMS = 0,
    NUMBER,
    REGISTER,
    RAM,

};

const int MAX_COMMAND_SIZE = 50;


int assembler(struct LINE* lines_text, char* bytecode) {
    assert(bytecode);

    ST_MARK* marks = (ST_MARK*)calloc(sizeof(lines_text), sizeof(marks[0]));
    marks->name = (char*)calloc(MAX_COMMAND_SIZE, sizeof(marks->name[0]));
    marks = CreateMarks(lines_text);

    int pc = 0;
    char *str_command = (char*) calloc(MAX_COMMAND_SIZE, sizeof(str_command[0]));

    for (size_t i_line = 0; bytecode[pc - 1] != 90; i_line++)
    {
        char *str = lines_text[i_line].ptrline;

        DeleteComm(str);

        sscanf(str, "%s", str_command);

        int value = 0;
        char* regis = (char*) (calloc)(MAX_COMMAND_SIZE, sizeof(regis[0]));
        switch (FindParams(str, &value, marks))
        {
            case NO_PARAMS:
                bytecode[pc++] = WhichCommand(str_command);
                sscanf(str, "%*s %s", regis);
                bytecode[pc++] = regis[0];
                break;

            case NUMBER:
                bytecode[pc++] = WhichCommand(str_command);
                *(int*)(bytecode + pc) = value;
                pc += sizeof(value);
                break;

            case REGISTER:
                bytecode[pc++] = WhichCommandReg(str_command);
                break;

            default:
                perror("Assembler error");
        }

    }
    free(str_command);

    return pc;
}


char WhichCommand(char* str_command)
{
    assert(str_command);

    #define DEF_CMD(name, num, code)\
        if(strcasecmp(str_command, #name) == 0)\
            return num;

    #define NON_REG_MOD

    #include "commands.h"

    #undef DEF_CMD

    return 0;
}



char WhichCommandReg(char* str_command)
{
    assert(str_command);

    #define DEF_CMDR(name, num, code) \
        if(strcasecmp(str_command, #name) == 0)\
            return num;

    #define REG_MOD

    #include "commands.h"

    #undef DEF_CMDR

    return 0;
}




bool DeleteComm(char* str)
{
    assert(str);

    char* comment = strchr (str, ';');
    if (comment)
        *comment = '\0';

    assert(str);

    return true;
}


int FindParams(char* str, int* value, ST_MARK* marks)
{
    assert(str);

    if(sscanf(str, "%*s %d", value) == 1)
        return NUMBER;

    char* param = (char*)calloc(MAX_COMMAND_SIZE, sizeof(param[0]));
    sscanf(str, "%*s %s", param);

    if(isalpha(*param))
    {
        if(FindMark(param, value, marks))
            return NUMBER;
        else
            return REGISTER;
    }


    free(param);

    assert(str);

    return NO_PARAMS;
}



ST_MARK* CreateMarks(LINE* lines_text)
{
    assert(lines_text);

    ST_MARK* marks = (ST_MARK*)calloc(sizeof(lines_text), sizeof(marks[0]));
    marks->name = (char*)calloc(MAX_COMMAND_SIZE, sizeof(marks->name[0]));
    for(size_t i_line = 0; i_line < sizeof(lines_text); i_line++)
    {

        char* str = lines_text[i_line].ptrline;
        if(strchr(str, ':'))
        {
            sscanf(str, "%s", marks[i_line].name);
            marks[i_line].address = i_line;
        }
    }
}



bool FindMark(char* param, int* value, ST_MARK* marks)
{
    assert(param);

    for(size_t i_line = 0; i_line < sizeof(marks); i_line++)
        if(!strcasecmp(param, marks[i_line].name))
        {
            *value = marks[i_line].address;
            return true;
        }

    return false;
}
