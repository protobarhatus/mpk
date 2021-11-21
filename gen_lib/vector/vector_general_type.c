#include "vector_general_type.h"

void assignFunctionsVector(Vector * vec)
{
    vec->at = &atVector;
    vec->cat = &catVector;
    vec->resize = &resizeVector;
    vec->getSize = &getSizeVector;
    vec->pushBack = &pushBackVector;
    vec->pushBackRV = &pushBackVectorRV;
    vec->popBack = &popBackVector;
    vec->back = &VectorBack;
    vec->pushBackCalloced = &pushBackCallocedVector;

}

Vector defaultVector(int size, const GeneralType * def_value)
{
    Vector res;
    res.size = size;
    res.allocated_size = size * 2 + 1;
    res.vec = calloc(res.allocated_size, sizeof(GeneralType));
    assignFunctionsVector(&res);
    if (def_value == NULL)
        return res;
    for (int i = 0; i < size; ++i)
        res.vec[i] = copyGeneralType(def_value);



    return res;
}
Vector defaultVectorRV(int size, GeneralType def_value)
{
    Vector res;
    res.size = size;
    res.allocated_size = size * 2 + 1;
    res.vec = calloc(res.allocated_size, sizeof(GeneralType));
    if (size > 0)
    {
        for (int i = 1; i < size; ++i)
            res.vec[i] = copyGeneralType(&def_value);
        res.vec[0] = moveGeneralType(&def_value);
    }
    else
        destructGeneralType(&def_value);

    assignFunctionsVector(&res);
    return res;
}

Vector defaultVectorWithStrictSize(int size, const GeneralType * def_value)
{
    Vector res;
    res.size = size;
    res.allocated_size = size;
    res.vec = calloc(res.allocated_size, sizeof(GeneralType));
    assignFunctionsVector(&res);
    if (def_value == NULL)
        return res;
    for (int i = 0; i < size; ++i)
        res.vec[i] = copyGeneralType(def_value);



    return res;
}
Vector defaultVectorWithStrictSizeRV(int size, GeneralType def_value)
{
    Vector res;
    res.size = size;
    res.allocated_size = size;
    res.vec = calloc(res.allocated_size, sizeof(GeneralType));
    if (size > 0)
    {
        for (int i = 1; i < size; ++i)
            res.vec[i] = copyGeneralType(&def_value);
        res.vec[0] = moveGeneralType(&def_value);
    }
    else
        destructGeneralType(&def_value);

    assignFunctionsVector(&res);
    return res;
}

VectorRef wrapVector(const GeneralType * vec, int size)
{
    VectorRef res;
    res.size = size;
    res.allocated_size = -2;
    res.vec = (GeneralType *)vec;

    assignFunctionsVector(&res);
    return res;
}

Vector emptyVector()
{
    Vector res;
    res.size = 0;
    res.allocated_size = 0;
    res.vec = NULL;

    assignFunctionsVector(&res);

    return res;
}

Vector copyVector(const Vector * cop)
{
    Vector res;
    res.size = cop->size;
    res.allocated_size = cop->allocated_size;
    res.vec = calloc(res.allocated_size, sizeof(GeneralType));
    for (int i = 0; i < cop->size; ++i)
        res.vec[i] = copyGeneralType(cop->vec + i);

    assignFunctionsVector(&res);
    return res;
}
Vector moveVector(Vector * cop)
{
    Vector res;
    res.size = cop->size;
    res.allocated_size = cop->allocated_size;
    res.vec = cop->vec;
    cop->size = 0;
    cop->allocated_size = -2;
    cop->vec = NULL;
    assignFunctionsVector(&res);
    return res;
}

GeneralType * atVector(Vector * v, int i)
{
    return v->vec + i;
}
const GeneralType * catVector(const Vector * v, int i)
{
    return v->vec + i;
}

bool equalVector(const Vector * a, const Vector * b)
{
    if (a->size != b->size)
        return false;
    for (int i = 0; i < a->size;++i)
    {
        if (!equalGeneralType(catVector(a, i), catVector(b, i)))
            return false;
    }
    return true;
}

void popBackVector(Vector * a)
{
    if (a->size == 0)
        return;
    a->size--;
    destructGeneralType(atVector(a, a->size));
}

void pushBackVector(Vector * a, const GeneralType * val)
{
    if (a->allocated_size > a->size)
    {
        a->vec[a->size] = copyGeneralType(val);
        a->size++;
        return;
    }
    a->allocated_size = a->allocated_size * 2 + 1;
    a->vec = realloc(a->vec, a->allocated_size * sizeof(GeneralType));
    assert(a->vec != NULL);

    a->vec[a->size] = copyGeneralType(val);
    a->size++;

}

void pushBackVectorRV(Vector * a, GeneralType val)
{
    if (a->allocated_size > a->size)
    {
        a->vec[a->size] = moveGeneralType(&val);
        a->size++;
        return;
    }
    a->allocated_size = a->allocated_size * 2 + 1;
    a->vec = realloc(a->vec, a->allocated_size * sizeof(GeneralType));
    assert(a->vec != NULL);

    a->vec[a->size] = moveGeneralType(&val);
    a->size++;
}
void destructVector(Vector * vec)
{
    for (int i = 0; i < vec->size; ++i)
    {
        destructGeneralType(vec->vec + i);
    }
    free(vec->vec);
    vec->vec = NULL;
    vec->size = 0;
    vec->allocated_size = -2;
}

int getSizeVector(const Vector * a)
{
    return a->size;
}

void resizeVector(Vector * vec, int new_size)
{
    assert(new_size < vec->size);
    for (int i = vec->size - 1; i >= new_size; --i)
        destructGeneralType(vec->vec + i);
    vec->size = new_size;

}

void pushBackCallocedVector(Vector * vec, GeneralType * obj)
{
    pushBackVectorRV(vec, *obj);
    free(obj);
}

GeneralType * VectorDissolveIntoPointer(VectorRef * vec)
{
    vec->size = -1;
    vec->allocated_size = -1;
    return vec->vec;
}

GeneralType * VectorBack(Vector * vec)
{
    if (vec->size == 0)
        return NULL;
    return vec->vec + vec->size - 1;
}

void sortVector(Vector * vec, int (*comparator)(const void *, const void *))
{
    qsort(vec->vec, vec->size, sizeof(GeneralType), comparator);
}