#include "stack_header.h"

int main()
{

    My_stack stk = {};

    StackInit(&stk);

    StackPush(&stk, 111);
    StackPush(&stk, 112);
    StackPush(&stk, 113);
    StackPush(&stk, 114);
    StackPush(&stk, 115);
    StackPush(&stk, 116);

    #define $ fprintf (stderr, "(%d): ", __LINE__); for(int i = 0; i < stk.size; i++) fprintf (stderr, "%d, ", stk.data[i]); fprintf (stderr, "\n");

    Elem_t temp1  = StackPop(&stk);
    Elem_t temp2  = StackPop(&stk);
    Elem_t temp3  = StackPop(&stk);
    Elem_t temp4  = StackPop(&stk);
    Elem_t temp5  = StackPop(&stk);
    Elem_t temp6  = StackPop(&stk);

    std::cout << temp1 << "  ";
    std::cout << temp2 << "  ";
    std::cout << temp3 << "  ";
    std::cout << temp4 << "  ";
    std::cout << temp5 << "  ";
    std::cout << temp6 << "  ";

    StackDestroy(&stk);

    return 0;
}
