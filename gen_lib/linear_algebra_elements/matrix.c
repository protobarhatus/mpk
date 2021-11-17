#include <stdio.h>
#include <stdarg.h>
#include "matrix.h"
#include "../vector/algorithms.h"

void assignFunctions(Matrix * mat)
{
    mat->at = &atMatrix;
}

Matrix defaultMatrix(int lines, int columns, GeneralType def_value, CompleteTypePresenter type)
{
    Matrix result;
    result.lines = lines;
    result.columns = columns;
    //here def_value is destroyed so dont have to call destructor
    result.matrix = defaultVectorVectorGeneralTypeCalloc(lines, defaultVectorGeneralTypeCalloc(columns, def_value));
    assignFunctions(&result);
    result.type = type;
    result.start_line = 0;
    result.start_column = 0;
    result.allocked_lines = result.lines;
    result.allocked_columns = result.columns;
    result.is_on_buffer = false;
    result.value_beyond_allocked_space = nullGeneralTypeOfCertainType(type);
    result.value_beyond_allocked_space_ptr = NULL;
    return result;
}

Matrix makeUnitMatrix(int n, CompleteTypePresenter type)
{
    Matrix res;
    res.lines = n;
    res.columns = n;
    res.matrix = defaultVectorVectorGeneralTypeCalloc(n, defaultVectorGeneralTypeCalloc(n, nullGeneralTypeOfCertainType(type)));
    for (int i = 0; i < n; ++i)
        *res.matrix.at(&res.matrix, i, i) = unitGeneralTypeOfCertainType(type);

    res.start_line = 0;
    res.start_column = 0;
    res.allocked_lines = res.lines;
    res.allocked_columns = res.columns;
    res.is_on_buffer = false;
    assignFunctions(&res);
    return res;
}
Matrix copyMatrix(const Matrix * mat)
{
    assert(!mat->is_on_buffer);
    Matrix res;
    res.type = mat->type;
    res.lines = mat->lines;
    res.columns = mat->columns;
    res.matrix = copyVectorVectorGeneralType(&mat->matrix);
    res.is_on_buffer = false;
    res.allocked_lines = mat->allocked_lines;
    res.start_column = mat->start_column;
    res.start_line = mat->start_line;
    res.allocked_columns = mat->allocked_columns;
    res.value_beyond_allocked_space = copyGeneralType(&mat->value_beyond_allocked_space);
    res.value_beyond_allocked_space_ptr = mat->value_beyond_allocked_space_ptr;

    assignFunctions(&res);
    return res;
}
Matrix moveMatrix(Matrix * mat)
{
    Matrix res;
    res.type = mat->type;
    res.lines = mat->lines;
    res.columns = mat->columns;
    res.matrix = moveVectorVectorGeneralType(&mat->matrix);
    res.is_on_buffer = mat->is_on_buffer;
    res.allocked_lines = mat->allocked_lines;
    res.start_column = mat->start_column;
    res.start_line = mat->start_line;
    res.allocked_columns = mat->allocked_columns;
    res.value_beyond_allocked_space = moveGeneralType(&mat->value_beyond_allocked_space);
    res.value_beyond_allocked_space_ptr = mat->value_beyond_allocked_space_ptr;

    mat->lines = -1;
    mat->columns = -1;
    assignFunctions(&res);
    return res;
}

bool equalMatrix(const Matrix * a, const Matrix * b)
{
    if (a->lines != b->lines || a->columns != b->columns)
        return false;
    for (int i = 0; i < a->lines; ++i)
    {
        for (int j = 0; j < a->columns; ++j)
        {
            if (!equalGeneralType(catMatrixEl(a, i, j), catMatrixEl(b, i, j)))
                return false;
        }
    }
    return true;
}
void destructMatrix(Matrix * mat)
{
    if (mat->is_on_buffer)
    {
        return;
    }
    destructVectorVectorGeneralType(&mat->matrix);
    destructGeneralType(&mat->value_beyond_allocked_space);
}

