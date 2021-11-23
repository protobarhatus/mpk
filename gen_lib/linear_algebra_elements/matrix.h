#ifndef FIBONACHY_NIM_MATRIX_H
#define FIBONACHY_NIM_MATRIX_H

#include "matrix_def.h"

struct MatrixInt_struct
{
    VectorVectorInt matrix;
    int lines, columns;

    VectorInt *(*at)(struct MatrixInt_struct *a, int i);

    _Bool is_on_buffer;
    int start_line, start_column, allocked_lines, allocked_columns;
    Int value_beyond_allocked_space;
    const Int *value_beyond_allocked_space_ptr;
};

typedef struct MatrixInt_struct MatrixInt;
typedef MatrixInt MatrixIntRef;

static inline MatrixInt defaultMatrixInt(int lines, int columns, Int def_value);

static inline MatrixInt makeUnitMatrixInt(int n);

static inline MatrixInt copyMatrixInt(const MatrixInt *mat);

static inline MatrixInt moveMatrixInt(MatrixInt *mat);

static inline void destructMatrixInt(MatrixInt *mat);

static inline _Bool equalMatrixInt(const MatrixInt *a, const MatrixInt *b);

MatrixInt copyMatrixInt(MatrixInt const *src);

static inline void *cpyFuncMatrixInt(void *dest, const void *src, size_t n)
{
    *((MatrixInt *) dest) = copyMatrixInt((MatrixInt const *) src);
    return ((void *) 0);
}

void destructMatrixInt(MatrixInt *el);

static inline void destrFuncMatrixInt(void *el)
{ destructMatrixInt((MatrixInt *) el); }

MatrixInt moveMatrixInt(MatrixInt *el);

static inline void *moveFuncMatrixInt(void *dest, void *src, size_t n)
{
    *((MatrixInt *) dest) = moveMatrixInt((MatrixInt *) src);
    return ((void *) 0);
}

_Bool equalMatrixInt(MatrixInt const *a, MatrixInt const *b);

static inline _Bool equalFuncMatrixInt(const void *a, const void *b, int num)
{ return equalMatrixInt((MatrixInt const *) a, (MatrixInt const *) b); }

static inline const TypePresenterContainer *TYPE_MatrixInt()
{
    static const TypePresenterContainer type = {&cpyFuncMatrixInt, &destrFuncMatrixInt, &moveFuncMatrixInt,
                                                &equalFuncMatrixInt, sizeof(MatrixInt), "MatrixInt"};
    return &type;
}

static inline void replaceMatrixInt(MatrixInt *a, MatrixInt b)
{
    destructMatrixInt(a);
    *a = b;
}

static inline _Bool equalMatrixIntLVRV(const MatrixInt *a, MatrixInt b)
{
    _Bool res = equalMatrixInt(a, &b);
    destructMatrixInt(&b);
    return res;
}

static inline _Bool equalMatrixIntRVLV(MatrixInt a, const MatrixInt *b)
{
    _Bool res = equalMatrixInt(&a, b);
    destructMatrixInt(&a);
    return res;
}

static inline _Bool equalMatrixIntRV(MatrixInt a, MatrixInt b)
{
    _Bool res = equalMatrixInt(&a, &b);
    destructMatrixInt(&a);
    destructMatrixInt(&b);
    return res;
};

static inline MatrixIntRef
getMatrixIntOnBuffer(const MatrixInt *origin, int lines_start, int lines_finish, int lines, int columns);

static inline void addToMatrixInt(MatrixInt *a, const MatrixInt *b);

static inline void subToMatrixInt(MatrixInt *a, const MatrixInt *b);

static inline MatrixInt addMatrixInt(const MatrixInt *a, const MatrixInt *b);

static inline MatrixInt subMatrixInt(const MatrixInt *a, const MatrixInt *b);

static inline MatrixInt multMatrixInt(const MatrixInt *a, const MatrixInt *b);

static inline MatrixInt divMatrixInt(const MatrixInt *a, const MatrixInt *b);

static inline void multToMatrixInt(MatrixInt *a, const MatrixInt *b);

static inline void divToMatrixInt(MatrixInt *a, const MatrixInt *b);

static inline MatrixInt unitMatrixInt();

static inline MatrixInt nullMatrixInt();

static inline MatrixInt minusMatrixInt(const MatrixInt *a);

static inline MatrixInt sqrtMatrixInt(const MatrixInt *a);

