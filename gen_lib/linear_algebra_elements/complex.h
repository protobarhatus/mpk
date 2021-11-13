#ifndef FIBONACHY_NIM_COMPLEX_H
#define FIBONACHY_NIM_COMPLEX_H
#include "../types_and_functions_declarations/type_declaration.h"
#include "../types_and_functions_declarations/arithmetic_type_declaration.h"
#include "../vector/vector.h"
#include "vector_algebraic_addendum.h"

#define euler 2.718281828
//turned out that complex.h exist. don't wanna delete this maybe will be useful  one day
struct MyComplex_struct
{
    double a, b;
};
typedef struct MyComplex_struct MyComplex;

MyComplex defaultMyComplex(double a, double b);

DECLARE_SIMPLE_TYPE(MyComplex, MyComplex);

void addToMyComplex(MyComplex * a, const MyComplex * b);
MyComplex addMyComplex(const MyComplex * a, const MyComplex * b);
void subToMyComplex(MyComplex * a, const MyComplex * b);
MyComplex subMyComplex(const MyComplex * a, const MyComplex * b);
MyComplex multMyComplex(const MyComplex * a, const MyComplex * b);
void multToMyComplex(MyComplex * a, const MyComplex * b);
MyComplex divMyComplex(const MyComplex * a, const MyComplex * b);
void divToMyComplex(MyComplex * a, const MyComplex * b);
//since complex have two indistinguishable roots, that function is invalid (need to arithm declaration)
MyComplex sqrtMyComplex(const MyComplex * a);
MyComplex minusMyComplex(const MyComplex * a);
MyComplex nullMyComplex();
MyComplex unitMyComplex();

void printfMyComplex(const MyComplex * com);



bool equalMyComplex(const MyComplex * a, const MyComplex * b);

GENERATE_RIGHT_VALUE_BINARY_EXTENSIONS(MyComplex, MyComplex, equal, bool)

DECLARE_TYPE_AS_ARITHMETIC(MyComplex, MyComplex);
MAKE_VECTOR(MyComplex, MyComplex)

MAKE_VECTOR_ALGEBRAIC_ADDENDUM(MyComplex, MyComplex);

MyComplex exponentMyComplex(const MyComplex * a);

GENERATE_RIGHT_VALUE_UNARY_EXTENSIONS(MyComplex, MyComplex, exponent, MyComplex);


#endif //FIBONACHY_NIM_COMPLEX_H
