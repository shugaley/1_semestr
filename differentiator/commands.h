DEF_COM(sin,     65,
        {
            return MUL ( ADD_COM(cos), dR );
        });


DEF_COM(cos,     66,
        {
            return MUL ( SUB (0, ADD_COM(sin)), dR );
        });


DEF_COM(tan,     67,
        {
            return MUL (DIV ( ADD_NUM(1), POW( ADD_COM(cos), ADD_NUM(2) ) ), dR );
        });


DEF_COM(ctan,    68,
        {
            return MUL( SUB ( ADD_NUM(0), DIV ( ADD_NUM(1), POW( ADD_COM(sin), ADD_NUM(2)) ) ),  dR );
        });


DEF_COM(sinh,    69,
        {
            return MUL( ADD_COM(cosh), dR);
        });


DEF_COM(cosh,    70,
        {
            return MUL( ADD_COM(sinh), dR);
        });


DEF_COM(tanh,    71,
        {
            return MUL( DIV (ADD_NUM(1), POW ( ADD_COM(cosh), ADD_NUM(2) ) ), dR );
        });


DEF_COM(ctanh,   72,
        {
            return  MUL( SUB ( ADD_NUM(0), DIV ( ADD_NUM(1), POW( ADD_COM(sinh), ADD_NUM(2)) ) ),  dR );
        });


DEF_COM(arctan,  75,
        {
            return MUL( DIV ( ADD_NUM(1), PLUS ( ADD_NUM(1), POW (cR, ADD_NUM(2)) ) ), dR);
        });



DEF_COM(arcctan, 76,
        {
            return MUL( SUB ( ADD_NUM(0), DIV ( ADD_NUM(1), PLUS ( ADD_NUM(1), POW(cR, ADD_NUM(2)) ) ) ), dR);
        });



DEF_COM(ln,      77,
        {
            return MUL( DIV ( ADD_NUM(1), cR ), dR);
        });


DEF_COM(exp,     79,
        {
            return MUL ( ADD_COM(exp), dR);
        });


