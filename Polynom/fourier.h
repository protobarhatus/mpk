#ifndef FIBONACHY_NIM_FOURIER_H
#define FIBONACHY_NIM_FOURIER_H

#include "polynom.h"
#include "vector/vector.h"
#include "linear_algebra_elements/complex.h"

typedef VectorComplex DiscreteFourier;

DiscreteFourier countDiscreteFourierTransform(const Polynom * polynom);

#endif //FIBONACHY_NIM_FOURIER_H
