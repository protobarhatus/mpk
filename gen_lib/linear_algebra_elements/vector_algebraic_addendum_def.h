#ifndef VECTOR_ALGEBRAIC_ADDENDUM_DEF_H
#define VECTOR_ALGEBRAIC_ADDENDUM_DEF_H

#include "../vector/vector.h"
#include "../types_and_functions_declarations/arithmetic_type_declaration.h"
#include "../types_and_functions_declarations/type_declaration.h"
#include "../types_and_functions_declarations/functions_extensions.h"
#include "vector_algebraic_addendum_general_type.h"
#include "../vector/algorithms.h"
#define MAKE_VECTOR_ALGEBRAIC_ADDENDUM(UCN) \
                                                                                                                                    \
                                                                                                                                    \
                                                                                                                                    \
                                                                                                                                    \
                                                                                                                                    \
                                                                                                                                    \
/*to make vector algebra functions for type TN, need to declare its as type, as arithmetic_type and*/                               \
/*then generate functions here*/                                                                                                    \
/*unfortunately, vector can not be declared as arithmetic type because it will have to define many unsutable for it functions*/     \
/*and arithmetic of vector of vector is described in matrix and it differs.*/                                                       \
static inline void addToVector##UCN(Vector##UCN * dest, const Vector##UCN * b);                                                     \
static inline void subToVector##UCN(Vector##UCN * dest, const Vector##UCN * b);                                                     \
                                                                                                                                    \
static inline Vector##UCN addVector##UCN(const Vector##UCN * a, const Vector##UCN * b);                                             \
static inline Vector##UCN subVector##UCN(const Vector##UCN * a, const Vector##UCN * b);                                             \
                                                                                                                                    \
static inline void multVector##UCN##OnNum(Vector##UCN * dest, const UCN * el);                                                      \
static inline Vector##UCN Vector##UCN##MultedOnNum(const Vector##UCN * vec, const void * el);                                              \
                                                                                                                                    \
static inline UCN scalarVector##UCN(const Vector##UCN * a, const Vector##UCN * b);                                                  \
                                                                                                                                    \
static inline UCN lengthVector##UCN(const Vector##UCN * a);                                                                         \
static inline UCN distanceVector##UCN(const Vector##UCN * a, const Vector##UCN * b);                                                \
                                                                                                                                    \
                                                                                                                                    \
