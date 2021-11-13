#ifndef MPK_POLYNOM_H
#define MPK_POLYNOM_H

#include <stdbool.h>
#include <string.h>
#include <bits/types/FILE.h>
#include "../gen_lib/vector/vector.h"
#include "../gen_lib/types_and_functions_declarations/functions_extensions.h"

struct Polynom_struct
{
    int deg;
    long long int * polynom;
};
typedef struct Polynom_struct Polynom;
typedef struct Polynom_struct PolynomRef;



static inline long long int * atPolynom(Polynom * a, int i)
{
    assert(i >= 0 && i <= a->deg);
    return &a->polynom[i ];
}
static inline const long long int * catPolynom(const Polynom * a, int i)
{
    assert(i >= 0 && i <= a->deg);
    return &a->polynom[i ];
}

//thats needed for mpk lvl 1, for other levels i prefer do it with macro
struct PairPolynom_struct
{
    PolynomRef first, second;
};
typedef struct PairPolynom_struct PairPolynom;

PairPolynom defaultPairPolynom(Polynom * a, Polynom * b);

PairPolynom splitPolynomOnXInDeg(const Polynom * p, int x_deg);
Polynom simpleMult(const Polynom * a, const Polynom * b);
void simpleMultOnBuff(Polynom * res, const Polynom * a, const Polynom * b);
void addShiftedOnBuff(Polynom * buff, const Polynom * a, int shift_a, const Polynom * b, int shift_b);

Polynom defaultPolynom(int deg);
//Polynom defaultSparcePolynomRef(int deg, void * start, int step);
//this sorta like standart constructor, that makes absolutely no callocs
Polynom emptyPolynom();
Polynom movePolynom(Polynom * pol);

Polynom multPolynom(const Polynom * ap, const Polynom * bp);

typedef Polynom PolynomRef;

void destructPolynom(Polynom * obj);

void shrinkLeadZeroez(Polynom * p);

void addToPolynom(Polynom * a, const Polynom * b);

Polynom copyPolynom(const Polynom * a);

Polynom addPolynom(const Polynom * a, const Polynom * b);

Polynom addRV(Polynom a, Polynom b);

void cumulativeMultOnNum(Polynom * a, int n);

Polynom multOnNum(const Polynom * a, long long int k);

void cumulativeSubtract(Polynom * a, const Polynom * b);

Polynom subtract(const Polynom * a, const Polynom * b);

Polynom subtractRV(Polynom a, Polynom b);

bool isZeroPolynom(const Polynom * a);

Polynom getZeroPolynom();

bool isUnitPolynom(const Polynom * a);


bool isPolynomConstantNumber(const Polynom * p);

long long int polynomToConstantNumber(const Polynom * p);

Polynom getXInDegPolynom(int deg);

Polynom getXInDegPolynomMult(const Polynom * a, const Polynom * b);

Polynom toomCookMultiplication(const Polynom * a, const Polynom * b);

void printfPolynom(const Polynom * p);
Polynom scanfPolynom(FILE *input);
bool areEqualPolynom(const Polynom * a, const Polynom * b);

Polynom karatsuba(const Polynom * ap, const Polynom * bp);

void testPolynoms(FILE * input, Polynom (*mult_function)(const Polynom * a, const Polynom * b));

bool * isForbidToomCook();
void forbidToomCook();
void allowToomCook();

Polynom increasedPolynom(const Polynom * pol, int new_deg);


Polynom randPolynom(int size);
Polynom scanfRandPolynom(int len);

Polynom schonhageStrassenAlgorithm(const Polynom * a, const Polynom * b);

//thus, vector will contain Polynom as objects, but will not destruct them and that will allow
//me make a split on single polynom buf
DECLARE_SIMPLE_TYPE(PolynomRef, PolynomRef)
MAKE_VECTOR(PolynomRef, PolynomRef);

DECLARE_STRUCT_TYPE(Polynom, Polynom)
MAKE_VECTOR(Polynom, Polynom)

GENERATE_RIGHT_VALUE_BINARY_EXTENSIONS(Polynom, Polynom, mult, Polynom)
GENERATE_RIGHT_VALUE_BINARY_EXTENSIONS(Polynom, Polynom, areEqual, bool);


#endif //MPK_POLYNOM_H
