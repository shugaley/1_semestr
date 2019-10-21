#ifdef NON_REG_MOD

DEF_CMD(PUSH, 65,
{
    PC('c');
    DPUSH ((int)bytecode[pc]);
    PC('i');
});



DEF_CMD(POP,  66,
{
    DPOP;
    PC('c');
});



DEF_CMD(ADD,  43,
{
    DPUSH (DPOP + DPOP);
    PC('c');
});



DEF_CMD(SUB,  45,
{
    DPUSH ( -DPOP + DPOP);
    PC('c');
});



DEF_CMD(MUL,  42,
{
    DPUSH (DPOP * DPOP);
    PC('c');
});



DEF_CMD(DIV,  47,
{
    DPUSH ((1 / DPOP) * DPOP);
    PC('c');
});



DEF_CMD(SQRT, 37,
{
    DPUSH (sqrt(DPOP));
    PC('c');
});



DEF_CMD(JMP, 124,
{
    ;
});



DEF_CMD(JA, 62,
{
    ;
});



DEF_CMD(JB, 60,
{
    ;
});



DEF_CMD(JAE, 125,
{
    ;
});



DEF_CMD(JBE, 123,
{
    ;
});



DEF_CMD(JE, 61,
{
    ;
});



DEF_CMD(JNE, 33,
{
    ;
});



DEF_CMD(END,  90, ;);

#undef NON_REG_MOD
#endif




#ifdef REG_MOD

DEF_CMDR(PUSH, 97,
{
    PC('c');
    WHICH_REG(pc) = DPOP;
    PC('c');
});

DEF_CMDR(POP, 98,
{
    PC('c');
    DPUSH (WHICH_REG(pc));
    PC('c');
});


#undef REG_MOD
#endif
