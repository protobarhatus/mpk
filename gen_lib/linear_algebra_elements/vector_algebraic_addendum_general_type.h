#ifndef FIBONACHY_NIM_VECTOR_ALGEBRAIC_ADDENDUM_GENERAL_TYPE_H
#define FIBONACHY_NIM_VECTOR_ALGEBRAIC_ADDENDUM_GENERAL_TYPE_H
#include "../vector/vector.h"
#include "../types_and_functions_declarations/arithmetic_type_declaration.h"
#include "../types_and_functions_declarations/type_declaration.h"
#include "../types_and_functions_declarations/functions_extensions.h"
//to make vector algebra functions for type TN, need to declare its as type, as arithmetic_type and
//then generate functions here
//unfortunately, vector can not be declared as arithmetic type because it will have to define many unsutable for it functions
//and arithmetic of vector of vector is described in matrix and it differs.
void addToVector(Vector * dest, const Vector * b);
void subToVector(Vector * dest, const Vector * b);

Vector addVector(const Vector * a, const Vector * b);
Vector subVector(const Vector * a, const Vector * b);

void multVectorOnNum(Vector * dest, const GeneralType * el);
Vector VectorMultedOnNum(const Vector * vec, const void * el);

GeneralType scalarVector(const Vector * a, const Vector * b);

GeneralType lengthVector(const Vector * a);
GeneralType distanceVector(const Vector * a, const Vector * b);


GENERATE_RIGHT_VALUE_BINARY_EXTENSIONS(Vector, Vector, add, Vector)
GENERATE_RIGHT_VALUE_BINARY_EXTENSIONS(Vector, Vector, sub, Vector)
GENERATE_RIGHT_VALUE_BINARY_EXTENSIONS(Vector, Vector, scalar, GeneralType)
GENERATE_RIGHT_VALUE_BINARY_EXTENSIONS(Vector, Vector, distance, GeneralType)
GENERATE_RIGHT_VALUE_UNARY_EXTENSIONS(Vector, Vector, length, GeneralType)



#endif //FIBONACHY_NIM_VECTOR_ALGEBRAIC_ADDENDUM_GENERAL_TYPE_H