static inline void __addMatrixInt(void *dest, const void *a, const void *b)
{
    MatrixInt buff = *(MatrixInt *) dest;
    *((MatrixInt *) dest) = addMatrixInt((const MatrixInt *) a, (const MatrixInt *) b);
    destructMatrixInt(&buff);
}

static inline void __subMatrixInt(void *dest, const void *a, const void *b)
{
    MatrixInt buff = *(MatrixInt *) dest;
    *((MatrixInt *) dest) = subMatrixInt((const MatrixInt *) a, (const MatrixInt *) b);
    destructMatrixInt(&buff);
}

static inline void __multMatrixInt(void *dest, const void *a, const void *b)
{
    MatrixInt buff = *(MatrixInt *) dest;
    *((MatrixInt *) dest) = multMatrixInt((const MatrixInt *) a, (const MatrixInt *) b);
    destructMatrixInt(&buff);
}

static inline void __divMatrixInt(void *dest, const void *a, const void *b)
{
    MatrixInt buff = *(MatrixInt *) dest;
    *((MatrixInt *) dest) = divMatrixInt((const MatrixInt *) a, (const MatrixInt *) b);
    destructMatrixInt(&buff);
}

static inline void __addToMatrixInt(void *dest, const void *a)
{ addToMatrixInt((MatrixInt *) dest, (const MatrixInt *) a); }

static inline void __subToMatrixInt(void *dest, const void *a)
{ subToMatrixInt((MatrixInt *) dest, (const MatrixInt *) a); }

static inline void __multToMatrixInt(void *dest, const void *a)
{ multToMatrixInt((MatrixInt *) dest, (const MatrixInt *) a); }

static inline void __divToMatrixInt(void *dest, const void *a)
{ divToMatrixInt((MatrixInt *) dest, (const MatrixInt *) a); }

static inline void __sqrtMatrixInt(void *dest, const void *a)
{
    MatrixInt buff = *(MatrixInt *) dest;
    *((MatrixInt *) dest) = sqrtMatrixInt((const MatrixInt *) a);
    destructMatrixInt(&buff);
}

static inline void __minusMatrixInt(void *dest, const void *a)
{
    MatrixInt buff = *(MatrixInt *) dest;
    *((MatrixInt *) dest) = minusMatrixInt((const MatrixInt *) a);
    destructMatrixInt(&buff);
}

static inline void *__nullMatrixInt()
{
    MatrixInt *res = malloc(TYPE_MatrixInt()->element_size);
    *res = nullMatrixInt();
    return (void *) res;
}

static inline void *__unitMatrixInt()
{
    MatrixInt *res = malloc(TYPE_MatrixInt()->element_size);
    *res = unitMatrixInt();
    return (void *) res;
}

static inline MatrixInt addMatrixIntLVRV(const MatrixInt *a, MatrixInt b)
{
    MatrixInt res = addMatrixInt(a, &b);
    destructMatrixInt(&b);
    return res;
}

static inline MatrixInt addMatrixIntRVLV(MatrixInt a, const MatrixInt *b)
{
    MatrixInt res = addMatrixInt(&a, b);
    destructMatrixInt(&a);
    return res;
}

static inline MatrixInt addMatrixIntRV(MatrixInt a, MatrixInt b)
{
    MatrixInt res = addMatrixInt(&a, &b);
    destructMatrixInt(&a);
    destructMatrixInt(&b);
    return res;
}

static inline MatrixInt subMatrixIntLVRV(const MatrixInt *a, MatrixInt b)
{
    MatrixInt res = subMatrixInt(a, &b);
    destructMatrixInt(&b);
    return res;
}

static inline MatrixInt subMatrixIntRVLV(MatrixInt a, const MatrixInt *b)
{
    MatrixInt res = subMatrixInt(&a, b);
    destructMatrixInt(&a);
    return res;
}

static inline MatrixInt subMatrixIntRV(MatrixInt a, MatrixInt b)
{
    MatrixInt res = subMatrixInt(&a, &b);
    destructMatrixInt(&a);
    destructMatrixInt(&b);
    return res;
}

static inline MatrixInt multMatrixIntLVRV(const MatrixInt *a, MatrixInt b)
{
    MatrixInt res = multMatrixInt(a, &b);
    destructMatrixInt(&b);
    return res;
}

static inline MatrixInt multMatrixIntRVLV(MatrixInt a, const MatrixInt *b)
{
    MatrixInt res = multMatrixInt(&a, b);
    destructMatrixInt(&a);
    return res;
}

static inline MatrixInt multMatrixIntRV(MatrixInt a, MatrixInt b)
{
    MatrixInt res = multMatrixInt(&a, &b);
    destructMatrixInt(&a);
    destructMatrixInt(&b);
    return res;
}