MatrixRef getMatrixOnBuffer(const Matrix * origin, int lines_start, int columns_start, int lines, int columns)
{
    MatrixRef res;
    res.type = origin->type;
    res.matrix = origin->matrix;
    res.lines = lines;
    res.columns = columns;
    res.is_on_buffer = true;
    res.start_line = origin->start_line + lines_start;
    res.start_column = origin->start_column + columns_start;
    res.allocked_lines = origin->allocked_lines - lines_start;
    res.allocked_columns = origin->allocked_columns - columns_start;
    if (origin->is_on_buffer)
        res.value_beyond_allocked_space_ptr = origin->value_beyond_allocked_space_ptr;
    else
        res.value_beyond_allocked_space_ptr = &origin->value_beyond_allocked_space;
    
    assignFunctions(&res);
    return res;
}
//unknown type may come up in inordinary cases like vectors of matrixes etc.
static void tryToResolveType(const Matrix * a, const Matrix * b)
{
    if (a->type.type == NULL && b->type.type != NULL)
        ((Matrix*)a)->type = b->type;
    if (a->type.type != NULL && b->type.type == NULL)
        ((Matrix*)b)->type = a->type;
}
void addToMatrix(Matrix * a, const Matrix * b)
{
    tryToResolveType(a, b);
    assert(sameTypes(a->type, b->type));
    assert(a->lines <= b->lines && a->columns <= b->columns);
    for (int i = 0; i < a->lines; ++i)
    {
        for (int j = 0; j < a->columns; ++j)
            if (!a->is_on_buffer || (i < a->allocked_lines && j < a->allocked_columns))
                addToGeneralType(atMatrixEl(a, i, j), catMatrixEl(b, i, j));
    }

}
Matrix addMatrix(const Matrix * a, const Matrix * b)
{
    tryToResolveType(a, b);
    assert(sameTypes(a->type, b->type));
    assert(a->lines == b->lines && a->columns == b->columns);
    Matrix res = defaultMatrix(a->lines, a->columns, nullGeneralTypeOfCertainType(a->type), a->type);
    addToMatrix(&res, a);
    addToMatrix(&res, b);
    return res;
}
void subToMatrix(Matrix * a, const Matrix * b)
{
    tryToResolveType(a, b);
    assert(sameTypes(a->type, b->type));
    assert(a->lines <= b->lines && a->columns <= b->columns);
    for (int i = 0; i < a->lines; ++i)
    {
        for (int j = 0; j < a->columns; ++j)
        {
            if (!a->is_on_buffer || (i < a->allocked_lines && j < a->allocked_columns))
                subToGeneralType(atMatrixEl(a, i, j), catMatrixEl(b, i, j));
        }
    }
}
Matrix subMatrix(const Matrix * a, const Matrix * b)
{
    tryToResolveType(a, b);
    assert(sameTypes(a->type, b->type));
    assert(a->lines == b->lines && a->columns == b->columns);
    Matrix res = defaultMatrix(a->lines, a->columns, nullGeneralTypeOfCertainType(a->type), a->type);
    //cannot just make copy because matrixes may be on buffer and now thats assert
    addToMatrix(&res, a);
    subToMatrix(&res, b);
    return res;
}
//unsafe if call explicitly from outside
Matrix naiveMultMatrix(const Matrix * a, const Matrix * b)
{
    Matrix res = defaultMatrix(a->lines, b->columns, nullGeneralTypeOfCertainType(a->type), a->type);
    for (int i = 0; i < a->lines; ++i)
    {
        for (int j = 0; j < b->columns; ++j)
        {
            for (int k = 0; k < a->columns; ++k)
                addToGeneralTypeRV(atMatrixEl(&res, i, j),
                                   multGeneralType(catMatrixEl(a, i, k), catMatrixEl(b, k, j)));
        }
    }
    return res;
}
Matrix multMatrixRV(Matrix a, Matrix b);

