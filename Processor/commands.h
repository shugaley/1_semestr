#ifdef NON_REG_MOD

CMD(PUSH, 65)
CMD(POP,  66)
CMD(ADD,  67)
CMD(SUB,  68)
CMD(MUL,  69)
CMD(DIV,  70)
CMD(END,  90)

#undef NON_REG_MOD
#endif








#ifdef REG_MOD

CMDR(PUSH, 97)
CMDR(POP, 98)

#undef REG_MOD
#endif