static inline MatrixInt divMatrixIntLVRV(const MatrixInt *a, MatrixInt b)
{
    MatrixInt res = divMatrixInt(a, &b);
    destructMatrixInt(&b);
    return res;
}

static inline MatrixInt divMatrixIntRVLV(MatrixInt a, const MatrixInt *b)
{
    MatrixInt res = divMatrixInt(&a, b);
    destructMatrixInt(&a);
    return res;
}

static inline MatrixInt divMatrixIntRV(MatrixInt a, MatrixInt b)
{
    MatrixInt res = divMatrixInt(&a, &b);
    destructMatrixInt(&a);
    destructMatrixInt(&b);
    return res;
}

static inline MatrixInt sqrtMatrixIntRV(MatrixInt a)
{
    MatrixInt res = sqrtMatrixInt(&a);
    destructMatrixInt(&a);
    return res;
}

static inline MatrixInt minusMatrixIntRV(MatrixInt a)
{
    MatrixInt res = minusMatrixInt(&a);
    destructMatrixInt(&a);
    return res;
}

static inline void addToMatrixIntRV(MatrixInt *a, MatrixInt b)
{
    addToMatrixInt(a, &b);
    destructMatrixInt(&b);
}

static inline void subToMatrixIntRV(MatrixInt *a, MatrixInt b)
{
    subToMatrixInt(a, &b);
    destructMatrixInt(&b);
}

static inline void multToMatrixIntRV(MatrixInt *a, MatrixInt b)
{
    multToMatrixInt(a, &b);
    destructMatrixInt(&b);
}

static inline void divToMatrixIntRV(MatrixInt *a, MatrixInt b)
{
    divToMatrixInt(a, &b);
    destructMatrixInt(&b);
}

static inline const ArithmeticTypePresenter *ARITHM_TYPE_MatrixInt()
{
    static const ArithmeticTypePresenter type = {&__addMatrixInt, &__subMatrixInt, &__multMatrixInt, &__divMatrixInt,
                                                 &__addToMatrixInt, &__subToMatrixInt, &__multToMatrixInt,
                                                 &__divToMatrixInt, &__sqrtMatrixInt, &__minusMatrixInt,
                                                 &__nullMatrixInt, &__unitMatrixInt};
    return &type;
};

static inline VectorInt *atMatrixInt(MatrixInt *mat, int i)
{
    ((void) sizeof((!mat->is_on_buffer) ? 1 : 0), ({
        if (!mat->is_on_buffer);
        else
            __assert_fail("!mat->is_on_buffer", "_file_name_", 6, "_function_name_");
    }));
    return atVectorVectorInt(&mat->matrix, i);
}

static inline const VectorInt *catMatrixInt(const MatrixInt *mat, int i)
{
    ((void) sizeof((!mat->is_on_buffer) ? 1 : 0), ({
        if (!mat->is_on_buffer);
        else
            __assert_fail("!mat->is_on_buffer", "_file_name_", 6, "_function_name_");
    }));
    return catVectorVectorInt(&mat->matrix, i);
}

static inline Int *atMatrixIntEl(MatrixInt *mat, int i, int j)
{
    if (mat->is_on_buffer)
    {
        ((void) sizeof((i < mat->allocked_lines && j < mat->allocked_columns) ? 1 : 0), ({
            if (i < mat->allocked_lines && j < mat->allocked_columns);
            else
                __assert_fail("i < mat->allocked_lines && j < mat->allocked_columns", "_file_name_", 6,
                              "_function_name_");
        }));
        return atVectorInt(atVectorVectorInt(&mat->matrix, i + mat->start_line), j + mat->start_column);
    }
    ((void) sizeof((i < mat->lines && j < mat->columns) ? 1 : 0), ({
        if (i < mat->lines && j < mat->columns);
        else __assert_fail("i < mat->lines && j < mat->columns", "_file_name_", 6, "_function_name_");
    }));
    return &mat->matrix.vec[i].vec[j];
    return atVectorInt(atVectorVectorInt(&mat->matrix, i), j);
}

static inline const Int *catMatrixIntEl(const MatrixInt *mat, int i, int j)
{
    if (mat->is_on_buffer)
    {
        if (i >= mat->allocked_lines || j >= mat->allocked_columns)return mat->value_beyond_allocked_space_ptr;
        return catVectorInt(catVectorVectorInt(&mat->matrix, i + mat->start_line), j + mat->start_column);
    }
    ((void) sizeof((i < mat->lines && j < mat->columns) ? 1 : 0), ({
        if (i < mat->lines && j < mat->columns);
        else __assert_fail("i < mat->lines && j < mat->columns", "_file_name_", 6, "_function_name_");
    }));
    return &mat->matrix.vec[i].vec[j];
    return catVectorInt(catVectorVectorInt(&mat->matrix, i), j);
}