Matrix* addMatrixOnBuff(Matrix* buff, const Matrix * a, const Matrix * b)
{
    for (int i = 0; i < buff->lines; ++i)
    {
        for (int j = 0; j < buff->columns; ++j)
            replaceGeneralType(atMatrixEl(buff, i, j), addGeneralType(catMatrixEl(a, i, j), catMatrixEl(b, i, j)));
    }
    return buff;
}
Matrix* subMatrixOnBuff(Matrix* buff, const Matrix * a, const Matrix * b)
{
    for (int i = 0; i < buff->lines; ++i)
    {
        for (int j = 0; j < buff->columns; ++j)
        {
            replaceGeneralType(atMatrixEl(buff, i, j), subGeneralType(catMatrixEl(a, i, j), catMatrixEl(b, i, j)));
        }
    }
    return buff;
}
enum Sign_enum
{
    PLUS,
    MINUS,
    STOP
};
typedef enum Sign_enum Sign;
void chainAddingOrSubtractionToMatrix(Matrix * mat, ...)
{
    va_list arg;
    va_start(arg, mat);
    Sign next_sign;
    while ((next_sign = va_arg(arg, Sign)) != STOP)
    {
        if (next_sign == PLUS)
            addToMatrix(mat, va_arg(arg, const Matrix *));
        else
            subToMatrix(mat, va_arg(arg, const Matrix *));
    }
    va_end(arg);
}

//unsafe if call explicitly from outside
Matrix strassenAlgorithmForMatrix(const Matrix * a, const Matrix * b)
{
    int size_in_mult;
    MatrixRef A, B;

    size_in_mult = max(max(findNextPower(a->lines), findNextPower(a->columns)),
                    max(findNextPower(b->lines), findNextPower(b->columns)));
    A = getMatrixOnBuffer(a, 0, 0, size_in_mult, size_in_mult);
    B = getMatrixOnBuffer(b, 0, 0, size_in_mult, size_in_mult);

    int half_size_in_mult = size_in_mult / 2;
    //all names are matching ones in wiki
    MatrixRef A11 = getMatrixOnBuffer(&A, 0, 0, half_size_in_mult, half_size_in_mult);
    MatrixRef A12 = getMatrixOnBuffer(&A, 0, half_size_in_mult, half_size_in_mult, half_size_in_mult);
    MatrixRef A21 = getMatrixOnBuffer(&A, half_size_in_mult, 0, half_size_in_mult, half_size_in_mult);
    MatrixRef A22 = getMatrixOnBuffer(&A, half_size_in_mult, half_size_in_mult, half_size_in_mult, half_size_in_mult);

    MatrixRef B11 = getMatrixOnBuffer(&B, 0, 0, half_size_in_mult, half_size_in_mult);
    MatrixRef B12 = getMatrixOnBuffer(&B, 0, half_size_in_mult, half_size_in_mult, half_size_in_mult);
    MatrixRef B21 = getMatrixOnBuffer(&B, half_size_in_mult, 0, half_size_in_mult, half_size_in_mult);
    MatrixRef B22 = getMatrixOnBuffer(&B, half_size_in_mult, half_size_in_mult, half_size_in_mult, half_size_in_mult);


    Matrix M1 = multMatrixRV(addMatrix(&A11, &A22), addMatrix(&B11, &B22));
    Matrix M2 = multMatrixRVLV(addMatrix(&A21, &A22), &B11);
    Matrix M3 = multMatrixLVRV(&A11, subMatrix(&B12, &B22));
    Matrix M4 = multMatrixLVRV(&A22, subMatrix(&B21, &B11));
    Matrix M5 = multMatrixRVLV(addMatrix(&A11, &A12), &B22);
    Matrix M6 = multMatrixRV(subMatrix(&A21, &A11), addMatrix(&B11, &B12));
    Matrix M7 = multMatrixRV(subMatrix(&A12, &A22), addMatrix(&B21, &B22));


    Matrix res = defaultMatrix(a->lines, b->columns, nullGeneralTypeOfCertainType(a->type), a->type);
    MatrixRef C11 = getMatrixOnBuffer(&res, 0, 0, half_size_in_mult, half_size_in_mult);
    MatrixRef C12 = getMatrixOnBuffer(&res, 0, half_size_in_mult, half_size_in_mult, b->columns - half_size_in_mult);
    MatrixRef C21 = getMatrixOnBuffer(&res, half_size_in_mult, 0, a->lines - half_size_in_mult, half_size_in_mult);
    MatrixRef C22 = getMatrixOnBuffer(&res, half_size_in_mult, half_size_in_mult, a->lines - half_size_in_mult, b->columns - half_size_in_mult);


    //Matrix C11 = addMatrixRV(addMatrix(&M1, &M4), subMatrix(&M7, &M5));
    //Matrix C12 = addMatrix(&M3, &M5);
    //Matrix C21 = addMatrix(&M2, &M4);
    //Matrix C22 = addMatrixRV(subMatrix(&M1, &M2), addMatrix(&M3, &M6));

    chainAddingOrSubtractionToMatrix(&C11, PLUS, &M1, PLUS, &M4, MINUS, &M5, PLUS, &M7, STOP);
    chainAddingOrSubtractionToMatrix(&C12, PLUS, &M3, PLUS, &M5, STOP);
    chainAddingOrSubtractionToMatrix(&C21, PLUS, &M2, PLUS, &M4, STOP);
    chainAddingOrSubtractionToMatrix(&C22, PLUS, &M1, MINUS, &M2, PLUS, &M3, PLUS, &M6, STOP);



    destructMatrix(&M1);
    destructMatrix(&M2);
    destructMatrix(&M3);
    destructMatrix(&M4);
    destructMatrix(&M5);
    destructMatrix(&M6);
    destructMatrix(&M7);

    return res;
}


