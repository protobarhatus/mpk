#ifndef FIBONACHY_NIM_FUNCTIONS_EXTENSIONS_H
#define FIBONACHY_NIM_FUNCTIONS_EXTENSIONS_H

//useful extensions for standart functions like RETV funcUCN(const TN * a, const TN * b)
//its veery inconvenient to do arithmetic without this overloads because have to make buffers for all subcomputatons
//to avoid memory leaks

#define GENERATE_RIGHT_VALUE_UNARY_EXTENSIONS_TO_VOID_FUNC(TN, UCN, FUNC) \
static inline void FUNC##UCN##RV(TN a)                                    \
{\
    FUNC##UCN(&a);                                                        \
    destruct##UCN(&a);\
}


#define GENERATE_RIGHT_VALUE_UNARY_EXTENSIONS(TN, UCN, FUNC, RETV) \
static inline RETV FUNC##UCN##RV(TN a)                         \
{                                                            \
    RETV res = FUNC##UCN(&a);                                  \
    destruct##UCN(&a);                                       \
    return res;                                              \
}

#define GENERATE_RIGHT_VALUE_BINARY_EXTENSIONS(TN, UCN, FUNC, RETV) \
static inline RETV FUNC##UCN##LVRV(const TN * a, TN b)                 \
{                                                      \
    RETV res = FUNC##UCN(a, &b);                         \
    destruct##UCN(&b);                                 \
    return res;                                        \
}                                                      \
static inline RETV FUNC##UCN##RVLV(TN a, const TN * b)                 \
{                                                      \
    RETV res = FUNC##UCN(&a, b);                         \
    destruct##UCN(&a);                                 \
    return res;                                        \
}                                                      \
static inline RETV FUNC##UCN##RV(TN a, TN b)                           \
{                                                      \
    RETV res = FUNC##UCN(&a, &b);                        \
    destruct##UCN(&a);                                 \
    destruct##UCN(&b);                                 \
    return res;                                        \
}                                                      \




#define GENERATE_RIGHT_VALUE_CUMULATIVE_UNARY_EXTENSIONS(TN, UCN, FUNC) \
static inline void FUNC##UCN##RV(TN * a, TN b)                                \
{\
    FUNC##UCN(a, &b);                                                   \
    destruct##UCN(&b);\
}



#endif //FIBONACHY_NIM_FUNCTIONS_EXTENSIONS_H
