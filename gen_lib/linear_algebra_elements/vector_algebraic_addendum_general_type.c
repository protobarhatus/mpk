
#include "vector_algebraic_addendum_general_type.h"
#include "../vector/algorithms.h"

void addToVector(Vector * dest, const Vector * b)
{
    //we can compare pointers by value because there is only one instance of type presenter
    assert(dest->size == b->size);

    for (int i = 0; i < dest->size; ++i)
        addToGeneralType(atVector(dest, i), catVector(b, i));

}

void subToVector(Vector * dest, const Vector * b)
{
    assert(dest->size == b->size);

    for (int i = 0; i < dest->size; ++i)
        subToGeneralType(atVector(dest, i), catVector(b, i));
}

Vector addVector(const Vector * a, const Vector * b)
{
    assert(a->size == b->size);

    Vector res = defaultVectorWithStrictSize(a->size, NULL);
    for (int i = 0; i < a->size; ++i)
        replaceGeneralType(atVector(&res, i), addGeneralType(catVector(a, i), catVector(b, i)));
    return res;
}

Vector subVector(const Vector * a, const Vector * b)
{
    assert(a->size == b->size);

    Vector res = defaultVectorWithStrictSize(a->size, NULL);
    for (int i = 0; i < a->size; ++i)
        replaceGeneralType(atVector(&res, i), subGeneralType(catVector(a, i), catVector(b, i)));
    return res;
}
//el такого же типа как элементы вектора, но проверять это здесь нет возможности
void multVectorOnNum(Vector * dest, const GeneralType * el)
{
    for (int i = 0; i < dest->size; ++i)
        multToGeneralType(atVector(dest, i), el);
}
Vector VectorMultedOnNum(const Vector * vec, const void * el)
{
    Vector res = defaultVectorWithStrictSize(vec->size, NULL);
    for (int i = 0; i < vec->size; ++i)
        replaceGeneralType(atVector(&res, i), multGeneralType(catVector(vec, i), el));
    return res;
}

GeneralType scalarVector(const Vector * a, const Vector * b)
{
    assert(a->size == b->size);

    GeneralType res = nullGeneralType();
    for (int i = 0; i < a->size; ++i)
    {
        addToGeneralTypeRV(&res, multGeneralType(catVector(a, i), catVector(b, i)));
    }


    return res;
}

GeneralType lengthVector(const Vector * a)
{
    GeneralType res = nullGeneralType();
    for (int i = 0; i < a->size; ++i)
    {
        addToGeneralTypeRV(&res, multGeneralType(catVector(a, i), catVector(a, i)));
    }

    return sqrtGeneralTypeRV(res);

}
GeneralType distanceVector(const Vector * a, const Vector * b)
{
    assert(a->size == b->size);
    GeneralType res = nullGeneralType();

    for (int i = 0; i < a->size; ++i)
    {
        GeneralType subres = subGeneralType(catVector(a, i), catVector(b, i));
        addToGeneralTypeRV(&res, multGeneralType(&subres, &subres));
        destructGeneralType(&subres);
    }


    return sqrtGeneralTypeRV(res);
}