Matrix multMatrix(const Matrix * a, const Matrix * b)
{
    tryToResolveType(a, b);
    assert(a->columns == b->lines);
    assert(sameTypes(a->type, b->type));
    //very rough estimate but seems to work
    if (a->lines + a->columns + b->columns <= 1000)
        return naiveMultMatrix(a, b);
    return strassenAlgorithmForMatrix(a, b);
}
Matrix divMatrix(const Matrix * a, const Matrix * b)
{
    assert(false);
}
void multToMatrix(Matrix * a, const Matrix * b)
{
    replaceMatrix(a, multMatrix(a, b));
}
void divToMatrix(Matrix * a, const Matrix * b)
{
    assert(false);
}
Matrix unitMatrix()
{
    //it could work without type passed but without size its meaningless (tho it can be done if make states like in general types
    //and somewhere it even could be useful buuut too specific
    assert(false);
}
Matrix nullMatrix()
{
    //same as unitMatrix()
    assert(false);
}
Matrix minusMatrix(const Matrix * a)
{
    Matrix res = defaultMatrix(a->lines, a->columns, nullGeneralTypeOfCertainType(a->type), a->type);
    for (int i = 0; i < a->lines; ++i)
    {
        for (int j = 0; j < a->columns; ++j)
            *atMatrixEl(&res, i, j) = minusGeneralType(catMatrixEl(a, i, j));
    }
    return res;
}
Matrix sqrtMatrix(const Matrix * a)
{
    assert(false);
}











//------- for inverse
static int getIndexOfFirstNonZero(VectorGeneralType * vec)
{
    for (int i = 0; i < vec->getSize(vec); ++i)
        if (!isNullGeneralType(vec->at(vec, i)) )
            return i;
    return vec->getSize(vec);
}

static int pairSecComparator(const void * ap, const void * bp)
{
    PairInt * a = (PairInt*)ap;
    PairInt * b = (PairInt*)bp;
    if (a->second < b->second)
        return -1;
    if (a->second > b->second)
        return 1;
    //first does not matter
    return 0;
}

static void swapVectorsRat(VectorGeneralType * a, VectorGeneralType * b)
{
    VectorGeneralType t;
    memcpy(&t, a, sizeof(VectorGeneralType));
    memcpy(a, b, sizeof(VectorGeneralType));
    memcpy(b, &t, sizeof(VectorGeneralType));
}

