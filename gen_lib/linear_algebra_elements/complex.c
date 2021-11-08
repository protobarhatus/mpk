#include <stdio.h>
#include "complex.h"

Complex defaultComplex(double a, double b)
{
    Complex res;
    res.a = a;
    res.b = b;
    return res;
}

void addToComplex(Complex * a, const Complex * b)
{
    a->a += b->a;
    a->b += b->b;
}

Complex addComplex(const Complex * a, const Complex * b)
{
    Complex res = copyComplex(a);
    addToComplex(&res, b);
    return res;
}

void subToComplex(Complex * a, const Complex * b)
{
    a->a -= b->a;
    a->b -= b->b;
}

Complex subComplex(const Complex * a, const Complex * b)
{
    Complex res = copyComplex(a);
    subToComplex(&res, b);
    return res;
}
//(a1 + b1 i)(a2 + b2 i) = a1*a2 + i(b1 a2 + b2 a1) - b1b2
Complex multComplex(const Complex * a, const Complex * b)
{

    return defaultComplex(a->a * b->a- a->b * b->b, a->b * b->a + a->a * b->b);
}

void multToComplex(Complex * a, const Complex * b)
{
    replaceComplex(a, multComplex(a, b));
}

// (a1 + b1 i )/(a2 + b2 i) = (a1 + b1 i)*(a2 - b2 i)/(a2 + b2 i)/(a2 - b2 i) = (a1*a2 + b1*b2 + i(b1*a2 - a1*b2)) / (a2^2 + b2^2)
Complex divComplex(const Complex * a, const Complex * b)
{
    double d = b->a * b->a + b->b * b->b;
    return defaultComplex((a->a * b->a + a->b * b->b) / d, (a->b * b->a - a->a * b->b) / d);
}
void divToComplex(Complex * a, const Complex * b)
{
    replaceComplex(a, divComplex(a, b));
}
Complex sqrtComplex(const Complex * a)
{
    assert(false);
    return defaultComplex(0, 0);
}
Complex minusComplex(const Complex * a)
{
    return defaultComplex(-a->a, -a->b);
}
Complex nullComplex()
{
    return defaultComplex(0, 0);
}
Complex unitComplex()
{
    return defaultComplex(1, 0);
}
Complex exponentComplex(const Complex * a)
{
    double real_mult = pow(euler, a->a);
    return defaultComplex(real_mult * cos(a->b), real_mult * sin(a->b));
}
static bool equal(double a, double b)
{
    return fabs(a - b) <= 1e-15;
}
void printfComplex(const Complex * com)
{
    if (equal(com->a, 0) && equal(com->b, 0))
        printf("0 ");
    else if (equal(com->a, 0))
        printf("%f * i ", com->b);
    else if (equal(com->b, 0))
        printf("%f", com->a);
    else
        printf("%f + %f * i ", com->a, com->b);
}