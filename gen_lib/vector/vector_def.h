#ifndef VECTOR_DEF_H
#define VECTOR_DEF_H

#include "stdlib.h"
#include "string.h"
#include "../types_and_functions_declarations/general_type.h"
#include "vector_general_type.h"
#define MAKE_VECTOR(UCN, ARITHM_TYPE) \
                                                                                                           \
                                                                                                           \
                                                                                                           \
                                                                                                           \
                                                                                                           \
                                                                                                           \
                                                                                                           \
struct Vector##UCN##_struct                                                                                \
{                                                                                                          \
    UCN * vec;                                                                                             \
    int size;                                                                                              \
    int allocated_size;                                                                                    \
                                                                                                           \
                                                                                                           \
    UCN * (*at)(struct Vector##UCN##_struct * obj, int i);                                                 \
    const UCN * (*cat)(const struct Vector##UCN##_struct * obj, int i);                                    \
    int (*getSize)(const struct Vector##UCN##_struct * obj);                                               \
    void (*pushBack)(struct Vector##UCN##_struct * obj, const UCN* el);                                    \
    void (*pushBackRV)(struct Vector##UCN##_struct * obj, UCN el);                                         \
    UCN * (*back)(struct Vector##UCN##_struct * obj);                                                      \
    void (*pushBackCalloced)(struct Vector##UCN##_struct * obj, UCN * el);                                 \
    void (*popBack)(struct Vector##UCN##_struct * obj);                                                    \
    void (*resize)(struct Vector##UCN##_struct * obj, int new_size);                                       \
};                                                                                                         \
                                                                                                           \
typedef struct Vector##UCN##_struct Vector##UCN;                                                           \
typedef Vector##UCN VectorRef##UCN;                                                                        \
                                                                                                           \
static inline Vector##UCN defaultVector##UCN(int size, const UCN * def_value);                             \
static inline Vector##UCN defaultVector##UCN##RV(int size, UCN def_value);                                 \
                                                                                                           \
static inline Vector##UCN defaultVector##UCN##WithStrictSize(int size, const UCN * def_value);             \
static inline Vector##UCN defaultVector##UCN##WithStrictSizeRV(int size, UCN def_value);                   \
                                                                                                           \
static inline VectorRef##UCN wrapVector##UCN(const UCN * vec, int size);                                   \
                                                                                                           \
static inline Vector##UCN emptyVector##UCN();                                                              \
                                                                                                           \
static inline Vector##UCN copyVector##UCN(const Vector##UCN * cop);                                        \
static inline Vector##UCN moveVector##UCN(Vector##UCN * cop);                                              \
static inline void destructVector##UCN(Vector##UCN * vec);                                                 \
                                                                                                           \
static inline UCN * atVector##UCN(Vector##UCN * v, int i);                                                 \
static inline const UCN * catVector##UCN(const Vector##UCN * v, int i);                                    \
                                                                                                           \
static inline bool equalVector##UCN(const Vector##UCN * a, const Vector##UCN * b);                         \
                                                                                                           \
static inline void popBackVector##UCN(Vector##UCN * a);                                                    \
                                                                                                           \
static inline void pushBackVector##UCN(Vector##UCN * a, const UCN * val);                                  \
static inline void pushBackVector##UCN##RV(Vector##UCN * a, UCN val);                                      \
                                                                                                           \
static inline int getSizeVector##UCN(const Vector##UCN * a);                                               \
                                                                                                           \
static inline void resizeVector##UCN(Vector##UCN * vec, int new_size);                                     \
                                                                                                           \
static inline void pushBackCallocedVector##UCN(Vector##UCN * vec, UCN * obj);                              \
                                                                                                           \
static inline UCN * Vector##UCN##DissolveIntoPointer(VectorRef##UCN * vec);                                \
                                                                                                           \
static inline UCN * Vector##UCN##Back(Vector##UCN * vec);                                                  \
                                                                                                           \
static inline void sortVector##UCN(Vector##UCN * vec, int (*comparator)(const void *, const void *) );     \
                                                                                                           \
DECLARE_STRUCT_TYPE(Vector##UCN, Vector##UCN)                                                              \
                                                                                                           \
                                                                                                           \
                                                                                                         \
                                                                                                         \
static inline void assignFunctionsVector##UCN(Vector##UCN * vec)                                         \
{                                                                                                        \
    vec->at = &atVector##UCN;                                                                            \
    vec->cat = &catVector##UCN;                                                                          \
    vec->resize = &resizeVector##UCN;                                                                    \
    vec->getSize = &getSizeVector##UCN;                                                                  \
    vec->pushBack = &pushBackVector##UCN;                                                                \
    vec->pushBackRV = &pushBackVector##UCN##RV;                                                          \
    vec->popBack = &popBackVector##UCN;                                                                  \
    vec->back = &Vector##UCN##Back;                                                                      \
    vec->pushBackCalloced = &pushBackCallocedVector##UCN;                                                \
                                                                                                         \
}                                                                                                        \
                                                                                                         \
static inline Vector##UCN defaultVector##UCN(int size, const UCN * def_value)                            \
{                                                                                                        \
    Vector##UCN res;                                                                                     \
    res.size = size;                                                                                     \
    res.allocated_size = size * 2 + 1;                                                                   \
    res.vec = calloc(res.allocated_size, sizeof(UCN));                                                   \
    assignFunctionsVector##UCN(&res);                                                                    \
    if (def_value == NULL)                                                                               \
        return res;                                                                                      \
    for (int i = 0; i < size; ++i)                                                                       \
        res.vec[i] = copy##UCN(def_value);                                                               \
                                                                                                         \
                                                                                                         \
                                                                                                         \
    return res;                                                                                          \
}                                                                                                        \
static inline Vector##UCN defaultVector##UCN##RV(int size, UCN def_value)                                \
{                                                                                                        \
    Vector##UCN res;                                                                                     \
    res.size = size;                                                                                     \
    res.allocated_size = size * 2 + 1;                                                                   \
    res.vec = calloc(res.allocated_size, sizeof(UCN));                                                   \
    if (size > 0)                                                                                        \
    {                                                                                                    \
        for (int i = 1; i < size; ++i)                                                                   \
            res.vec[i] = copy##UCN(&def_value);                                                          \
        res.vec[0] = move##UCN(&def_value);                                                              \
    }                                                                                                    \
    else                                                                                                 \
        destruct##UCN(&def_value);                                                                       \
                                                                                                         \
    assignFunctionsVector##UCN(&res);                                                                    \
    return res;                                                                                          \
}                                                                                                        \
                                                                                                         \
static inline Vector##UCN defaultVector##UCN##WithStrictSize(int size, const UCN * def_value)            \
{                                                                                                        \
    Vector##UCN res;                                                                                     \
    res.size = size;                                                                                     \
    res.allocated_size = size;                                                                           \
    res.vec = calloc(res.allocated_size, sizeof(UCN));                                                   \
    assignFunctionsVector##UCN(&res);                                                                    \
    if (def_value == NULL)                                                                               \
        return res;                                                                                      \
    for (int i = 0; i < size; ++i)                                                                       \
        res.vec[i] = copy##UCN(def_value);                                                               \
                                                                                                         \
                                                                                                         \
                                                                                                         \
    return res;                                                                                          \
}                                                                                                        \
static inline Vector##UCN defaultVector##UCN##WithStrictSizeRV(int size, UCN def_value)                  \
{                                                                                                        \
    Vector##UCN res;                                                                                     \
    res.size = size;                                                                                     \
    res.allocated_size = size;                                                                           \
    res.vec = calloc(res.allocated_size, sizeof(UCN));                                                   \
    if (size > 0)                                                                                        \
    {                                                                                                    \
        for (int i = 1; i < size; ++i)                                                                   \
            res.vec[i] = copy##UCN(&def_value);                                                          \
        res.vec[0] = move##UCN(&def_value);                                                              \
    }                                                                                                    \
    else                                                                                                 \
        destruct##UCN(&def_value);                                                                       \
                                                                                                         \
    assignFunctionsVector##UCN(&res);                                                                    \
    return res;                                                                                          \
}                                                                                                        \
                                                                                                         \
static inline VectorRef##UCN wrapVector##UCN(const UCN * vec, int size)                                  \
{                                                                                                        \
    VectorRef##UCN res;                                                                                  \
    res.size = size;                                                                                     \
    res.allocated_size = -2;                                                                             \
    res.vec = (UCN *)vec;                                                                                \
                                                                                                         \
    assignFunctionsVector##UCN(&res);                                                                    \
    return res;                                                                                          \
}                                                                                                        \
                                                                                                         \
static inline Vector##UCN emptyVector##UCN()                                                             \
{                                                                                                        \
    Vector##UCN res;                                                                                     \
    res.size = 0;                                                                                        \
    res.allocated_size = 0;                                                                              \
    res.vec = NULL;                                                                                      \
                                                                                                         \
    assignFunctionsVector##UCN(&res);                                                                    \
                                                                                                         \
    return res;                                                                                          \
}                                                                                                        \
                                                                                                         \
static inline Vector##UCN copyVector##UCN(const Vector##UCN * cop)                                       \
{                                                                                                        \
    Vector##UCN res;                                                                                     \
    res.size = cop->size;                                                                                \
    res.allocated_size = cop->allocated_size;                                                            \
    res.vec = calloc(res.allocated_size, sizeof(UCN));                                                   \
    for (int i = 0; i < cop->size; ++i)                                                                  \
        res.vec[i] = copy##UCN(cop->vec + i);                                                            \
                                                                                                         \
    assignFunctionsVector##UCN(&res);                                                                    \
    return res;                                                                                          \
}                                                                                                        \
static inline Vector##UCN moveVector##UCN(Vector##UCN * cop)                                             \
{                                                                                                        \
    Vector##UCN res;                                                                                     \
    res.size = cop->size;                                                                                \
    res.allocated_size = cop->allocated_size;                                                            \
    res.vec = cop->vec;                                                                                  \
    cop->size = 0;                                                                                       \
    cop->allocated_size = -2;                                                                            \
    cop->vec = NULL;                                                                                     \
    assignFunctionsVector##UCN(&res);                                                                    \
    return res;                                                                                          \
}                                                                                                        \
                                                                                                         \
static inline UCN * atVector##UCN(Vector##UCN * v, int i)                                                \
{                                                                                                        \
    return v->vec + i;                                                                                   \
}                                                                                                        \
static inline const UCN * catVector##UCN(const Vector##UCN * v, int i)                                   \
{                                                                                                        \
    return v->vec + i;                                                                                   \
}                                                                                                        \
                                                                                                         \
static inline bool equalVector##UCN(const Vector##UCN * a, const Vector##UCN * b)                        \
{                                                                                                        \
    if (a->size != b->size)                                                                              \
        return false;                                                                                    \
    for (int i = 0; i < a->size;++i)                                                                     \
    {                                                                                                    \
        if (!equal##UCN(catVector##UCN(a, i), catVector##UCN(b, i)))                                     \
            return false;                                                                                \
    }                                                                                                    \
    return true;                                                                                         \
}                                                                                                        \
                                                                                                         \
static inline void popBackVector##UCN(Vector##UCN * a)                                                   \
{                                                                                                        \
    if (a->size == 0)                                                                                    \
        return;                                                                                          \
    a->size--;                                                                                           \
    destruct##UCN(atVector##UCN(a, a->size));                                                            \
}                                                                                                        \
                                                                                                         \
static inline void pushBackVector##UCN(Vector##UCN * a, const UCN * val)                                 \
{                                                                                                        \
    if (a->allocated_size > a->size)                                                                     \
    {                                                                                                    \
        a->vec[a->size] = copy##UCN(val);                                                                \
        a->size++;                                                                                       \
        return;                                                                                          \
    }                                                                                                    \
    a->allocated_size = a->allocated_size * 2 + 1;                                                       \
    a->vec = realloc(a->vec, a->allocated_size * sizeof(UCN));                                           \
    assert(a->vec != NULL);                                                                              \
                                                                                                         \
    a->vec[a->size] = copy##UCN(val);                                                                    \
    a->size++;                                                                                           \
                                                                                                         \
}                                                                                                        \
                                                                                                         \
static inline void pushBackVector##UCN##RV(Vector##UCN * a, UCN val)                                     \
{                                                                                                        \
    if (a->allocated_size > a->size)                                                                     \
    {                                                                                                    \
        a->vec[a->size] = move##UCN(&val);                                                               \
        a->size++;                                                                                       \
        return;                                                                                          \
    }                                                                                                    \
    a->allocated_size = a->allocated_size * 2 + 1;                                                       \
    a->vec = realloc(a->vec, a->allocated_size * sizeof(UCN));                                           \
    assert(a->vec != NULL);                                                                              \
                                                                                                         \
    a->vec[a->size] = move##UCN(&val);                                                                   \
    a->size++;                                                                                           \
}                                                                                                        \
static inline void destructVector##UCN(Vector##UCN * vec)                                                \
{                                                                                                        \
    for (int i = 0; i < vec->size; ++i)                                                                  \
    {                                                                                                    \
        destruct##UCN(vec->vec + i);                                                                     \
    }                                                                                                    \
    free(vec->vec);                                                                                      \
    vec->vec = NULL;                                                                                     \
    vec->size = 0;                                                                                       \
    vec->allocated_size = -2;                                                                            \
}                                                                                                        \
                                                                                                         \
static inline int getSizeVector##UCN(const Vector##UCN * a)                                              \
{                                                                                                        \
    return a->size;                                                                                      \
}                                                                                                        \
                                                                                                         \
static inline void resizeVector##UCN(Vector##UCN * vec, int new_size)                                    \
{                                                                                                        \
    /*assert(new_size < vec->size);*/                                                                    \
    if (new_size >= vec->size)                                                                           \
    {                                                                                                    \
        if (new_size > vec->allocated_size)                                                              \
        {                                                                                                \
            while (new_size >= vec->allocated_size)                                                      \
                vec->allocated_size = vec->allocated_size * 2 + 1;                                       \
            vec->vec = realloc(vec->vec, vec->allocated_size * sizeof(UCN));                             \
        }                                                                                                \
        memset(atVector##UCN(vec, vec->size), 0, (new_size - vec->size) * sizeof (UCN));                 \
        vec->size = new_size;                                                                            \
        return;                                                                                          \
    }                                                                                                    \
    for (int i = vec->size - 1; i >= new_size; --i)                                                      \
        destruct##UCN(vec->vec + i);                                                                     \
    vec->size = new_size;                                                                                \
                                                                                                         \
}                                                                                                        \
                                                                                                         \
static inline void pushBackCallocedVector##UCN(Vector##UCN * vec, UCN * obj)                             \
{                                                                                                        \
    pushBackVector##UCN##RV(vec, *obj);                                                                  \
    free(obj);                                                                                           \
}                                                                                                        \
                                                                                                         \
static inline UCN * Vector##UCN##DissolveIntoPointer(VectorRef##UCN * vec)                               \
{                                                                                                        \
    vec->size = -1;                                                                                      \
    vec->allocated_size = -1;                                                                            \
    return vec->vec;                                                                                     \
}                                                                                                        \
                                                                                                         \
static inline UCN * Vector##UCN##Back(Vector##UCN * vec)                                                 \
{                                                                                                        \
    if (vec->size == 0)                                                                                  \
        return NULL;                                                                                     \
    return vec->vec + vec->size - 1;                                                                     \
}                                                                                                        \
                                                                                                         \
static inline void sortVector##UCN(Vector##UCN * vec, int (*comparator)(const void *, const void *))     \
{                                                                                                        \
    qsort(vec->vec, vec->size, sizeof(UCN), comparator);                                                 \
}                                                                                                        \


#endif