static void sortRows(int height, Matrix * matrix, VectorPairInt * indexes_of_first_non_zero, Matrix * result)
{
    for (int i = 0; i < height; ++i)
    {
        *indexes_of_first_non_zero->at(indexes_of_first_non_zero, i) =
                defaultPairInt( i, getIndexOfFirstNonZero(matrix->matrix.at(&matrix->matrix, i)) );
    }
    sortVectorPairInt(indexes_of_first_non_zero, &pairSecComparator);
    for (int i = 0; i < height; ++i)
    {
        if (i < atVectorPairInt(indexes_of_first_non_zero, i)->first)
        {
            swapVectorsRat(atMatrix(matrix, i), atMatrix(matrix, atVectorPairInt(indexes_of_first_non_zero, i)->first));
            swapVectorsRat(atMatrix(result, i), atMatrix(result, atVectorPairInt(indexes_of_first_non_zero, i)->first));
        }
    }
}

static void divideOnLeadElement(Matrix * matrix, Matrix * result, int x)
{
    GeneralType lead_el = *atMatrixEl(matrix, x, x);
    for (int i = x; i < matrix->lines; ++i)
    {
        divToGeneralType(atMatrixEl(matrix, x, i), &lead_el);
    }
    for (int i = 0; i < matrix->lines; ++i)
    {
        divToGeneralType(atMatrixEl(result, x, i), &lead_el);
    }
}

//by gauss algorithm.
//algorithm will give divide by zero error somewhere (in divideByLeadElement) if determinant is null
Matrix inverseMatrix(Matrix * matrix)
{
//only squares matrix are inverted
assert(matrix->lines == matrix->columns);
    Matrix result = makeUnitMatrix(matrix->lines, matrix->type);
    int height = matrix->lines;
    int width = matrix->columns;

    VectorPairInt indexes_of_first_non_zero = defaultVectorPairIntCalloc(height, defaultPairInt(0,0));


    sortRows(height, matrix, &indexes_of_first_non_zero, &result);
//to triangular form
    for (int n = 0; n < height; ++n) {
        divideOnLeadElement(matrix, &result, n);
        for (int i = n + 1; i < height; ++i)
        {
            GeneralType multiplier = minusGeneralTypeRV(divGeneralType(atMatrixEl(matrix, i, n), atMatrixEl(matrix, n, n)));
            //HOW ITS UGLY IN C
            replaceVectorGeneralType(atMatrix(matrix, i) , addVectorGeneralTypeLVRV(matrix->at(matrix, i),
                                                         vectorGeneralTypeMultedOnNum(matrix->at(matrix, n), &multiplier)));
            replaceVectorGeneralType(atMatrix(&result, i) , addVectorGeneralTypeLVRV(atMatrix(&result, i),
                                                          vectorGeneralTypeMultedOnNum(atMatrix(&result, n) , &multiplier)));


        }

    }

//back to normal
    for (int n = height - 1; n >= 0; --n)
    {
        for (int i = n - 1; i >= 0; --i)
        {
            GeneralType multiplier = minusGeneralTypeRV(divGeneralType(matrix->at(matrix, i, n), matrix->at(matrix, n, n)));
            replaceVectorGeneralType(atMatrix(matrix, i) , addVectorGeneralTypeLVRV(matrix->at(matrix, i),
                                                         vectorGeneralTypeMultedOnNum(matrix->at(matrix, n), &multiplier)));
            replaceVectorGeneralType(atMatrix(&result, i) , addVectorGeneralTypeLVRV(atMatrix(&result, i),
                                                          vectorGeneralTypeMultedOnNum(atMatrix(&result, n) , &multiplier)));
        }
    }
    destructVectorPairInt(&indexes_of_first_non_zero);
    return result;
}

void printfMatrix(const Matrix * mat)
{
    for (int i = 0; i < mat->lines; ++i)
    {
        for (int j = 0; j < mat->columns; ++j)
        {
            printfGeneralType(catMatrixEl(mat, i, j));
        }
        printf("\n");
    }
    printf("\n");
}
