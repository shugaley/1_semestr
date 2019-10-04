#ifndef STEK_STACK_H
#define STEK_STACK_H

#endif //STEK_STACK_H



#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int Elem_t;
typedef long long Canary_t;

const size_t BEGIN_MAX_SIZE = 1;

const Elem_t POISON = -1488228;

const Canary_t LEFT_CANARY = 88005553535;
const Canary_t RIGHT_CANARY = 53535550088;

//const Canary_t* AR_LEFT_CANARY = 0xBEDAB0DA;
//const Canary_t* AR_RIGHT_CANARY = 0xAD0BADEB;

enum Stack_error
{
    STK_NO_ERROR = 0,
    STK_NULLPTR = 1,
    STK_DATA_NULLPTR = 2,
    STK_OVER_MAXSIZE = 3,
    STK_SIZE_NEGATIVE = 4,
    STK_MAXSIZE_NEGATIVE = 5,
    STK_LEFT_CANARY = 6,
    STK_RIGHT_CANARY = 7,
    STK_LEFT_AR_CANARY = 8,
    STK_RIGHT_AR_CANARY = 9,
    STK_HASH_SUM_ERR = 10,
};


struct My_stack
{
    Canary_t left_canary;
    Canary_t* left_ar_canary;

    Elem_t* data;
    size_t size;
    size_t maxsize;
    unsigned int hash_sum;
    Stack_error stk_err;

    Canary_t* right_ar_canary;
    Canary_t right_canary;
};


//================================================================================


#define already_defined(what)

// --------------------------------------------------------------------------

//Secure


#define MURMUR

#define dump \
{\
    printf("Error file %s\n",__FILE__);\
    printf("Error function %s\n", __PRETTY_FUNCTION__);\
    printf("Error line %d\n",__LINE__);\
}

#ifdef MURMUR
#define assert_My_stack(PointerStk)\
{\
    if(StackCheck(PointerStk) == false )\
    {\
        printf("I have bad news. Check DUMP\n");\
        dump;\
        StackDump(PointerStk);\
        abort();\
    }\
}
#else
#define  assert_My_stack(PointerStk)
#endif


#ifdef MURMUR
#define Hash_Sum(val, oper, change)\
{\
    if((#oper)[0]) == '+')\
    {\
        (val) = ((val) + (chage));\
        (val) = ( ( (int)(val)) << 1);\
    }\
    else\
    {\
        (val) =( ( (int)(val)) >> 1);\
        (val) = ((val) - (change));\
}

#else
#define Hash_Sum(val, oper, change)

#endif




bool StackInit(My_stack* stk);
bool StackMaxsizeCreate(My_stack* stk);
bool StackPush(My_stack* stk, Elem_t elem);
bool StackMaxsizeInc(My_stack* stk);
Elem_t StackPop(My_stack* stk);
bool StackPeek(My_stack* stk);
bool StackMaxsizeDec(My_stack* stk);
bool StackClear(My_stack* stk);
bool StackDestroy(My_stack* stk);
bool StackCheck(const My_stack* stk);
inline bool StackCheckHashSum(const My_stack* stk);
void StackDump(My_stack* stk);