static inline void setValueToMatrixInt(MatrixInt *mat, int i, int j, Int value)
{
    if (mat->is_on_buffer)
    { if (i >= mat->allocked_lines || j >= mat->allocked_columns)return; }
    replaceInt(atMatrixIntEl(mat, i, j), moveInt(&value));
}

static inline MatrixInt scanfMatrixInt();

static inline MatrixInt inverseMatrixInt(MatrixInt *matrix);

static inline MatrixInt inverseMatrixIntRV(MatrixInt a)
{
    MatrixInt res = inverseMatrixInt(&a);
    destructMatrixInt(&a);
    return res;
};

static inline void printfMatrixInt(const MatrixInt *mat);

static inline void printfMatrixIntRV(MatrixInt a)
{
    printfMatrixInt(&a);
    destructMatrixInt(&a);
}

static inline MatrixInt naiveMultMatrixInt(const MatrixInt *a, const MatrixInt *b);

static inline void assignFunctionsMatrixInt(MatrixInt *mat)
{ mat->at = &atMatrixInt; }

static inline MatrixInt defaultMatrixInt(int lines, int columns, Int def_value)
{
    MatrixInt result;
    result.lines = lines;
    result.columns = columns;
    result.matrix = defaultVectorVectorIntRV(lines, defaultVectorIntRV(columns, def_value));
    assignFunctionsMatrixInt(&result);
    result.start_line = 0;
    result.start_column = 0;
    result.allocked_lines = result.lines;
    result.allocked_columns = result.columns;
    result.is_on_buffer = 0;
    result.value_beyond_allocked_space = nullInt();
    result.value_beyond_allocked_space_ptr = ((void *) 0);
    return result;
}

static inline MatrixInt makeUnitMatrixInt(int n)
{
    MatrixInt res;
    res.lines = n;
    res.columns = n;
    res.matrix = defaultVectorVectorIntRV(n, defaultVectorIntRV(n, nullInt()));
    for (int i = 0; i < n; ++i)*atMatrixIntEl(&res, i, i) = unitInt();
    res.start_line = 0;
    res.start_column = 0;
    res.allocked_lines = res.lines;
    res.allocked_columns = res.columns;
    res.is_on_buffer = 0;
    assignFunctionsMatrixInt(&res);
    return res;
}

static inline MatrixInt copyMatrixInt(const MatrixInt *mat)
{
    ((void) sizeof((!mat->is_on_buffer) ? 1 : 0), ({
        if (!mat->is_on_buffer);
        else
            __assert_fail("!mat->is_on_buffer", "_file_name_", 6, "_function_name_");
    }));
    MatrixInt res;
    res.lines = mat->lines;
    res.columns = mat->columns;
    res.matrix = copyVectorVectorInt(&mat->matrix);
    res.is_on_buffer = 0;
    res.allocked_lines = mat->allocked_lines;
    res.start_column = mat->start_column;
    res.start_line = mat->start_line;
    res.allocked_columns = mat->allocked_columns;
    res.value_beyond_allocked_space = copyInt(&mat->value_beyond_allocked_space);
    res.value_beyond_allocked_space_ptr = mat->value_beyond_allocked_space_ptr;
    assignFunctionsMatrixInt(&res);
    return res;
}

static inline MatrixInt moveMatrixInt(MatrixInt *mat)
{
    MatrixInt res;
    res.lines = mat->lines;
    res.columns = mat->columns;
    res.matrix = moveVectorVectorInt(&mat->matrix);
    res.is_on_buffer = mat->is_on_buffer;
    res.allocked_lines = mat->allocked_lines;
    res.start_column = mat->start_column;
    res.start_line = mat->start_line;
    res.allocked_columns = mat->allocked_columns;
    res.value_beyond_allocked_space = moveInt(&mat->value_beyond_allocked_space);
    res.value_beyond_allocked_space_ptr = mat->value_beyond_allocked_space_ptr;
    mat->lines = -1;
    mat->columns = -1;
    assignFunctionsMatrixInt(&res);
    return res;
}

