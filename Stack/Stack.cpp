#include "stack_header.h"

#define $(what)   std::cerr << __PRETTY_FUNCTION__ << " (" << __LINE__ << "): " << #what << " = " << what << std::endl

bool StackInit(My_stack* stk, size_t maxsize already_defined(BEGIN_MAX_SIZE))
{

    assert(stk);

    stk->left_canary = LEFT_CANARY;

    stk->left_ar_canary = nullptr;
    stk->right_ar_canary = nullptr;

    stk->maxsize = 0;
    stk->data = nullptr;
    stk->size = 0;

    stk->hash_sum = 0;
    stk->stk_err = STK_NO_ERROR;

    stk->right_canary = RIGHT_CANARY;


    if(maxsize != 0)
    {
        stk->maxsize = maxsize;
        StackMaxsizeCreate(stk);  }
    else
        stk->maxsize = 0;

    return true;
}


bool StackPush(My_stack* stk, Elem_t elem)
{

    assert(stk);

    if(stk->maxsize == 0)
        StackMaxsizeCreate(stk);

    if(stk->size >= stk->maxsize)
        StackMaxsizeInc(stk);

    stk->data[stk->size++] = elem;

    //Hash_Sum(stk->hash_sum, +, stk->data[stk->size]);

    assert_My_stack(stk);

    return true;

}


bool StackMaxsizeCreate(My_stack* stk)
{

    assert(stk);

    if(stk->size == 0)
        stk->size = BEGIN_MAX_SIZE;

    stk->data = (Elem_t*) calloc(stk->maxsize * sizeof(stk->data[0]) + 2 * sizeof(Canary_t), sizeof(stk->data[0]));

    StackNewDataCanary(stk);

    assert_My_stack(stk);

    return true;
}


bool StackMaxsizeInc(My_stack* stk)
{
    assert_My_stack(stk);

    if(stk->maxsize == 0)
        StackMaxsizeCreate(stk);

    stk->maxsize *= 2;

    stk->data = (Elem_t*)((Canary_t*)(stk->data) - 1);
    stk->data = (Elem_t*) realloc(stk->data, stk->maxsize * sizeof(stk->data[0]) + 2 * sizeof(Canary_t));

    StackNewDataCanary(stk);

    assert_My_stack(stk);

    return true;
}


bool StackNewDataCanary(My_stack* stk)
{
    assert(stk);

     stk->left_ar_canary  = (Canary_t*)stk->data;
    *stk->left_ar_canary  = LEFT_CANARY;
     stk->right_ar_canary = (Canary_t*)((Elem_t*)((Canary_t*)stk->data + 1) + stk->maxsize);
    *stk->right_ar_canary = RIGHT_CANARY;

    stk->data = (Elem_t*)((Canary_t*)stk->data + 1) ;

    assert_My_stack(stk);

    return true;
}


Elem_t StackPop(My_stack* stk)
{

    assert_My_stack(stk);

    if (!StackPeek(stk))
    {
        printf("Data is empty");
        return POISON;
    }

    Elem_t elem = stk->data[--stk->size];

    if(stk->maxsize >= (3 * stk->size))
        StackMaxsizeDec(stk);

    assert_My_stack(stk);

    return elem;
}


bool StackPeek(My_stack* stk)
{

    assert_My_stack(stk);

    if(stk->size == 0)
        return false;

    assert_My_stack(stk);

    return true;

}


bool StackMaxsizeDec(My_stack* stk)
{

    assert_My_stack(stk);

    stk->maxsize /= 2;
    stk->data = (Elem_t*)((Canary_t*)(stk->data) - 1);
    stk->data = (Elem_t*)realloc(stk->data, stk->maxsize * sizeof(stk->data[0]) + 2 * sizeof(Canary_t));

    StackNewDataCanary(stk);

    assert_My_stack(stk);

    return true;
}


bool StackClear(My_stack* stk)
{

    assert_My_stack(stk);

    while(stk->size > 0)
        stk->data[--stk->size] = POISON;

    return true;

}


bool StackDestroy(My_stack* stk)
{

    assert_My_stack(stk);

    StackClear(stk);

     stk->maxsize = 0;
     stk->left_canary     = POISON;
     stk->right_canary    = POISON;
    *stk->left_ar_canary  = POISON;
    *stk->right_ar_canary = POISON;
     stk->left_ar_canary  = nullptr;
     stk->right_ar_canary = nullptr;

     stk->data = (Elem_t*)((Canary_t*)(stk->data) - 1);
     free(stk->data);

    return true;
}

#define CHECK(what, code) \
    if(what) \
    { stk->stk_err = code; return false;}


bool StackCheck(My_stack* stk)
{

    assert(stk);

    CHECK (stk->stk_err != STK_NO_ERROR,           STK_ERR_ERR         )
    CHECK (stk->data == nullptr,                   STK_DATA_NULLPTR    )
    CHECK (stk->size > stk->maxsize,               STK_OVER_MAXSIZE    )
    CHECK (stk->size < 0,                          STK_SIZE_NEGATIVE   )
    CHECK (stk->maxsize < 0,                       STK_MAXSIZE_NEGATIVE)
    CHECK (stk->left_canary != LEFT_CANARY,        STK_LEFT_CANARY     )
    CHECK (stk->right_canary != RIGHT_CANARY,      STK_RIGHT_CANARY    )
    CHECK (*stk->left_ar_canary != LEFT_CANARY,    STK_LEFT_AR_CANARY  )
    CHECK (*stk->right_ar_canary != RIGHT_CANARY,  STK_RIGHT_AR_CANARY )
    CHECK (!StackCheckHashSum(stk),                STK_HASH_SUM_ERR    )

    return true;

}

#undef CHECK


inline bool StackCheckHashSum(My_stack* stk)
{

    assert(stk);

    unsigned int ControlHashSum = 0;
    for(size_t i_size = stk->size; i_size >= 0; i_size--)
//        Hash_Sum(ControlHashSum, +, stk->data[i_size]);

        return stk->hash_sum == ControlHashSum;

    return true;

}


void StackDump(My_stack* stk)
{

    FILE* Dump = fopen("DUMP.txt", "a");

    assert(Dump);

    fprintf(Dump, "If you see this I have bad news");
    fprintf(Dump, "#---------------------------------------\n");
    fprintf(Dump, "My_stack stk  ");
    fprintf(Dump, "[%p]", stk);

    if(stk == nullptr)
    {
        fprintf(Dump, "ERROOOOOOR!!! \n{\n");
        return;
    }
    else
        fprintf(Dump, "(ok)\n{\n");

    fprintf(Dump, "maxsize %ld\n", stk->maxsize);
    fprintf(Dump, "size %ld\n", stk->size);
    fprintf(Dump, "hashsum %d\n", stk->hash_sum);

    if(stk->data == nullptr)
    {
        fprintf(Dump, "NULLPTR DATA!!!");
        return;
    }
    else
        fprintf(Dump, "data[%ld] = [%p]\n", stk->size, stk->data);


    for(size_t i_size = 0; i_size < stk->maxsize; i_size++)
    {

        if((stk->data + i_size) != nullptr)
        {
            fprintf(Dump, "data[%ld] is ", i_size);
            fwrite(stk->data + i_size, sizeof(stk->data[0]), 1, Dump);
            if(stk->data[i_size] == POISON)
                fprintf(Dump, " (POISON?)");
            fprintf(Dump, "\n");
        }

        else
            fprintf(Dump, "nullptr data[%ld]", i_size);
    }
}
