#ifndef MPK_RATIONAL_H
#define MPK_RATIONAL_H
#include "../types_and_functions_declarations/type_declaration.h"
#include "../types_and_functions_declarations/arithmetic_type_declaration.h"
#include "../vector/vector.h"
#include "vector_algebraic_addendum_def.h"
#include "matrix.h"
#include "../types_and_functions_declarations/general_type.h"

struct Rational_struct
{
    long long int num, denom;
};
typedef struct Rational_struct Rational;
Rational defaultRational(long long int num, long long int denom);

DECLARE_SIMPLE_TYPE(Rational, Rational);

Rational nullRational();
Rational unitRational();
Rational minusOneRational();

Rational addRational(const Rational* a, const Rational* b);
Rational multRational(const Rational* a, const Rational* b);
Rational subRational(const Rational* a, const Rational* b);
Rational divRational(const Rational* a, const Rational * b);

void addToRational(Rational * a, const Rational * b);
void subToRational(Rational * a, const Rational * b);
void multToRational(Rational * a, const Rational * b);
void divToRational(Rational * a, const Rational * b);

Rational sqrtRational(const Rational * a);
Rational minusRational(const Rational * a);

void printfRational(const Rational * rat);
Rational scanfRational();

bool isNullRational(const Rational * rat);

GENERATE_RIGHT_VALUE_UNARY_EXTENSIONS(Rational, Rational, isNull, bool);

DECLARE_IO_TYPE(Rational, Rational);

bool isNull(const Rational * r);

DECLARE_TYPE_AS_ARITHMETIC(Rational, Rational);


MAKE_VECTOR(Rational, STRUCT);
MAKE_VECTOR(VectorRational, STRUCT);

#include "vector_algebraic_addendum.h"

MAKE_VECTOR_ALGEBRAIC_ADDENDUM(Rational)

MAKE_GENERAL_TYPE_TRANSLATION_FUNCTIONS(Rational, Rational)

MAKE_MATRIX(Rational, STRUCT);
#endif //MPK_RATIONAL_H
