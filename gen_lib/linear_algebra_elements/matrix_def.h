#ifndef MATRIX_DEF_H
#define MATRIX_DEF_H

#include "../vector/vector.h"
#include "../types_and_functions_declarations/general_type.h"
#include <stdio.h>
#include <stdarg.h>
#include "matrix_general_type.h"
#include "../vector/algorithms.h"
#include "vector_algebraic_addendum.h"
#define MAKE_MATRIX(UCN, ARITHM_TYPE) \
                                                                                                                                                  \
                                                                                                                                                  \
                                                                                                                                                  \
                                                                                                                                                  \
struct Matrix##UCN##_struct {                                                                                                                     \
                                                                                                                                                  \
    VectorVector##UCN matrix;                                                                                                                     \
    int lines, columns;                                                                                                                           \
    Vector##UCN * (*at)(struct Matrix##UCN##_struct * a, int i);                                                                                  \
                                                                                                                                                  \
    bool is_on_buffer;                                                                                                                            \
    /*its for matrix that is build on buffer. allocked_* means from its current start till end without considering allocked space behind*/        \
    int start_line, start_column, allocked_lines, allocked_columns;                                                                               \
    /*thats made only in non buffered matrix*/                                                                                                    \
    UCN value_beyond_allocked_space;                                                                                                              \
    /*thats for buffered matrix. reason is that for buffered matrixes it is preferable to be Ref, but Ref*/                                       \
    /*dont require destructor*/                                                                                                                   \
    const UCN * value_beyond_allocked_space_ptr;                                                                                                  \
                                                                                                                                                  \
};                                                                                                                                                \
                                                                                                                                                  \
                                                                                                                                                  \
                                                                                                                                                  \
typedef struct Matrix##UCN##_struct Matrix##UCN;                                                                                                  \
typedef Matrix##UCN MatrixRef##UCN;                                                                                                               \
                                                                                                                                                  \
static inline Matrix##UCN defaultMatrix##UCN(int lines, int columns, UCN def_value);                                                              \
static inline Matrix##UCN makeUnitMatrix##UCN(int n);                                                                                             \
                                                                                                                                                  \
static inline Matrix##UCN copyMatrix##UCN(const Matrix##UCN * mat);                                                                               \
static inline Matrix##UCN moveMatrix##UCN(Matrix##UCN * mat);                                                                                     \
static inline void destructMatrix##UCN(Matrix##UCN * mat);                                                                                        \
static inline bool equalMatrix##UCN(const Matrix##UCN * a, const Matrix##UCN * b);                                                                \
                                                                                                                                                  \
