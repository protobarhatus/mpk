#ifndef FIBONACHY_NIM_VECTOR_GENERAL_TYPE_H
#define FIBONACHY_NIM_VECTOR_GENERAL_TYPE_H

#include "stdlib.h"
#include "string.h"
#include "../types_and_functions_declarations/general_type.h"

struct Vector_struct
{
    GeneralType * vec;
    int size;
    int allocated_size;


    GeneralType * (*at)(struct Vector_struct * obj, int i);
    const GeneralType * (*cat)(const struct Vector_struct * obj, int i);
    int (*getSize)(const struct Vector_struct * obj);
    void (*pushBack)(struct Vector_struct * obj, const GeneralType* el);
    void (*pushBackRV)(struct Vector_struct * obj, GeneralType el);
    GeneralType * (*back)(struct Vector_struct * obj);
    void (*pushBackCalloced)(struct Vector_struct * obj, GeneralType * el);
    void (*popBack)(struct Vector_struct * obj);
    void (*resize)(struct Vector_struct * obj, int new_size);
};

typedef struct Vector_struct Vector;
typedef Vector VectorRef;

Vector defaultVector(int size, const GeneralType * def_value);
Vector defaultVectorRV(int size, GeneralType def_value);

Vector defaultVectorWithStrictSize(int size, const GeneralType * def_value);
Vector defaultVectorWithStrictSizeRV(int size, GeneralType def_value);

VectorRef wrapVector(const GeneralType * vec, int size);

Vector emptyVector();

Vector copyVector(const Vector * cop);
Vector moveVector(Vector * cop);
void destructVector(Vector * vec);

GeneralType * atVector(Vector * v, int i);
const GeneralType * catVector(const Vector * v, int i);

bool equalVector(const Vector * a, const Vector * b);

void popBackVector(Vector * a);

void pushBackVector(Vector * a, const GeneralType * val);
void pushBackVectorRV(Vector * a, GeneralType val);

int getSizeVector(const Vector * a);

void resizeVector(Vector * vec, int new_size);

void pushBackCallocedVector(Vector * vec, GeneralType * obj);

GeneralType * VectorDissolveIntoPointer(VectorRef * vec);

GeneralType * VectorBack(Vector * vec);

void sortVector(Vector * vec, int (*comparator)(const void *, const void *) );

DECLARE_STRUCT_TYPE(Vector, Vector)

#endif //FIBONACHY_NIM_VECTOR_GENERAL_TYPE_H