static inline _Bool equalMatrixInt(const MatrixInt *a, const MatrixInt *b)
{
    if (a->lines != b->lines || a->columns != b->columns)return 0;
    for (int i = 0; i < a->lines; ++i)
    {
        for (int j = 0; j < a->columns; ++j)
        { if (!equalInt(catMatrixIntEl(a, i, j), catMatrixIntEl(b, i, j)))return 0; }
    }
    return 1;
}

static inline void destructMatrixInt(MatrixInt *mat)
{
    if (mat->is_on_buffer)
    { return; }
    destructVectorVectorInt(&mat->matrix);
    destructInt(&mat->value_beyond_allocked_space);
}

static inline MatrixIntRef
getMatrixIntOnBuffer(const MatrixInt *origin, int lines_start, int columns_start, int lines, int columns)
{
    MatrixIntRef res;
    res.matrix = origin->matrix;
    res.lines = lines;
    res.columns = columns;
    res.is_on_buffer = 1;
    res.start_line = origin->start_line + lines_start;
    res.start_column = origin->start_column + columns_start;
    res.allocked_lines = origin->allocked_lines - lines_start;
    res.allocked_columns = origin->allocked_columns - columns_start;
    if (origin->is_on_buffer)res.value_beyond_allocked_space_ptr = origin->value_beyond_allocked_space_ptr; else res.value_beyond_allocked_space_ptr = &origin->value_beyond_allocked_space;
    assignFunctionsMatrixInt(&res);
    return res;
}

static inline void addToMatrixInt(MatrixInt *a, const MatrixInt *b)
{
    ((void) sizeof((a->lines <= b->lines && a->columns <= b->columns) ? 1 : 0), ({
        if (a->lines <= b->lines && a->columns <= b->columns);
        else
            __assert_fail("a->lines <= b->lines && a->columns <= b->columns", "_file_name_", 6, "_function_name_");
    }));
    for (int i = 0; i < a->lines; ++i)
    {
        for (int j = 0; j < a->columns; ++j)
            if (!a->is_on_buffer || (i < a->allocked_lines && j < a->allocked_columns))
                ((*atMatrixIntEl(a, i, j)) += (*catMatrixIntEl(b, i, j)));
    }
}

static inline MatrixInt addMatrixInt(const MatrixInt *a, const MatrixInt *b)
{
    ((void) sizeof((a->lines == b->lines && a->columns == b->columns) ? 1 : 0), ({
        if (a->lines == b->lines && a->columns == b->columns);
        else
            __assert_fail("a->lines == b->lines && a->columns == b->columns", "_file_name_", 6, "_function_name_");
    }));
    MatrixInt res = defaultMatrixInt(a->lines, a->columns, nullInt());
    addToMatrixInt(&res, a);
    addToMatrixInt(&res, b);
    return res;
}

static inline void subToMatrixInt(MatrixInt *a, const MatrixInt *b)
{
    ((void) sizeof((a->lines <= b->lines && a->columns <= b->columns) ? 1 : 0), ({
        if (a->lines <= b->lines && a->columns <= b->columns);
        else
            __assert_fail("a->lines <= b->lines && a->columns <= b->columns", "_file_name_", 6, "_function_name_");
    }));
    for (int i = 0; i < a->lines; ++i)
    {
        for (int j = 0; j < a->columns; ++j)
        {
            if (!a->is_on_buffer || (i < a->allocked_lines && j < a->allocked_columns))
                ((*atMatrixIntEl(a, i, j)) -= (*catMatrixIntEl(b, i, j)));
        }
    }
}

static inline MatrixInt subMatrixInt(const MatrixInt *a, const MatrixInt *b)
{
    ((void) sizeof((a->lines == b->lines && a->columns == b->columns) ? 1 : 0), ({
        if (a->lines == b->lines && a->columns == b->columns);
        else
            __assert_fail("a->lines == b->lines && a->columns == b->columns", "_file_name_", 6, "_function_name_");
    }));
    MatrixInt res = defaultMatrixInt(a->lines, a->columns, nullInt());
    addToMatrixInt(&res, a);
    subToMatrixInt(&res, b);
    return res;
}

static inline MatrixInt naiveMultMatrixInt(const MatrixInt *a, const MatrixInt *b)
{
    MatrixInt res = defaultMatrixInt(a->lines, b->columns, nullInt());
    int a_lines = min(a->lines, a->allocked_lines);
    int b_columns = min(b->columns, b->allocked_columns);
    int mid_columns = min(min(a->columns, a->allocked_columns), min(b->allocked_lines, b->lines));
    for (int i = 0; i < a_lines; ++i)
    {
        for (int j = 0; j < b_columns; ++j)
        {
            for (int k = 0; k < mid_columns; ++k)
                ((*&res.matrix.vec[i].vec[j]) += (((*&a->matrix.vec[i + a->start_line].vec[k + a->start_column]) *
                                                   (*&b->matrix.vec[k + b->start_line].vec[j + b->start_column]))));
        }
    }
    return res;
}