DECLARE_STRUCT_TYPE(Matrix##UCN, Matrix##UCN);                                                                                                    \
                                                                                                                                                  \
static inline MatrixRef##UCN getMatrix##UCN##OnBuffer(const Matrix##UCN * origin, int lines_start, int lines_finish, int lines, int columns);     \
                                                                                                                                                  \
static inline void addToMatrix##UCN(Matrix##UCN * a, const Matrix##UCN * b);                                                                      \
static inline void subToMatrix##UCN(Matrix##UCN * a, const Matrix##UCN * b);                                                                      \
                                                                                                                                                  \
                                                                                                                                                  \
                                                                                                                                                  \
static inline Matrix##UCN addMatrix##UCN(const Matrix##UCN * a, const Matrix##UCN * b);                                                           \
static inline Matrix##UCN subMatrix##UCN(const Matrix##UCN * a, const Matrix##UCN * b);                                                           \
                                                                                                                                                  \
static inline Matrix##UCN multMatrix##UCN(const Matrix##UCN * a, const Matrix##UCN * b);                                                          \
static inline Matrix##UCN divMatrix##UCN(const Matrix##UCN * a, const Matrix##UCN * b);                                                           \
static inline void multToMatrix##UCN(Matrix##UCN * a, const Matrix##UCN * b);                                                                     \
static inline void divToMatrix##UCN(Matrix##UCN * a, const Matrix##UCN * b);                                                                      \
                                                                                                                                                  \
static inline Matrix##UCN unitMatrix##UCN();                                                                                                      \
static inline Matrix##UCN nullMatrix##UCN();                                                                                                      \
                                                                                                                                                  \
static inline Matrix##UCN minusMatrix##UCN(const Matrix##UCN * a);                                                                                \
static inline Matrix##UCN sqrtMatrix##UCN(const Matrix##UCN * a);                                                                                 \
                                                                                                                                                  \
DECLARE_TYPE_AS_ARITHMETIC(Matrix##UCN, Matrix##UCN);                                                                                             \
                                                                                                                                                  \
                                                                                                                                                  \
                                                                                                                                                  \
static inline Vector##UCN * atMatrix##UCN(Matrix##UCN * mat, int i)                                                                               \
{                                                                                                                                                 \
    assert(!mat->is_on_buffer);                                                                                                                   \
    return atVectorVector##UCN(&mat->matrix, i);                                                                                                  \
}                                                                                                                                                 \
static inline const Vector##UCN * catMatrix##UCN(const Matrix##UCN * mat, int i)                                                                  \
{                                                                                                                                                 \
    assert(!mat->is_on_buffer);                                                                                                                   \
    return catVectorVector##UCN(&mat->matrix, i);                                                                                                 \
}                                                                                                                                                 \
                                                                                                                                                  \
                                                                                                                                                  \
static inline UCN * atMatrix##UCN##El(Matrix##UCN * mat, int i, int j)                                                                            \
{                                                                                                                                                 \
    if (mat->is_on_buffer)                                                                                                                        \
    {                                                                                                                                             \
        assert (i < mat->allocked_lines && j < mat->allocked_columns);                                                                            \
        return  atVector##UCN(atVectorVector##UCN(&mat->matrix, i + mat->start_line), j + mat->start_column);                                     \
    }                                                                                                                                             \
    assert(i < mat->lines && j < mat->columns);                                                                                                   \
    return &mat->matrix.vec[i].vec[j];                                                                                                            \
    return atVector##UCN(atVectorVector##UCN(&mat->matrix, i), j);                                                                                \
}                                                                                                                                                 \
static inline const UCN * catMatrix##UCN##El(const Matrix##UCN * mat, int i, int j)                                                               \
{                                                                                                                                                 \
    if (mat->is_on_buffer)                                                                                                                        \
    {                                                                                                                                             \
        if (i >= mat->allocked_lines || j >= mat->allocked_columns)                                                                               \
            return mat->value_beyond_allocked_space_ptr;                                                                                          \
        return  catVector##UCN(catVectorVector##UCN(&mat->matrix, i + mat->start_line), j + mat->start_column);                                   \
    }                                                                                                                                             \
    assert(i < mat->lines && j < mat->columns);                                                                                                   \
    return &mat->matrix.vec[i].vec[j];                                                                                                            \
    return catVector##UCN(catVectorVector##UCN(&mat->matrix, i), j);                                                                              \
}                                                                                                                                                 \
static inline void setValueToMatrix##UCN(Matrix##UCN * mat, int i, int j, UCN value)                                                              \
{                                                                                                                                                 \
    if (mat->is_on_buffer)                                                                                                                        \
    {                                                                                                                                             \
        if (i >= mat->allocked_lines || j >= mat->allocked_columns)                                                                               \
            return;                                                                                                                               \
    }                                                                                                                                             \
    replace##UCN(atMatrix##UCN##El(mat, i, j) , move##UCN(&value));                                                                               \
}                                                                                                                                                 \
                                                                                                                                                  \
static inline Matrix##UCN scanfMatrix##UCN();                                                                                                     \
                                                                                                                                                  \
static inline Matrix##UCN inverseMatrix##UCN(Matrix##UCN * matrix);                                                                               \
                                                                                                                                                  \
GENERATE_RIGHT_VALUE_UNARY_EXTENSIONS(Matrix##UCN, Matrix##UCN, inverse, Matrix##UCN);                                                            \
static inline void printfMatrix##UCN(const Matrix##UCN * mat);                                                                                    \
                                                                                                                                                  \
GENERATE_RIGHT_VALUE_UNARY_EXTENSIONS_TO_VOID_FUNC(Matrix##UCN, Matrix##UCN, printf)                                                              \
                                                                                                                                                  \
                                                                                                                                                  \
static inline Matrix##UCN naiveMultMatrix##UCN(const Matrix##UCN * a, const Matrix##UCN * b);                                                     \
                                                                                                                                                  \
                                                                                                                                                  \
                                                                                                                                                  \
                                                                                                                                                  \
                                                                                                                                                  \
                                                                                                                                                                 \
                                                                                                                                                                 \
                                                                                                                                                                 \
                                                                                                                                                                 \
                                                                                                                                                                 \
                                                                                                                                                                 \
static inline void assignFunctionsMatrix##UCN(Matrix##UCN * mat)                                                                                                 \
{                                                                                                                                                                \
    mat->at = &atMatrix##UCN;                                                                                                                                    \
}                                                                                                                                                                \
                                                                                                                                                                 \
static inline Matrix##UCN defaultMatrix##UCN(int lines, int columns, UCN def_value)                                                                              \
{                                                                                                                                                                \
    Matrix##UCN result;                                                                                                                                          \
    result.lines = lines;                                                                                                                                        \
    result.columns = columns;                                                                                                                                    \
    /*here def_value is destroyed so dont have to call destructor*/                                                                                              \
    result.matrix = defaultVectorVector##UCN##RV(lines, defaultVector##UCN##RV(columns, def_value));                                                             \
    assignFunctionsMatrix##UCN(&result);                                                                                                                         \
                                                                                                                                                                 \
    result.start_line = 0;                                                                                                                                       \
    result.start_column = 0;                                                                                                                                     \
    result.allocked_lines = result.lines;                                                                                                                        \
    result.allocked_columns = result.columns;                                                                                                                    \
    result.is_on_buffer = false;                                                                                                                                 \
    result.value_beyond_allocked_space = null##UCN();                                                                                                            \
    result.value_beyond_allocked_space_ptr = NULL;                                                                                                               \
    return result;                                                                                                                                               \
}                                                                                                                                                                \
                                                                                                                                                                 \
static inline Matrix##UCN makeUnitMatrix##UCN(int n)                                                                                                             \
{                                                                                                                                                                \
    Matrix##UCN res;                                                                                                                                             \
    res.lines = n;                                                                                                                                               \
    res.columns = n;                                                                                                                                             \
    res.matrix = defaultVectorVector##UCN##RV(n, defaultVector##UCN##RV(n, null##UCN()));                                                                        \
    for (int i = 0; i < n; ++i)                                                                                                                                  \
        *atMatrix##UCN##El(&res, i, i) = unit##UCN();                                                                                                            \
                                                                                                                                                                 \
    res.start_line = 0;                                                                                                                                          \
    res.start_column = 0;                                                                                                                                        \
    res.allocked_lines = res.lines;                                                                                                                              \
    res.allocked_columns = res.columns;                                                                                                                          \
    res.is_on_buffer = false;                                                                                                                                    \
    assignFunctionsMatrix##UCN(&res);                                                                                                                            \
    return res;                                                                                                                                                  \
}                                                                                                                                                                \
static inline Matrix##UCN copyMatrix##UCN(const Matrix##UCN * mat)                                                                                               \
{                                                                                                                                                                \
    assert(!mat->is_on_buffer);                                                                                                                                  \
    Matrix##UCN res;                                                                                                                                             \
                                                                                                                                                                 \
    res.lines = mat->lines;                                                                                                                                      \
    res.columns = mat->columns;                                                                                                                                  \
    res.matrix = copyVectorVector##UCN(&mat->matrix);                                                                                                            \
    res.is_on_buffer = false;                                                                                                                                    \
    res.allocked_lines = mat->allocked_lines;                                                                                                                    \
    res.start_column = mat->start_column;                                                                                                                        \
    res.start_line = mat->start_line;                                                                                                                            \
    res.allocked_columns = mat->allocked_columns;                                                                                                                \
    res.value_beyond_allocked_space = copy##UCN(&mat->value_beyond_allocked_space);                                                                              \
    res.value_beyond_allocked_space_ptr = mat->value_beyond_allocked_space_ptr;                                                                                  \
                                                                                                                                                                 \
    assignFunctionsMatrix##UCN(&res);                                                                                                                            \
    return res;                                                                                                                                                  \
}                                                                                                                                                                \
static inline Matrix##UCN moveMatrix##UCN(Matrix##UCN * mat)                                                                                                     \
{                                                                                                                                                                \
    Matrix##UCN res;                                                                                                                                             \
                                                                                                                                                                 \
    res.lines = mat->lines;                                                                                                                                      \
    res.columns = mat->columns;                                                                                                                                  \
    res.matrix = moveVectorVector##UCN(&mat->matrix);                                                                                                            \
    res.is_on_buffer = mat->is_on_buffer;                                                                                                                        \
    res.allocked_lines = mat->allocked_lines;                                                                                                                    \
    res.start_column = mat->start_column;                                                                                                                        \
    res.start_line = mat->start_line;                                                                                                                            \
    res.allocked_columns = mat->allocked_columns;                                                                                                                \
    res.value_beyond_allocked_space = move##UCN(&mat->value_beyond_allocked_space);                                                                              \
    res.value_beyond_allocked_space_ptr = mat->value_beyond_allocked_space_ptr;                                                                                  \
                                                                                                                                                                 \
    mat->lines = -1;                                                                                                                                             \
    mat->columns = -1;                                                                                                                                           \
    assignFunctionsMatrix##UCN(&res);                                                                                                                            \
    return res;                                                                                                                                                  \
}                                                                                                                                                                \
                                                                                                                                                                 \
static inline bool equalMatrix##UCN(const Matrix##UCN * a, const Matrix##UCN * b)                                                                                \
{                                                                                                                                                                \
    if (a->lines != b->lines || a->columns != b->columns)                                                                                                        \
        return false;                                                                                                                                            \
    for (int i = 0; i < a->lines; ++i)                                                                                                                           \
    {                                                                                                                                                            \
        for (int j = 0; j < a->columns; ++j)                                                                                                                     \
        {                                                                                                                                                        \
            if (!equal##UCN(catMatrix##UCN##El(a, i, j), catMatrix##UCN##El(b, i, j)))                                                                           \
                return false;                                                                                                                                    \
        }                                                                                                                                                        \
    }                                                                                                                                                            \
    return true;                                                                                                                                                 \
}                                                                                                                                                                \
static inline void destructMatrix##UCN(Matrix##UCN * mat)                                                                                                        \
{                                                                                                                                                                \
    if (mat->is_on_buffer)                                                                                                                                       \
    {                                                                                                                                                            \
        return;                                                                                                                                                  \
    }                                                                                                                                                            \
    destructVectorVector##UCN(&mat->matrix);                                                                                                                     \
    destruct##UCN(&mat->value_beyond_allocked_space);                                                                                                            \
}                                                                                                                                                                \
                                                                                                                                                                 \
static inline MatrixRef##UCN getMatrix##UCN##OnBuffer(const Matrix##UCN * origin, int lines_start, int columns_start, int lines, int columns)                    \
{                                                                                                                                                                \
    MatrixRef##UCN res;                                                                                                                                          \
                                                                                                                                                                 \
    res.matrix = origin->matrix;                                                                                                                                 \
    res.lines = lines;                                                                                                                                           \
    res.columns = columns;                                                                                                                                       \
    res.is_on_buffer = true;                                                                                                                                     \
    res.start_line = origin->start_line + lines_start;                                                                                                           \
    res.start_column = origin->start_column + columns_start;                                                                                                     \
    res.allocked_lines = origin->allocked_lines - lines_start;                                                                                                   \
    res.allocked_columns = origin->allocked_columns - columns_start;                                                                                             \
    if (origin->is_on_buffer)                                                                                                                                    \
        res.value_beyond_allocked_space_ptr = origin->value_beyond_allocked_space_ptr;                                                                           \
    else                                                                                                                                                         \
        res.value_beyond_allocked_space_ptr = &origin->value_beyond_allocked_space;                                                                              \
                                                                                                                                                                 \
    assignFunctionsMatrix##UCN(&res);                                                                                                                            \
    return res;                                                                                                                                                  \
}                                                                                                                                                                \
                                                                                                                                                                 \
static inline void addToMatrix##UCN(Matrix##UCN * a, const Matrix##UCN * b)                                                                                      \
{                                                                                                                                                                \
                                                                                                                                                                 \
    assert(a->lines <= b->lines && a->columns <= b->columns);                                                                                                    \
    for (int i = 0; i < a->lines; ++i)                                                                                                                           \
    {                                                                                                                                                            \
        for (int j = 0; j < a->columns; ++j)                                                                                                                     \
            if (!a->is_on_buffer || (i < a->allocked_lines && j < a->allocked_columns))                                                                          \
                ARITHM_TYPE##_TYPE_ADD_TO(UCN, atMatrix##UCN##El(a, i, j), catMatrix##UCN##El(b, i, j));                                                         \
    }                                                                                                                                                            \
                                                                                                                                                                 \
}                                                                                                                                                                \
static inline Matrix##UCN addMatrix##UCN(const Matrix##UCN * a, const Matrix##UCN * b)                                                                           \
{                                                                                                                                                                \
                                                                                                                                                                 \
    assert(a->lines == b->lines && a->columns == b->columns);                                                                                                    \
    Matrix##UCN res = defaultMatrix##UCN(a->lines, a->columns, null##UCN());                                                                                     \
    addToMatrix##UCN(&res, a);                                                                                                                                   \
    addToMatrix##UCN(&res, b);                                                                                                                                   \
    return res;                                                                                                                                                  \
}                                                                                                                                                                \
static inline void subToMatrix##UCN(Matrix##UCN * a, const Matrix##UCN * b)                                                                                      \
{                                                                                                                                                                \
                                                                                                                                                                 \
    assert(a->lines <= b->lines && a->columns <= b->columns);                                                                                                    \
    for (int i = 0; i < a->lines; ++i)                                                                                                                           \
    {                                                                                                                                                            \
        for (int j = 0; j < a->columns; ++j)                                                                                                                     \
        {                                                                                                                                                        \
            if (!a->is_on_buffer || (i < a->allocked_lines && j < a->allocked_columns))                                                                          \
                ARITHM_TYPE##_TYPE_SUB_TO(UCN, atMatrix##UCN##El(a, i, j), catMatrix##UCN##El(b, i, j));                                                         \
        }                                                                                                                                                        \
    }                                                                                                                                                            \
}                                                                                                                                                                \
static inline Matrix##UCN subMatrix##UCN(const Matrix##UCN * a, const Matrix##UCN * b)                                                                           \
{                                                                                                                                                                \
                                                                                                                                                                 \
    assert(a->lines == b->lines && a->columns == b->columns);                                                                                                    \
    Matrix##UCN res = defaultMatrix##UCN(a->lines, a->columns, null##UCN());                                                                                     \
    /*cannot just make copy because matrixes may be on buffer and now thats assert*/                                                                             \
    addToMatrix##UCN(&res, a);                                                                                                                                   \
    subToMatrix##UCN(&res, b);                                                                                                                                   \
    return res;                                                                                                                                                  \
}                                                                                                                                                                \
/*unsafe if call explicitly from outside*/                                                                                                                       \
static inline Matrix##UCN naiveMultMatrix##UCN(const Matrix##UCN * a, const Matrix##UCN * b)                                                                     \
{                                                                                                                                                                \
    Matrix##UCN res = defaultMatrix##UCN(a->lines, b->columns, null##UCN());                                                                                     \
    int a_lines = min(a->lines, a->allocked_lines);                                                                                                              \
    int b_columns = min(b->columns, b->allocked_columns);                                                                                                        \
    int m_columns = min(min(a->columns, a->allocked_columns), min(b->lines, b->allocked_lines));                                                                 \
    for (int i = 0; i < a_lines; ++i)                                                                                                                            \
    {                                                                                                                                                            \
        for (int j = 0; j < b_columns; ++j)                                                                                                                      \
        {                                                                                                                                                        \
            for (int k = 0; k < m_columns; ++k)                                                                                                                  \
                /*ARITHM_TYPE##_TYPE_ADD_TO_RV(UCN, atMatrix##UCN##El(&res, i, j),*/                                                                             \
                  /*                 ARITHM_TYPE##_TYPE_MULT(UCN, catMatrix##UCN##El(a, i, k), catMatrix##UCN##El(b, k, j)));*/                                  \
                ARITHM_TYPE##_TYPE_ADD_TO_RV(UCN, &res.matrix.vec[i].vec[j],                                                                                     \
                                   ARITHM_TYPE##_TYPE_MULT(UCN, &a->matrix.vec[i + a->start_line].vec[k + a->start_column],                                      \
                                                   &b->matrix.vec[k + b->start_line].vec[j + b->start_column]));                                                 \
        }                                                                                                                                                        \
    }                                                                                                                                                            \
    return res;                                                                                                                                                  \
}                                                                                                                                                                \
static inline Matrix##UCN multMatrix##UCN##RV(Matrix##UCN a, Matrix##UCN b);                                                                                     \
                                                                                                                                                                 \
static inline Matrix##UCN* addMatrix##UCN##OnBuff(Matrix##UCN* buff, const Matrix##UCN * a, const Matrix##UCN * b)                                               \
{                                                                                                                                                                \
    for (int i = 0; i < buff->lines; ++i)                                                                                                                        \
    {                                                                                                                                                            \
        for (int j = 0; j < buff->columns; ++j)                                                                                                                  \
            replace##UCN(atMatrix##UCN##El(buff, i, j), ARITHM_TYPE##_TYPE_ADD(UCN, catMatrix##UCN##El(a, i, j), catMatrix##UCN##El(b, i, j)));                  \
    }                                                                                                                                                            \
    return buff;                                                                                                                                                 \
}                                                                                                                                                                \
static inline Matrix##UCN* subMatrix##UCN##OnBuff(Matrix##UCN* buff, const Matrix##UCN * a, const Matrix##UCN * b)                                               \
{                                                                                                                                                                \
    for (int i = 0; i < buff->lines; ++i)                                                                                                                        \
    {                                                                                                                                                            \
        for (int j = 0; j < buff->columns; ++j)                                                                                                                  \
        {                                                                                                                                                        \
            replace##UCN(atMatrix##UCN##El(buff, i, j), ARITHM_TYPE##_TYPE_SUB(UCN, catMatrix##UCN##El(a, i, j), catMatrix##UCN##El(b, i, j)));                  \
        }                                                                                                                                                        \
    }                                                                                                                                                            \
    return buff;                                                                                                                                                 \
}                                                                                                                                                                \
                                                                                                                                                                 \
static inline void chainAddingOrSubtractionToMatrix##UCN(Matrix##UCN * mat, ...)                                                                                 \
{                                                                                                                                                                \
    va_list arg;                                                                                                                                                 \
    va_start(arg, mat);                                                                                                                                          \
    Sign next_sign;                                                                                                                                              \
    while ((next_sign = va_arg(arg, Sign)) != STOP)                                                                                                              \
    {                                                                                                                                                            \
        if (next_sign == PLUS)                                                                                                                                   \
            addToMatrix##UCN(mat, va_arg(arg, const Matrix##UCN *));                                                                                             \
        else                                                                                                                                                     \
            subToMatrix##UCN(mat, va_arg(arg, const Matrix##UCN *));                                                                                             \
    }                                                                                                                                                            \
    va_end(arg);                                                                                                                                                 \
}                                                                                                                                                                \
                                                                                                                                                                 \
static inline Matrix##UCN scanfMatrix##UCN()                                                                                                                     \
{                                                                                                                                                                \
    int len = scanfInt(), col = scanfInt();                                                                                                                      \
    Matrix##UCN res = defaultMatrix##UCN(len, col, null##UCN());                                                                                                 \
    for (int i = 0; i < len; ++i)                                                                                                                                \
    {                                                                                                                                                            \
        for (int j = 0; j < col; ++j)                                                                                                                            \
        {                                                                                                                                                        \
            replace##UCN(atMatrix##UCN##El(&res, i, j), scanf##UCN());                                                                                           \
        }                                                                                                                                                        \
    }                                                                                                                                                            \
    return res;                                                                                                                                                  \
}                                                                                                                                                                \
                                                                                                                                                                 \
/*unsafe if call explicitly from outside*/                                                                                                                       \
static inline Matrix##UCN strassenAlgorithmForMatrix##UCN(const Matrix##UCN * a, const Matrix##UCN * b)                                                          \
{                                                                                                                                                                \
    int size_in_mult;                                                                                                                                            \
    MatrixRef##UCN A, B;                                                                                                                                         \
                                                                                                                                                                 \
    size_in_mult = max(max(findNextPower(a->lines), findNextPower(a->columns)),                                                                                  \
                    max(findNextPower(b->lines), findNextPower(b->columns)));                                                                                    \
    A = getMatrix##UCN##OnBuffer(a, 0, 0, size_in_mult, size_in_mult);                                                                                           \
    B = getMatrix##UCN##OnBuffer(b, 0, 0, size_in_mult, size_in_mult);                                                                                           \
                                                                                                                                                                 \
    int half_size_in_mult = size_in_mult / 2;                                                                                                                    \
    /*all names are matching ones in wiki*/                                                                                                                      \
    MatrixRef##UCN A11 = getMatrix##UCN##OnBuffer(&A, 0, 0, half_size_in_mult, half_size_in_mult);                                                               \
    MatrixRef##UCN A12 = getMatrix##UCN##OnBuffer(&A, 0, half_size_in_mult, half_size_in_mult, half_size_in_mult);                                               \
    MatrixRef##UCN A21 = getMatrix##UCN##OnBuffer(&A, half_size_in_mult, 0, half_size_in_mult, half_size_in_mult);                                               \
    MatrixRef##UCN A22 = getMatrix##UCN##OnBuffer(&A, half_size_in_mult, half_size_in_mult, half_size_in_mult, half_size_in_mult);                               \
                                                                                                                                                                 \
    MatrixRef##UCN B11 = getMatrix##UCN##OnBuffer(&B, 0, 0, half_size_in_mult, half_size_in_mult);                                                               \
    MatrixRef##UCN B12 = getMatrix##UCN##OnBuffer(&B, 0, half_size_in_mult, half_size_in_mult, half_size_in_mult);                                               \
    MatrixRef##UCN B21 = getMatrix##UCN##OnBuffer(&B, half_size_in_mult, 0, half_size_in_mult, half_size_in_mult);                                               \
    MatrixRef##UCN B22 = getMatrix##UCN##OnBuffer(&B, half_size_in_mult, half_size_in_mult, half_size_in_mult, half_size_in_mult);                               \
                                                                                                                                                                 \
                                                                                                                                                                 \
    Matrix##UCN M1 = multMatrix##UCN##RV(addMatrix##UCN(&A11, &A22), addMatrix##UCN(&B11, &B22));                                                                \
    Matrix##UCN M2 = multMatrix##UCN##RVLV(addMatrix##UCN(&A21, &A22), &B11);                                                                                    \
    Matrix##UCN M3 = multMatrix##UCN##LVRV(&A11, subMatrix##UCN(&B12, &B22));                                                                                    \
    Matrix##UCN M4 = multMatrix##UCN##LVRV(&A22, subMatrix##UCN(&B21, &B11));                                                                                    \
    Matrix##UCN M5 = multMatrix##UCN##RVLV(addMatrix##UCN(&A11, &A12), &B22);                                                                                    \
    Matrix##UCN M6 = multMatrix##UCN##RV(subMatrix##UCN(&A21, &A11), addMatrix##UCN(&B11, &B12));                                                                \
    Matrix##UCN M7 = multMatrix##UCN##RV(subMatrix##UCN(&A12, &A22), addMatrix##UCN(&B21, &B22));                                                                \
                                                                                                                                                                 \
                                                                                                                                                                 \
    Matrix##UCN res = defaultMatrix##UCN(a->lines, b->columns, null##UCN());                                                                                     \
    MatrixRef##UCN C11 = getMatrix##UCN##OnBuffer(&res, 0, 0, half_size_in_mult, half_size_in_mult);                                                             \
    MatrixRef##UCN C12 = getMatrix##UCN##OnBuffer(&res, 0, half_size_in_mult, half_size_in_mult, b->columns - half_size_in_mult);                                \
    MatrixRef##UCN C21 = getMatrix##UCN##OnBuffer(&res, half_size_in_mult, 0, a->lines - half_size_in_mult, half_size_in_mult);                                  \
    MatrixRef##UCN C22 = getMatrix##UCN##OnBuffer(&res, half_size_in_mult, half_size_in_mult, a->lines - half_size_in_mult, b->columns - half_size_in_mult);     \
                                                                                                                                                                 \
                                                                                                                                                                 \
    /*Matrix##UCN C11 = addMatrix##UCN##RV(addMatrix##UCN(&M1, &M4), subMatrix##UCN(&M7, &M5));*/                                                                \
    /*Matrix##UCN C12 = addMatrix##UCN(&M3, &M5);*/                                                                                                              \
    /*Matrix##UCN C21 = addMatrix##UCN(&M2, &M4);*/                                                                                                              \
    /*Matrix##UCN C22 = addMatrix##UCN##RV(subMatrix##UCN(&M1, &M2), addMatrix##UCN(&M3, &M6));*/                                                                \
                                                                                                                                                                 \
    chainAddingOrSubtractionToMatrix##UCN(&C11, PLUS, &M1, PLUS, &M4, MINUS, &M5, PLUS, &M7, STOP);                                                              \
    chainAddingOrSubtractionToMatrix##UCN(&C12, PLUS, &M3, PLUS, &M5, STOP);                                                                                     \
    chainAddingOrSubtractionToMatrix##UCN(&C21, PLUS, &M2, PLUS, &M4, STOP);                                                                                     \
    chainAddingOrSubtractionToMatrix##UCN(&C22, PLUS, &M1, MINUS, &M2, PLUS, &M3, PLUS, &M6, STOP);                                                              \
                                                                                                                                                                 \
                                                                                                                                                                 \
                                                                                                                                                                 \
    destructMatrix##UCN(&M1);                                                                                                                                    \
    destructMatrix##UCN(&M2);                                                                                                                                    \
    destructMatrix##UCN(&M3);                                                                                                                                    \
    destructMatrix##UCN(&M4);                                                                                                                                    \
    destructMatrix##UCN(&M5);                                                                                                                                    \
    destructMatrix##UCN(&M6);                                                                                                                                    \
    destructMatrix##UCN(&M7);                                                                                                                                    \
                                                                                                                                                                 \
    return res;                                                                                                                                                  \
}                                                                                                                                                                \
                                                                                                                                                                 \
                                                                                                                                                                 \
static inline Matrix##UCN multMatrix##UCN(const Matrix##UCN * a, const Matrix##UCN * b)                                                                          \
{                                                                                                                                                                \
                                                                                                                                                                 \
    assert(a->columns == b->lines);                                                                                                                              \
                                                                                                                                                                 \
    /*very rough estimate but seems to work*/                                                                                                                    \
    if (a->lines + a->columns + b->columns <= 1000)                                                                                                              \
        return naiveMultMatrix##UCN(a, b);                                                                                                                       \
    return strassenAlgorithmForMatrix##UCN(a, b);                                                                                                                \
}                                                                                                                                                                \
static inline Matrix##UCN divMatrix##UCN(const Matrix##UCN * a, const Matrix##UCN * b)                                                                           \
{                                                                                                                                                                \
    assert(false);                                                                                                                                               \
}                                                                                                                                                                \
static inline void multToMatrix##UCN(Matrix##UCN * a, const Matrix##UCN * b)                                                                                     \
{                                                                                                                                                                \
    replaceMatrix##UCN(a, multMatrix##UCN(a, b));                                                                                                                \
}                                                                                                                                                                \
static inline void divToMatrix##UCN(Matrix##UCN * a, const Matrix##UCN * b)                                                                                      \
{                                                                                                                                                                \
    assert(false);                                                                                                                                               \
}                                                                                                                                                                \
static inline Matrix##UCN unitMatrix##UCN()                                                                                                                      \
{                                                                                                                                                                \
    /*it could work without type passed but without size its meaningless (tho it can be done if make states like in general types*/                              \
    /*and somewhere it even could be useful buuut too specific*/                                                                                                 \
    assert(false);                                                                                                                                               \
}                                                                                                                                                                \
static inline Matrix##UCN nullMatrix##UCN()                                                                                                                      \
{                                                                                                                                                                \
    /*same as unitMatrix##UCN()*/                                                                                                                                \
    assert(false);                                                                                                                                               \
}                                                                                                                                                                \
static inline Matrix##UCN minusMatrix##UCN(const Matrix##UCN * a)                                                                                                \
{                                                                                                                                                                \
    Matrix##UCN res = defaultMatrix##UCN(a->lines, a->columns, null##UCN());                                                                                     \
    for (int i = 0; i < a->lines; ++i)                                                                                                                           \
    {                                                                                                                                                            \
        for (int j = 0; j < a->columns; ++j)                                                                                                                     \
            *atMatrix##UCN##El(&res, i, j) = minus##UCN(catMatrix##UCN##El(a, i, j));                                                                            \
    }                                                                                                                                                            \
    return res;                                                                                                                                                  \
}                                                                                                                                                                \
static inline Matrix##UCN sqrtMatrix##UCN(const Matrix##UCN * a)                                                                                                 \
{                                                                                                                                                                \
    assert(false);                                                                                                                                               \
}                                                                                                                                                                \
                                                                                                                                                                 \
                                                                                                                                                                 \
                                                                                                                                                                 \
                                                                                                                                                                 \
                                                                                                                                                                 \
                                                                                                                                                                 \
                                                                                                                                                                 \
                                                                                                                                                                 \
                                                                                                                                                                 \
                                                                                                                                                                 \
                                                                                                                                                                 \
/*------- for inverse*/                                                                                                                                          \
static inline int getIndexOfFirstNonZero##UCN(Vector##UCN * vec)                                                                                                 \
{                                                                                                                                                                \
    for (int i = 0; i < vec->getSize(vec); ++i)                                                                                                                  \
        if (!isNull##UCN(vec->at(vec, i)) )                                                                                                                      \
            return i;                                                                                                                                            \
    return vec->getSize(vec);                                                                                                                                    \
}                                                                                                                                                                \
                                                                                                                                                                 \
static inline int pairSecComparator##UCN(const void * ap, const void * bp)                                                                                       \
{                                                                                                                                                                \
    PairInt * a = (PairInt*)ap;                                                                                                                                  \
    PairInt * b = (PairInt*)bp;                                                                                                                                  \
    if (a->second < b->second)                                                                                                                                   \
        return -1;                                                                                                                                               \
    if (a->second > b->second)                                                                                                                                   \
        return 1;                                                                                                                                                \
    /*first does not matter*/                                                                                                                                    \
    return 0;                                                                                                                                                    \
}                                                                                                                                                                \
                                                                                                                                                                 \
static inline void swapVectorsRat##UCN(Vector##UCN * a, Vector##UCN * b)                                                                                         \
{                                                                                                                                                                \
    Vector##UCN t;                                                                                                                                               \
    memcpy(&t, a, sizeof(Vector##UCN));                                                                                                                          \
    memcpy(a, b, sizeof(Vector##UCN));                                                                                                                           \
    memcpy(b, &t, sizeof(Vector##UCN));                                                                                                                          \
}                                                                                                                                                                \
                                                                                                                                                                 \
static inline void sortRows##UCN(int height, Matrix##UCN * matrix, VectorPairInt * indexes_of_first_non_zero, Matrix##UCN * result)                              \
{                                                                                                                                                                \
    for (int i = 0; i < height; ++i)                                                                                                                             \
    {                                                                                                                                                            \
        *indexes_of_first_non_zero->at(indexes_of_first_non_zero, i) =                                                                                           \
                defaultPairInt( i, getIndexOfFirstNonZero##UCN(matrix->matrix.at(&matrix->matrix, i)) );                                                         \
    }                                                                                                                                                            \
    sortVectorPairInt(indexes_of_first_non_zero, &pairSecComparator##UCN);                                                                                       \
    for (int i = 0; i < height; ++i)                                                                                                                             \
    {                                                                                                                                                            \
        if (i < atVectorPairInt(indexes_of_first_non_zero, i)->first)                                                                                            \
        {                                                                                                                                                        \
            swapVectorsRat##UCN(atMatrix##UCN(matrix, i), atMatrix##UCN(matrix, atVectorPairInt(indexes_of_first_non_zero, i)->first));                          \
            swapVectorsRat##UCN(atMatrix##UCN(result, i), atMatrix##UCN(result, atVectorPairInt(indexes_of_first_non_zero, i)->first));                          \
        }                                                                                                                                                        \
    }                                                                                                                                                            \
}                                                                                                                                                                \
                                                                                                                                                                 \
static inline void divideOnLeadElement##UCN(Matrix##UCN * matrix, Matrix##UCN * result, int x)                                                                   \
{                                                                                                                                                                \
    UCN lead_el = *atMatrix##UCN##El(matrix, x, x);                                                                                                              \
    for (int i = x; i < matrix->lines; ++i)                                                                                                                      \
    {                                                                                                                                                            \
        ARITHM_TYPE##_TYPE_DIV_TO(UCN, atMatrix##UCN##El(matrix, x, i), &lead_el);                                                                               \
    }                                                                                                                                                            \
    for (int i = 0; i < matrix->lines; ++i)                                                                                                                      \
    {                                                                                                                                                            \
        ARITHM_TYPE##_TYPE_DIV_TO(UCN, atMatrix##UCN##El(result, x, i), &lead_el);                                                                               \
    }                                                                                                                                                            \
}                                                                                                                                                                \
                                                                                                                                                                 \
/*by gauss algorithm.*/                                                                                                                                          \
/*algorithm will give divide by zero error somewhere (in divideByLeadElement) if determinant is null*/                                                           \
static inline Matrix##UCN inverseMatrix##UCN(Matrix##UCN * matrix)                                                                                               \
{                                                                                                                                                                \
/*only squares matrix are inverted*/                                                                                                                             \
assert(matrix->lines == matrix->columns);                                                                                                                        \
    Matrix##UCN result = makeUnitMatrix##UCN(matrix->lines);                                                                                                     \
    int height = matrix->lines;                                                                                                                                  \
    int width = matrix->columns;                                                                                                                                 \
                                                                                                                                                                 \
    VectorPairInt indexes_of_first_non_zero = defaultVectorPairIntRV(height, defaultPairInt(0,0));                                                               \
                                                                                                                                                                 \
                                                                                                                                                                 \
    sortRows##UCN(height, matrix, &indexes_of_first_non_zero, &result);                                                                                          \
/*to triangular form*/                                                                                                                                           \
    for (int n = 0; n < height; ++n) {                                                                                                                           \
        divideOnLeadElement##UCN(matrix, &result, n);                                                                                                            \
        for (int i = n + 1; i < height; ++i)                                                                                                                     \
        {                                                                                                                                                        \
            UCN multiplier = minus##UCN##RV(ARITHM_TYPE##_TYPE_DIV(UCN, atMatrix##UCN##El(matrix, i, n), atMatrix##UCN##El(matrix, n, n)));                      \
            /*HOW ITS UGLY IN C*/                                                                                                                                \
            replaceVector##UCN(atMatrix##UCN(matrix, i) , addVector##UCN##LVRV(matrix->at(matrix, i),                                                            \
                                                         Vector##UCN##MultedOnNum(atMatrix##UCN(matrix, n), &multiplier)));                                      \
            replaceVector##UCN(atMatrix##UCN(&result, i) , addVector##UCN##LVRV(atMatrix##UCN(&result, i),                                                       \
                                                          Vector##UCN##MultedOnNum(atMatrix##UCN(&result, n) , &multiplier)));                                   \
                                                                                                                                                                 \
                                                                                                                                                                 \
        }                                                                                                                                                        \
                                                                                                                                                                 \
    }                                                                                                                                                            \
                                                                                                                                                                 \
/*back to normal*/                                                                                                                                               \
    for (int n = height - 1; n >= 0; --n)                                                                                                                        \
    {                                                                                                                                                            \
        for (int i = n - 1; i >= 0; --i)                                                                                                                         \
        {                                                                                                                                                        \
            UCN multiplier = minus##UCN##RV(ARITHM_TYPE##_TYPE_DIV(UCN, atMatrix##UCN##El(matrix, i, n), atMatrix##UCN##El(matrix, n, n)));                      \
            replaceVector##UCN(atMatrix##UCN(matrix, i) , addVector##UCN##LVRV(matrix->at(matrix, i),                                                            \
                                                         Vector##UCN##MultedOnNum(matrix->at(matrix, n), &multiplier)));                                         \
            replaceVector##UCN(atMatrix##UCN(&result, i) , addVector##UCN##LVRV(atMatrix##UCN(&result, i),                                                       \
                                                          Vector##UCN##MultedOnNum(atMatrix##UCN(&result, n) , &multiplier)));                                   \
        }                                                                                                                                                        \
    }                                                                                                                                                            \
    destructVectorPairInt(&indexes_of_first_non_zero);                                                                                                           \
    return result;                                                                                                                                               \
}                                                                                                                                                                \
                                                                                                                                                                 \
static inline void printfMatrix##UCN(const Matrix##UCN * mat)                                                                                                    \
{                                                                                                                                                                \
    for (int i = 0; i < mat->lines; ++i)                                                                                                                         \
    {                                                                                                                                                            \
        for (int j = 0; j < mat->columns; ++j)                                                                                                                   \
        {                                                                                                                                                        \
            printf##UCN(catMatrix##UCN##El(mat, i, j));                                                                                                          \
        }                                                                                                                                                        \
        printf("\n");                                                                                                                                            \
    }                                                                                                                                                            \
    printf("\n");                                                                                                                                                \
}                                                                                                                                                                \


#endif
