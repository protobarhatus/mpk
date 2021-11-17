#ifndef FIBONACHY_NIM_FOURIER_H
#define FIBONACHY_NIM_FOURIER_H

#include "polynom.h"
#include "vector/vector.h"
/*this header presents functions for computing dft or inverse dft of sequence.
 * functions that dont have "naive" prefix use Cooley-Tookey algorithm.
 * if sequence length is not a power of two then in Cooley-Tookey algorithm it will be completed up to nearest power with zeroes
 * note that in that case result will differ from naive functions
 * */

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