static inline MatrixInt multMatrixIntRV(MatrixInt a, MatrixInt b);

static inline MatrixInt *addMatrixIntOnBuff(MatrixInt *buff, const MatrixInt *a, const MatrixInt *b)
{
    for (int i = 0; i < buff->lines; ++i)
    {
        for (int j = 0; j < buff->columns; ++j)
            replaceInt(atMatrixIntEl(buff, i, j), ((*catMatrixIntEl(a, i, j)) + (*catMatrixIntEl(b, i, j))));
    }
    return buff;
}

static inline MatrixInt *subMatrixIntOnBuff(MatrixInt *buff, const MatrixInt *a, const MatrixInt *b)
{
    for (int i = 0; i < buff->lines; ++i)
    {
        for (int j = 0; j < buff->columns; ++j)
        { replaceInt(atMatrixIntEl(buff, i, j), ((*catMatrixIntEl(a, i, j)) - (*catMatrixIntEl(b, i, j)))); }
    }
    return buff;
}

static inline void chainAddingOrSubtractionToMatrixInt(MatrixInt *mat, ...)
{
    va_list arg;
    va_start(arg, mat);
    Sign next_sign;
    while ((next_sign = va_arg(arg, Sign)) != STOP)
    {
        if (next_sign == PLUS)
            addToMatrixInt(mat, va_arg(arg, MatrixInt*));
        else
            subToMatrixInt(mat, va_arg(arg, MatrixInt*));
    }
    va_end(arg);
}

static inline MatrixInt scanfMatrixInt()
{
    int len = scanfInt(), col = scanfInt();
    MatrixInt res = defaultMatrixInt(len, col, nullInt());
    for (int i = 0; i < len; ++i)
    {
        for (int j = 0; j < col; ++j)
        { replaceInt(atMatrixIntEl(&res, i, j), scanfInt()); }
    }
    return res;
}

static inline MatrixInt strassenAlgorithmForMatrixInt(const MatrixInt *a, const MatrixInt *b)
{
    int size_in_mult;
    MatrixIntRef A, B;
    size_in_mult = max(max(findNextPower(a->lines), findNextPower(a->columns)),
                       max(findNextPower(b->lines), findNextPower(b->columns)));
    A = getMatrixIntOnBuffer(a, 0, 0, size_in_mult, size_in_mult);
    B = getMatrixIntOnBuffer(b, 0, 0, size_in_mult, size_in_mult);
    int half_size_in_mult = size_in_mult / 2;
    MatrixIntRef A11 = getMatrixIntOnBuffer(&A, 0, 0, half_size_in_mult, half_size_in_mult);
    MatrixIntRef A12 = getMatrixIntOnBuffer(&A, 0, half_size_in_mult, half_size_in_mult, half_size_in_mult);
    MatrixIntRef A21 = getMatrixIntOnBuffer(&A, half_size_in_mult, 0, half_size_in_mult, half_size_in_mult);
    MatrixIntRef A22 = getMatrixIntOnBuffer(&A, half_size_in_mult, half_size_in_mult, half_size_in_mult,
                                            half_size_in_mult);
    MatrixIntRef B11 = getMatrixIntOnBuffer(&B, 0, 0, half_size_in_mult, half_size_in_mult);
    MatrixIntRef B12 = getMatrixIntOnBuffer(&B, 0, half_size_in_mult, half_size_in_mult, half_size_in_mult);
    MatrixIntRef B21 = getMatrixIntOnBuffer(&B, half_size_in_mult, 0, half_size_in_mult, half_size_in_mult);
    MatrixIntRef B22 = getMatrixIntOnBuffer(&B, half_size_in_mult, half_size_in_mult, half_size_in_mult,
                                            half_size_in_mult);
    MatrixInt M1 = multMatrixIntRV(addMatrixInt(&A11, &A22), addMatrixInt(&B11, &B22));
    MatrixInt M2 = multMatrixIntRVLV(addMatrixInt(&A21, &A22), &B11);
    MatrixInt M3 = multMatrixIntLVRV(&A11, subMatrixInt(&B12, &B22));
    MatrixInt M4 = multMatrixIntLVRV(&A22, subMatrixInt(&B21, &B11));
    MatrixInt M5 = multMatrixIntRVLV(addMatrixInt(&A11, &A12), &B22);
    MatrixInt M6 = multMatrixIntRV(subMatrixInt(&A21, &A11), addMatrixInt(&B11, &B12));
    MatrixInt M7 = multMatrixIntRV(subMatrixInt(&A12, &A22), addMatrixInt(&B21, &B22));
    MatrixInt res = defaultMatrixInt(a->lines, b->columns, nullInt());
    MatrixIntRef C11 = getMatrixIntOnBuffer(&res, 0, 0, half_size_in_mult, half_size_in_mult);
    MatrixIntRef C12 = getMatrixIntOnBuffer(&res, 0, half_size_in_mult, half_size_in_mult,
                                            b->columns - half_size_in_mult);
    MatrixIntRef C21 = getMatrixIntOnBuffer(&res, half_size_in_mult, 0, a->lines - half_size_in_mult,
                                            half_size_in_mult);
    MatrixIntRef C22 = getMatrixIntOnBuffer(&res, half_size_in_mult, half_size_in_mult, a->lines - half_size_in_mult,
                                            b->columns - half_size_in_mult);
    chainAddingOrSubtractionToMatrixInt(&C11, PLUS, &M1, PLUS, &M4, MINUS, &M5, PLUS, &M7, STOP);
    chainAddingOrSubtractionToMatrixInt(&C12, PLUS, &M3, PLUS, &M5, STOP);
    chainAddingOrSubtractionToMatrixInt(&C21, PLUS, &M2, PLUS, &M4, STOP);
    chainAddingOrSubtractionToMatrixInt(&C22, PLUS, &M1, MINUS, &M2, PLUS, &M3, PLUS, &M6, STOP);
    destructMatrixInt(&M1);
    destructMatrixInt(&M2);
    destructMatrixInt(&M3);
    destructMatrixInt(&M4);
    destructMatrixInt(&M5);
    destructMatrixInt(&M6);
    destructMatrixInt(&M7);
    return res;
}

