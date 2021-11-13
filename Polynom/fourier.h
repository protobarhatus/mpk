#ifndef FIBONACHY_NIM_FOURIER_H
#define FIBONACHY_NIM_FOURIER_H

#include "polynom.h"
#include "vector/vector.h"

//now its on standart double complex
typedef VectorComplex DiscreteFourier;

DiscreteFourier discreteFourierTransformForPolynom(const Polynom * polynom);
DiscreteFourier naiveDiscreteFourierTransformForPolynom(const Polynom * polynom);
DiscreteFourier discreteFourierTransform(const VectorComplex * vec);
DiscreteFourier naiveDiscreteFourierTransform(const VectorComplex * vec);

complex double* dft(complex double const* arr, size_t len);
complex double* inverseDft(complex double const* arr, size_t len);

Polynom inverseFourierTransformForPolynom(const DiscreteFourier * fourier);
VectorComplex inverseFourierTransform(const DiscreteFourier * fourier);

bool equalDiscreteFourier(const DiscreteFourier * a, const DiscreteFourier * b);

void printfDiscreteFourier(const DiscreteFourier * fourier);



#endif //FIBONACHY_NIM_FOURIER_H
