cmake_minimum_required(VERSION 3.16)
project(mpk C)

set(CMAKE_C_STANDARD 11)

set(LINEAR_ALGEBRA
        linear_algebra_elements/matrix.h
        linear_algebra_elements/matrix_def.h
        linear_algebra_elements/vector_algebraic_addendum.h
        linear_algebra_elements/vector_algebraic_addendum_def.h
        linear_algebra_elements/vector_algebraic_addendum_general_type.h
        linear_algebra_elements/vector_algebraic_addendum_general_type.c
        linear_algebra_elements/rational.c
        linear_algebra_elements/rational.h
        linear_algebra_elements/complex.c
        linear_algebra_elements/complex.h
        linear_algebra_elements/matrix_general_type.h
        linear_algebra_elements/matrix_general_type.c)