static inline MatrixInt multMatrixInt(const MatrixInt *a, const MatrixInt *b)
{
    ((void) sizeof((a->columns == b->lines) ? 1 : 0), ({
        if (a->columns == b->lines);
        else
            __assert_fail("a->columns == b->lines", "_file_name_", 6, "_function_name_");
    }));
    if (a->lines + a->columns + b->columns <= 1500)return naiveMultMatrixInt(a, b);
    return strassenAlgorithmForMatrixInt(a, b);
}

static inline MatrixInt divMatrixInt(const MatrixInt *a, const MatrixInt *b)
{ ((void) sizeof((0) ? 1 : 0), ({ if (0); else __assert_fail("false", "_file_name_", 6, "_function_name_"); })); }

static inline void multToMatrixInt(MatrixInt *a, const MatrixInt *b)
{ replaceMatrixInt(a, multMatrixInt(a, b)); }

static inline void divToMatrixInt(MatrixInt *a, const MatrixInt *b)
{ ((void) sizeof((0) ? 1 : 0), ({ if (0); else __assert_fail("false", "_file_name_", 6, "_function_name_"); })); }

static inline MatrixInt unitMatrixInt()
{ ((void) sizeof((0) ? 1 : 0), ({ if (0); else __assert_fail("false", "_file_name_", 6, "_function_name_"); })); }

static inline MatrixInt nullMatrixInt()
{ ((void) sizeof((0) ? 1 : 0), ({ if (0); else __assert_fail("false", "_file_name_", 6, "_function_name_"); })); }

static inline MatrixInt minusMatrixInt(const MatrixInt *a)
{
    MatrixInt res = defaultMatrixInt(a->lines, a->columns, nullInt());
    for (int i = 0; i < a->lines; ++i)
    { for (int j = 0; j < a->columns; ++j)*atMatrixIntEl(&res, i, j) = minusInt(catMatrixIntEl(a, i, j)); }
    return res;
}

static inline MatrixInt sqrtMatrixInt(const MatrixInt *a)
{ ((void) sizeof((0) ? 1 : 0), ({ if (0); else __assert_fail("false", "_file_name_", 6, "_function_name_"); })); }

static inline int getIndexOfFirstNonZeroInt(VectorInt *vec)
{
    for (int i = 0; i < vec->getSize(vec); ++i)if (!isNullInt(vec->at(vec, i)))return i;
    return vec->getSize(vec);
}

static inline int pairSecComparatorInt(const void *ap, const void *bp)
{
    PairInt *a = (PairInt *) ap;
    PairInt *b = (PairInt *) bp;
    if (a->second < b->second)return -1;
    if (a->second > b->second)return 1;
    return 0;
}

