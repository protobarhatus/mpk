#include <stdio.h>
#include "complex.h"

MyComplex defaultMyComplex(double a, double b)
{
    MyComplex res;
    res.a = a;
    res.b = b;
    return res;
}

void addToMyComplex(MyComplex * a, const MyComplex * b)
{
    a->a += b->a;
    a->b += b->b;
}

MyComplex addMyComplex(const MyComplex * a, const MyComplex * b)
{
    MyComplex res = copyMyComplex(a);
    addToMyComplex(&res, b);
    return res;
}

void subToMyComplex(MyComplex * a, const MyComplex * b)
{
    a->a -= b->a;
    a->b -= b->b;
}

MyComplex subMyComplex(const MyComplex * a, const MyComplex * b)
{
    MyComplex res = copyMyComplex(a);
    subToMyComplex(&res, b);
    return res;
}
//(a1 + b1 i)(a2 + b2 i) = a1*a2 + i(b1 a2 + b2 a1) - b1b2
MyComplex multMyComplex(const MyComplex * a, const MyComplex * b)
{

    return defaultMyComplex(a->a * b->a- a->b * b->b, a->b * b->a + a->a * b->b);
}

void multToMyComplex(MyComplex * a, const MyComplex * b)
{
    replaceMyComplex(a, multMyComplex(a, b));
}

// (a1 + b1 i )/(a2 + b2 i) = (a1 + b1 i)*(a2 - b2 i)/(a2 + b2 i)/(a2 - b2 i) = (a1*a2 + b1*b2 + i(b1*a2 - a1*b2)) / (a2^2 + b2^2)
MyComplex divMyComplex(const MyComplex * a, const MyComplex * b)
{
    double d = b->a * b->a + b->b * b->b;
    return defaultMyComplex((a->a * b->a + a->b * b->b) / d, (a->b * b->a - a->a * b->b) / d);
}
void divToMyComplex(MyComplex * a, const MyComplex * b)
{
    replaceMyComplex(a, divMyComplex(a, b));
}
MyComplex sqrtMyComplex(const MyComplex * a)
{
    assert(false);
    return defaultMyComplex(0, 0);
}
MyComplex minusMyComplex(const MyComplex * a)
{
    return defaultMyComplex(-a->a, -a->b);
}
MyComplex nullMyComplex()
{
    return defaultMyComplex(0, 0);
}
MyComplex unitMyComplex()
{
    return defaultMyComplex(1, 0);
}
MyComplex exponentMyComplex(const MyComplex * a)
{
    double real_mult = pow(euler, a->a);
    return defaultMyComplex(real_mult * cos(a->b), real_mult * sin(a->b));
}

void printfMyComplex(const MyComplex * com)
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

bool equalMyComplex(const MyComplex * a, const MyComplex * b)
{
    const double precision = 1e-3;
    return (fabs(a->a - b->a) <= precision) && (fabs(a->b - b->b) <= precision);
}

