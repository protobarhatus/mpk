#ifndef FIBONACHY_NIM_SPARSE_VECTOR_H
#define FIBONACHY_NIM_SPARSE_VECTOR_H
#include "vector.h"
//for some special algorithms
//didn't complete as dont need now but dont want to delete
#define MAKE_SPARSE_VECTOR(TN, UCN)                         \
struct SparseVector##UCN_struct {\
    Vector##UCN##Ref vec;                                   \
    int step;                                               \
    int actual_size;\
};                                                          \
typedef struct SparseVector##UCN_struct SparseVector##UCN;  \
static inline SparseVector##UCN wrapSparseVector##UCN(const Vector##UCN##Ref * orig, int step) \
{\
    SparseVector##UCN res;                                  \
    res.vec = *orig;                                        \
    res.step = step;                                        \
    res.actual_size = vector##UCN##GetSize(&orig->vec) / step + (vector##UCN##GetSize(&orig->vec) % step == 0 ? 0 : 1);\
}                                                           \
static inline TN * atSparseVector##UCN(SparseVector##UCN * obj, int i)           \
{                                                           \
    assert(i >= 0);                                         \
    assert(i < obj->actual_size);\
    return atVector##UCN(&obj->vec, i * obj->step);\
}                                                           \
static inline const TN * catSparseVector##UCN(const SparseVector##UCN * obj, int i)            \
{\
    assert(i >= 0);                                         \
    assert(i < obj->actual_size);                           \
    return catVector##UCN(&obj->vec, i * obj->step);\
}                                                           \
static inline int sparseVectorGetSize(const SparseVector##UCN * obj)                           \
{\
    return obj->actual_size;                                                            \
}



#endif //FIBONACHY_NIM_SPARSE_VECTOR_H
