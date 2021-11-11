#include <stdio.h>
#include "vector/algorithms.h"
#include "fourier.h"
#define Pi M_PI
DiscreteFourier naiveDiscreteFourierTransform(const Polynom * polynom)
{
    int N = polynom->deg + 1;
    DiscreteFourier res = defaultVectorComplexCalloc(N, nullComplex());
    double exp_mult = -2*Pi / N;
    for (int k = 0; k < N; ++k)
    {
        for (int n = 0; n < N; ++n)
        {
            addToComplexRV(atVectorComplex(&res, k),
                         multComplexRV(exponentComplexRV(defaultComplex(0, exp_mult * k * n)),
                                       defaultComplex((double)*catPolynom(polynom, n), 0)));
        }
    }
    return res;
}

DiscreteFourier cooleyTukey(const Polynom * polynom)
{
    int N = polynom->deg + 1;
    assert(N % 2 == 0);
    int N_half = N / 2;
    PolynomRef e_polynom = defaultSparcePolynomRef(N_half - 1, polynom->polynom, 2 * polynom->step);
    PolynomRef o_polynom = defaultSparcePolynomRef(N_half - 1, polynom->polynom + 1 * polynom->step, 2 * polynom->step);
    DiscreteFourier E = countDiscreteFourierTransform(&e_polynom),
                    O = countDiscreteFourierTransform(&o_polynom);

    double exp_mult = -2*Pi / N;
    DiscreteFourier res = defaultVectorComplexCalloc(N, nullComplex());
    for (int k = 0; k <N_half; ++k)
    {
        Complex O_mult = exponentComplexRV(defaultComplex(0, exp_mult * k));

        *atVectorComplex(&res, k) = addComplexLVRV(atVectorComplex(&E, k),
                                                 multComplex(&O_mult, atVectorComplex(&O, k)));

        *atVectorComplex(&res, k + N_half) = subComplexLVRV(atVectorComplex(&E, k),
                                                            multComplex(&O_mult, atVectorComplex(&O, k)));

        destructComplex(&O_mult);
    }

    destructVectorComplex(&E);
    destructVectorComplex(&O);

    return res;

}




DiscreteFourier countDiscreteFourierTransform(const Polynom * polynom)
{
    int N = polynom->deg + 1;
    //really seems that it is the fastest
    if (N <= 2)
        return naiveDiscreteFourierTransform(polynom);


    int next_pow = findNextPower(N);
    if (next_pow == N)
        return cooleyTukey(polynom);

    Polynom counted_polynom = increasedPolynom(polynom, next_pow - 1);
    DiscreteFourier res = cooleyTukey(&counted_polynom);
    res.resize(&res, N);

    destructPolynom(&counted_polynom);
    return res;

}

bool equalDiscreteFourier(const DiscreteFourier * a, const DiscreteFourier * b)
{

    if (vectorComplexGetSize(a) != vectorComplexGetSize(b))
        return false;
    for (int i = 0; i < vectorComplexGetSize(a); ++i)
        if (!equalComplex(catVectorComplex(a, i), catVectorComplex(b, i)))
            return false;

    return true;
}

void printfDiscreteFourier(const DiscreteFourier * fourier)
{
    for (int i = 0; i < fourier->getSize(fourier); ++i)
    {
        printfComplex(catVectorComplex(fourier, i));
        printf("; ");
    }
    printf("\n");
}