static inline void swapVectorsRatInt(VectorInt *a, VectorInt *b)
{
    VectorInt t;
    memcpy(&t, a, sizeof(VectorInt));
    memcpy(a, b, sizeof(VectorInt));
    memcpy(b, &t, sizeof(VectorInt));
}

static inline void
sortRowsInt(int height, MatrixInt *matrix, VectorPairInt *indexes_of_first_non_zero, MatrixInt *result)
{
    for (int i = 0; i < height; ++i)
    {
        *indexes_of_first_non_zero->at(indexes_of_first_non_zero, i) = defaultPairInt(i, getIndexOfFirstNonZeroInt(
                matrix->matrix.at(&matrix->matrix, i)));
    }
    sortVectorPairInt(indexes_of_first_non_zero, &pairSecComparatorInt);
    for (int i = 0; i < height; ++i)
    {
        if (i < atVectorPairInt(indexes_of_first_non_zero, i)->first)
        {
            swapVectorsRatInt(atMatrixInt(matrix, i),
                              atMatrixInt(matrix, atVectorPairInt(indexes_of_first_non_zero, i)->first));
            swapVectorsRatInt(atMatrixInt(result, i),
                              atMatrixInt(result, atVectorPairInt(indexes_of_first_non_zero, i)->first));
        }
    }
}

static inline void divideOnLeadElementInt(MatrixInt *matrix, MatrixInt *result, int x)
{
    Int lead_el = *atMatrixIntEl(matrix, x, x);
    for (int i = x; i < matrix->lines; ++i)
    { ((*atMatrixIntEl(matrix, x, i)) /= (*&lead_el)); }
    for (int i = 0; i < matrix->lines; ++i)
    { ((*atMatrixIntEl(result, x, i)) /= (*&lead_el)); }
}

static inline MatrixInt inverseMatrixInt(MatrixInt *matrix)
{
    ((void) sizeof((matrix->lines == matrix->columns) ? 1 : 0), ({
        if (matrix->lines == matrix->columns);
        else __assert_fail("matrix->lines == matrix->columns", "_file_name_", 6, "_function_name_");
    }));
    MatrixInt result = makeUnitMatrixInt(matrix->lines);
    int height = matrix->lines;
    int width = matrix->columns;
    VectorPairInt indexes_of_first_non_zero = defaultVectorPairIntRV(height, defaultPairInt(0, 0));
    sortRowsInt(height, matrix, &indexes_of_first_non_zero, &result);
    for (int n = 0; n < height; ++n)
    {
        divideOnLeadElementInt(matrix, &result, n);
        for (int i = n + 1; i < height; ++i)
        {
            Int multiplier = minusIntRV(((*atMatrixIntEl(matrix, i, n)) / (*atMatrixIntEl(matrix, n, n))));
            replaceVectorInt(atMatrixInt(matrix, i), addVectorIntLVRV(matrix->at(matrix, i),
                                                                      VectorIntMultedOnNum(atMatrixInt(matrix, n),
                                                                                           &multiplier)));
            replaceVectorInt(atMatrixInt(&result, i), addVectorIntLVRV(atMatrixInt(&result, i),
                                                                       VectorIntMultedOnNum(atMatrixInt(&result, n),
                                                                                            &multiplier)));
        }
    }
    for (int n = height - 1; n >= 0; --n)
    {
        for (int i = n - 1; i >= 0; --i)
        {
            Int multiplier = minusIntRV(((*atMatrixIntEl(matrix, i, n)) / (*atMatrixIntEl(matrix, n, n))));
            replaceVectorInt(atMatrixInt(matrix, i), addVectorIntLVRV(matrix->at(matrix, i),
                                                                      VectorIntMultedOnNum(matrix->at(matrix, n),
                                                                                           &multiplier)));
            replaceVectorInt(atMatrixInt(&result, i), addVectorIntLVRV(atMatrixInt(&result, i),
                                                                       VectorIntMultedOnNum(atMatrixInt(&result, n),
                                                                                            &multiplier)));
        }
    }
    destructVectorPairInt(&indexes_of_first_non_zero);
    return result;
}

static inline void printfMatrixInt(const MatrixInt *mat)
{
    for (int i = 0; i < mat->lines; ++i)
    {
        for (int j = 0; j < mat->columns; ++j)
        { printfInt(catMatrixIntEl(mat, i, j)); }
        printf("\n");
    }
    printf("\n");
}

#endif //FIBONACHY_NIM_MATRIX_H
