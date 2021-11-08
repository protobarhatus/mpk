#include "fourier.h"
#define Pi 3.1415926536
DiscreteFourier naiveDiscreteFourierTransform(const Polynom * polynom)
{
    DiscreteFourier res = defaultVectorComplexCalloc(polynom->deg + 1, nullComplex());
    int N = polynom->deg + 1;
    for (int k = 0; k < polynom->deg + 1; ++k)
    {
        for (int n = 0; n < polynom->deg + 1; ++n)
        {
            addToComplexRV(atVectorComplex(&res, k),
                         multComplexRV(exponentComplexRV(defaultComplex(0, -2*Pi/N * k * n)),
                                       defaultComplex((double)*catPolynom(polynom, n), 0)));
        }
    }
    return res;
}

DiscreteFourier cooleyTukey(const Polynom * polynom)
{
    int N_half = (polynom->deg + 1) / 2;
    PolynomRef e_polynom = defaultSparcePolynomRef(N_half - 1, polynom->polynom, 2 * polynom->step);
    PolynomRef o_polynom = defaultSparcePolynomRef(N_half - 1, polynom->polynom + 1 * polynom->step, 2 * polynom->step);
    DiscreteFourier E = countDiscreteFourierTransform(&e_polynom),
                    O = countDiscreteFourierTransform(&o_polynom);

    double exp_mult = -2*Pi / (polynom->deg + 1);
    DiscreteFourier res = defaultVectorComplexCalloc(polynom->deg + 1, nullComplex());
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



const int powers_of_two[] = {
        1,
        2,
        4,
        8,
        16,
        32,
        64,
        128,
        256,
        512,
        1024,
        2048,
        4096,
        8192,
        16384,
        32768,
        65536,
        131072,
        262144,
        524288,
        1048576,
        2097152,
        4194304,
        8388608,
        16777216,
        33554432,
        67108864,
        134217728,
        268435456,
        536870912,
        1073741824
};
static int findNextPower(int n)
{
    //kinda no sense write binsearcn but just cut twice why not
    if (n > powers_of_two[15])
    {
        for (int i = 16; i <= 30; ++i)
            if (powers_of_two[i] >= n)
                return powers_of_two[i];
    }
    else if (n < powers_of_two[15])
    {
        for (int i = 0; i <= 14; ++i)
            if (powers_of_two[i] >= n)
                return powers_of_two[i];
    }
    return powers_of_two[15];
}
DiscreteFourier countDiscreteFourierTransform(const Polynom * polynom)
{
    assert(polynom->deg + 1 <= powers_of_two[30]);

    if (polynom->deg + 1 <= 2)
        return naiveDiscreteFourierTransform(polynom);


    int next_pow = findNextPower(polynom->deg + 1);
    if (next_pow == polynom->deg + 1)
        return cooleyTukey(polynom);

    Polynom counted_polynom = increasedPolynom(polynom, next_pow - 1);
    DiscreteFourier res = cooleyTukey(&counted_polynom);
    res.resize(&res, polynom->deg + 1);

    destructPolynom(&counted_polynom);
    return res;

}