#ifndef DIFFERENTIATOR_DSL_H
#define DIFFERENTIATOR_DSL_H

#define dR Create_TreeDiffElem(pos->right)
#define dL Create_TreeDiffElem(pos->left )

#define cR Copy(pos->right)
#define cL Copy(pos->left )

#define NUM MODE_NUMBER, 0, nullptr
#define VAR MODE_VAR   , 1, nullptr

#define NData(what) Create_TreeDiffNewData(what)

#define  NData_Op(what) Create_TreeDiffNewData(MODE_OPERATOR, *(#what), nullptr)
#define NData_Com(what) Create_TreeDiffNewData(MODE_COMMAND, 0, #what)

#define ADD_NUM(what) Add_TreeDiffElem( Create_TreeDiffNewData(MODE_NUMBER,  1, nullptr),  nullptr, nullptr)
#define ADD_COM(what) Add_TreeDiffElem( Create_TreeDiffNewData(MODE_COMMAND, 0, #what  ),  nullptr, cR)

#define ADD(what) Add_TreeDiffElem( Create_TreeDiffNewData(what), nullptr, nullptr);

#define PLUS(L, R) Add_TreeDiffElem(NData_Op(+), L, R)

#define  SUB(L, R) Add_TreeDiffElem(NData_Op(-), L, R)

#define  MUL(L, R) Add_TreeDiffElem(NData_Op(*), L, R)

#define  DIV(L, R) Add_TreeDiffElem(NData_Op(/), L, R)

#define  POW(L, R) Add_TreeDiffElem(NData_Op(^), L, R)

#endif //DIFFERENTIATOR_DSL_H