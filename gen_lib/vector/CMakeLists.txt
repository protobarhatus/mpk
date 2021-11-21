cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_STANDARD 99)

#add_library(Vector STATIC Vector.c Vector.h vectordef.c vectordef.h vectorfuncs.c vectorfuncs.h)
set(VECTOR vector/arrayint.c
        vector/arrayint.h
        vector/Array2dInt.c
        vector/Array2dInt.h
        vector/vector.c
        vector/vector.h
        vector/algorithms.c
        vector/algorithms.h
        vector/sparse_vector.c
        vector/sparse_vector.h
        vector/vector_general_type.c
        vector/vector_general_type.h
        vector/vector_def.h
)
