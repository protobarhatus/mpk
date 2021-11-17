#include <stdio.h>
#include "vector/algorithms.h"
#include "fourier.h"
#include "math.h"
#define Pi M_PI
static DiscreteFourier insideNaiveDiscreteFourierTransform(const VectorComplex * polynom, int vec_start, int step, int N, bool inverse);
DiscreteFourier cooleyTukey(const VectorComplex * polynom, int vec_start, int step, int N, bool inverse);

static DiscreteFourier insideDiscreteFourierTransform(const VectorComplex * vec, int vec_start, int step,  int N, bool inverse)
{
    //really seems that it is the fastest
    if (N <= 2)
        return insideNaiveDiscreteFourierTransform(vec, vec_start, step, N, inverse);


    int next_pow = findNextPower(N);
    if (next_pow == N)
        return cooleyTukey(vec, vec_start, step, N, inverse);
    assert(vec_start == 0 && step == 1);
    VectorComplex counted_polynom = copyVectorComplex(vec);
    counted_polynom.resize(&counted_polynom, next_pow);
    for (int i = N; i < next_pow; ++i)
        *atVectorComplex(&counted_polynom, i) = 0;
    DiscreteFourier res = cooleyTukey(&counted_polynom, vec_start, step, next_pow, inverse);
    res.resize(&res, N);

    destructVectorComplex(&counted_polynom);
    return res;
}

static DiscreteFourier insideNaiveDiscreteFourierTransform(const VectorComplex * polynom, int vec_start, int step, int N, bool inverse)
{
    DiscreteFourier res = defaultVectorComplexCalloc(N, 0);
    double exp_mult = (inverse ? 1 : -1) * 2*Pi / N;
    for (int k = 0; k < N; ++k)
    {
        for (int n = 0; n < N; ++n)
        {
            *atVectorComplex(&res, k) += *catVectorComplex(polynom, vec_start + n * step) * cexp(exp_mult * k * n * I);
        }
    }
    return res;
}

DiscreteFourier cooleyTukey(const VectorComplex * polynom, int vec_start, int step, int N, bool inverse)
{
    assert(N % 2 == 0);
    int N_half = N / 2;
    VectorRefComplex e_polynom = *polynom;
    VectorRefComplex o_polynom = *polynom;
    DiscreteFourier E = insideDiscreteFourierTransform(&e_polynom, vec_start, step * 2, N_half, inverse),
                    O = insideDiscreteFourierTransform(&o_polynom, vec_start + step, step * 2, N_half, inverse);

    double exp_mult = (inverse ? 1 : -1) * 2*Pi / N;
    DiscreteFourier res = defaultVectorComplexCalloc(N, 0);
    for (int k = 0; k <N_half; ++k)
    {
        Complex O_multed = cexp(exp_mult * k * I) * *atVectorComplex(&O, k);

        *atVectorComplex(&res, k) = *atVectorComplex(&E, k) + O_multed;
        *atVectorComplex(&res, k + N_half) = *atVectorComplex(&E, k) - O_multed;

        destructComplex(&O_multed);
    }

    destructVectorComplex(&E);
    destructVectorComplex(&O);

    return res;
}



DiscreteFourier naiveDiscreteFourierTransformForPolynom(const Polynom * polynom)
{
    VectorComplex vec = defaultVectorComplexCalloc(polynom->deg + 1, 0);
    for (int i = 0; i < polynom->deg + 1; ++i)
        *atVectorComplex(&vec, i) = (double complex) *catPolynom(polynom, i);
    DiscreteFourier res = insideNaiveDiscreteFourierTransform(&vec, 0, 1, vectorComplexGetSize(&vec), false);

    destructVectorComplex(&vec);
    return res;
}
DiscreteFourier discreteFourierTransformForPolynom(const Polynom * polynom)
{
    VectorComplex vec = defaultVectorComplexCalloc(polynom->deg + 1, 0);
    for (int i = 0; i < polynom->deg + 1; ++i)
        *atVectorComplex(&vec, i) = (double complex) *catPolynom(polynom, i);

    DiscreteFourier res = insideDiscreteFourierTransform(&vec, 0, 1, vectorComplexGetSize(&vec), false);

    destructVectorComplex(&vec);
    return res;

}





bool equalDiscreteFourier(const DiscreteFourier * a, const DiscreteFourier * b)
{
    equal(1, 2);
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
        printf(" ");
    }
    printf("\n");
}

Polynom inverseFourierTransformForPolynom(const DiscreteFourier * fourier)
{
    int N = vectorComplexGetSize(fourier);
    int next_pow = findNextPower(N);
    if (next_pow != N)
    {
        DiscreteFourier cop = copyVectorComplex(fourier);
        cop.resize(&cop, next_pow);
        for (int i = N; i < next_pow; ++i)
            *atVectorComplex(&cop, i) = 0;
        Polynom res = inverseFourierTransformForPolynom(&cop);
        destructVectorComplex(&cop);
        return res;
    }
    Polynom res = defaultPolynom(fourier->getSize(fourier) - 1);
    DiscreteFourier inv_res = insideDiscreteFourierTransform(fourier, 0, 1, N, true);
    for (int i = 0; i < N; ++i)
    {
        //assert(equal(cimag(*atVectorComplex(&inv_res, i)), 0));
        *atPolynom(&res, i) = round(creal(*atVectorComplex(&inv_res, i)) / N);
    }
    destructVectorComplex(&inv_res);
    return res;
}
VectorComplex inverseFourierTransform(const DiscreteFourier * fourier)
{
    int N = vectorComplexGetSize(fourier);
    int next_pow = findNextPower(N);
    if (next_pow != N)
    {
        DiscreteFourier cop = copyVectorComplex(fourier);
        cop.resize(&cop, next_pow);
        for (int i = N; i < next_pow; ++i)
            *atVectorComplex(&cop, i) = 0;
        VectorComplex res = inverseFourierTransform(&cop);
        destructVectorComplex(&cop);
        return res;
    }
    DiscreteFourier res = insideDiscreteFourierTransform(fourier, 0, 1, N, true);
    for (int i = 0; i < N; ++i)
    {
        *atVectorComplex(&res, i) /= N;
    }
    return res;
}
DiscreteFourier discreteFourierTransform(const VectorComplex * vec)
{
    return insideDiscreteFourierTransform(vec, 0, 1, vectorComplexGetSize(vec), false);
}
DiscreteFourier naiveDiscreteFourierTransform(const VectorComplex * vec)
{
    return insideNaiveDiscreteFourierTransform(vec, 0, 1, vectorComplexGetSize(vec), false);
}

complex double* dft(complex double const* arr, size_t len)
{
    VectorRefComplex vec = wrapVectorComplex(arr, len);
    DiscreteFourier res = discreteFourierTransform(&vec);
    return vectorComplexDissolveIntoPointer(&res);
}
complex double* inverseDft(complex double const* arr, size_t len)
{
    VectorRefComplex vec = wrapVectorComplex(arr, len);
    DiscreteFourier res = inverseFourierTransform(&vec);
    return vectorComplexDissolveIntoPointer(&res);
}