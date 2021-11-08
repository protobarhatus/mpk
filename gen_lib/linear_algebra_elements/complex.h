#ifndef FIBONACHY_NIM_COMPLEX_H
#define FIBONACHY_NIM_COMPLEX_H
#include "../types_and_functions_declarations/type_declaration.h"
#include "../types_and_functions_declarations/arithmetic_type_declaration.h"
#include "../vector/vector.h"
#include "vector_algebraic_addendum.h"

#define euler 2.718281828

struct Complex_struct
{
    double a, b;
};
typedef struct Complex_struct Complex;

Complex defaultComplex(double a, double b);

DECLARE_SIMPLE_TYPE(Complex, Complex);

void addToComplex(Complex * a, const Complex * b);
Complex addComplex(const Complex * a, const Complex * b);
void subToComplex(Complex * a, const Complex * b);
Complex subComplex(const Complex * a, const Complex * b);
Complex multComplex(const Complex * a, const Complex * b);
void multToComplex(Complex * a, const Complex * b);
Complex divComplex(const Complex * a, const Complex * b);
void divToComplex(Complex * a, const Complex * b);
//since complex have two indistinguishable roots, that function is invalid (need to arithm declaration)
Complex sqrtComplex(const Complex * a);
Complex minusComplex(const Complex * a);
Complex nullComplex();
Complex unitComplex();

void printfComplex(const Complex * com);

DECLARE_TYPE_AS_ARITHMETIC(Complex, Complex);
MAKE_VECTOR(Complex, Complex)

MAKE_VECTOR_ALGEBRAIC_ADDENDUM(Complex, Complex);

Complex exponentComplex(const Complex * a);

GENERATE_RIGHT_VALUE_UNARY_EXTENSIONS(Complex, Complex, exponent, Complex);


#endif //FIBONACHY_NIM_COMPLEX_H