GENERATE_RIGHT_VALUE_BINARY_EXTENSIONS(Vector##UCN, Vector##UCN, add, Vector##UCN)                                                  \
GENERATE_RIGHT_VALUE_BINARY_EXTENSIONS(Vector##UCN, Vector##UCN, sub, Vector##UCN)                                                  \
GENERATE_RIGHT_VALUE_BINARY_EXTENSIONS(Vector##UCN, Vector##UCN, scalar, UCN)                                                       \
GENERATE_RIGHT_VALUE_BINARY_EXTENSIONS(Vector##UCN, Vector##UCN, distance, UCN)                                                     \
GENERATE_RIGHT_VALUE_UNARY_EXTENSIONS(Vector##UCN, Vector##UCN, length, UCN)                                                        \
                                                                                                                                    \
                                                                                                                                    \
                                                                                                                                    \
                                                                                                                                    \
                                                                                                                                                      \
                                                                                                                                                      \
                                                                                                                                                      \
                                                                                                                                                      \
static inline void addToVector##UCN(Vector##UCN * dest, const Vector##UCN * b)                                                                        \
{                                                                                                                                                     \
    /*we can compare pointers by value because there is only one instance of type presenter*/                                                         \
    assert(dest->size == b->size);                                                                                                                    \
                                                                                                                                                      \
    for (int i = 0; i < dest->size; ++i)                                                                                                              \
        addTo##UCN(atVector##UCN(dest, i), catVector##UCN(b, i));                                                                                     \
                                                                                                                                                      \
}                                                                                                                                                     \
                                                                                                                                                      \
static inline void subToVector##UCN(Vector##UCN * dest, const Vector##UCN * b)                                                                        \
{                                                                                                                                                     \
    assert(dest->size == b->size);                                                                                                                    \
                                                                                                                                                      \
    for (int i = 0; i < dest->size; ++i)                                                                                                              \
        subTo##UCN(atVector##UCN(dest, i), catVector##UCN(b, i));                                                                                     \
}                                                                                                                                                     \
                                                                                                                                                      \
static inline Vector##UCN addVector##UCN(const Vector##UCN * a, const Vector##UCN * b)                                                                \
{                                                                                                                                                     \
    assert(a->size == b->size);                                                                                                                       \
                                                                                                                                                      \
    Vector##UCN res = defaultVector##UCN##WithStrictSize(a->size, NULL);                                                                              \
    for (int i = 0; i < a->size; ++i)                                                                                                                 \
        replace##UCN(atVector##UCN(&res, i), add##UCN(catVector##UCN(a, i), catVector##UCN(b, i)));                                                   \
    return res;                                                                                                                                       \
}                                                                                                                                                     \
                                                                                                                                                      \
static inline Vector##UCN subVector##UCN(const Vector##UCN * a, const Vector##UCN * b)                                                                \
{                                                                                                                                                     \
    assert(a->size == b->size);                                                                                                                       \
                                                                                                                                                      \
    Vector##UCN res = defaultVector##UCN##WithStrictSize(a->size, NULL);                                                                              \
    for (int i = 0; i < a->size; ++i)                                                                                                                 \
        replace##UCN(atVector##UCN(&res, i), sub##UCN(catVector##UCN(a, i), catVector##UCN(b, i)));                                                   \
    return res;                                                                                                                                       \
}                                                                                                                                                     \
/*el такого же типа как элементы вектора, но проверять это здесь нет возможности*/     \
static inline void multVector##UCN##OnNum(Vector##UCN * dest, const UCN * el)                                                                         \
{                                                                                                                                                     \
    for (int i = 0; i < dest->size; ++i)                                                                                                              \
        multTo##UCN(atVector##UCN(dest, i), el);                                                                                                      \
}                                                                                                                                                     \
static inline Vector##UCN Vector##UCN##MultedOnNum(const Vector##UCN * vec, const void * el)                                                                 \
{                                                                                                                                                     \
    Vector##UCN res = defaultVector##UCN##WithStrictSize(vec->size, NULL);                                                                            \
    for (int i = 0; i < vec->size; ++i)                                                                                                               \
        replace##UCN(atVector##UCN(&res, i), mult##UCN(catVector##UCN(vec, i), el));                                                                  \
    return res;                                                                                                                                       \
}                                                                                                                                                     \
                                                                                                                                                      \
static inline UCN scalarVector##UCN(const Vector##UCN * a, const Vector##UCN * b)                                                                     \
{                                                                                                                                                     \
    assert(a->size == b->size);                                                                                                                       \
                                                                                                                                                      \
    UCN res = null##UCN();                                                                                                                            \
    for (int i = 0; i < a->size; ++i)                                                                                                                 \
    {                                                                                                                                                 \
        addTo##UCN##RV(&res, mult##UCN(catVector##UCN(a, i), catVector##UCN(b, i)));                                                                  \
    }                                                                                                                                                 \
                                                                                                                                                      \
                                                                                                                                                      \
    return res;                                                                                                                                       \
}                                                                                                                                                     \
                                                                                                                                                      \
static inline UCN lengthVector##UCN(const Vector##UCN * a)                                                                                            \
{                                                                                                                                                     \
    UCN res = null##UCN();                                                                                                                            \
    for (int i = 0; i < a->size; ++i)                                                                                                                 \
    {                                                                                                                                                 \
        addTo##UCN##RV(&res, mult##UCN(catVector##UCN(a, i), catVector##UCN(a, i)));                                                                  \
    }                                                                                                                                                 \
                                                                                                                                                      \
    return sqrt##UCN##RV(res);                                                                                                                        \
                                                                                                                                                      \
}                                                                                                                                                     \
static inline UCN distanceVector##UCN(const Vector##UCN * a, const Vector##UCN * b)                                                                   \
{                                                                                                                                                     \
    assert(a->size == b->size);                                                                                                                       \
    UCN res = null##UCN();                                                                                                                            \
                                                                                                                                                      \
    for (int i = 0; i < a->size; ++i)                                                                                                                 \
    {                                                                                                                                                 \
        UCN subres = sub##UCN(catVector##UCN(a, i), catVector##UCN(b, i));                                                                            \
        addTo##UCN##RV(&res, mult##UCN(&subres, &subres));                                                                                            \
        destruct##UCN(&subres);                                                                                                                       \
    }                                                                                                                                                 \
                                                                                                                                                      \
                                                                                                                                                      \
    return sqrt##UCN##RV(res);                                                                                                                        \
}                                                                                                                                                     \





#endif
