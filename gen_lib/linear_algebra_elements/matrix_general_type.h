#ifndef FIBONACHY_NIM_MATRIX_GENERAL_TYPE_H
#define FIBONACHY_NIM_MATRIX_GENERAL_TYPE_H
#include "../vector/vector.h"
#include "../types_and_functions_declarations/general_type.h"
struct Matrix_struct {

    VectorVectorGeneralType matrix;
    int lines, columns;
    VectorGeneralType * (*at)(struct Matrix_struct * a, int i);

    bool is_on_buffer;
    //its for matrix that is build on buffer. allocked_* means from its current start till end without considering allocked space behind
    int start_line, start_column, allocked_lines, allocked_columns;
    //thats made only in non buffered matrix
    GeneralType value_beyond_allocked_space;
    //thats for buffered matrix. reason is that for buffered matrixes it is preferable to be Ref, but Ref
    //dont require destructor
    const GeneralType * value_beyond_allocked_space_ptr;

};



typedef struct Matrix_struct Matrix;
typedef Matrix MatrixRef;

Matrix defaultMatrix(int lines, int columns, GeneralType def_value);
Matrix makeUnitMatrix(int n);

Matrix copyMatrix(const Matrix * mat);
Matrix moveMatrix(Matrix * mat);
void destructMatrix(Matrix * mat);
bool equalMatrix(const Matrix * a, const Matrix * b);

DECLARE_STRUCT_TYPE(Matrix, Matrix);

MatrixRef getMatrixOnBuffer(const Matrix * origin, int lines_start, int lines_finish, int lines, int columns);

void addToMatrix(Matrix * a, const Matrix * b);
void subToMatrix(Matrix * a, const Matrix * b);



Matrix addMatrix(const Matrix * a, const Matrix * b);
Matrix subMatrix(const Matrix * a, const Matrix * b);

Matrix multMatrix(const Matrix * a, const Matrix * b);
Matrix divMatrix(const Matrix * a, const Matrix * b);
void multToMatrix(Matrix * a, const Matrix * b);
void divToMatrix(Matrix * a, const Matrix * b);

Matrix unitMatrix();
Matrix nullMatrix();

Matrix minusMatrix(const Matrix * a);
Matrix sqrtMatrix(const Matrix * a);

DECLARE_TYPE_AS_ARITHMETIC(Matrix, Matrix);



static inline VectorGeneralType * atMatrix(Matrix * mat, int i)
{
    assert(!mat->is_on_buffer);
    return atVectorVectorGeneralType(&mat->matrix, i);
}
static inline const VectorGeneralType * catMatrix(const Matrix * mat, int i)
{
    assert(!mat->is_on_buffer);
    return catVectorVectorGeneralType(&mat->matrix, i);
}


static inline GeneralType * atMatrixEl(Matrix * mat, int i, int j)
{
    if (mat->is_on_buffer)
    {
        assert (i < mat->allocked_lines && j < mat->allocked_columns);
        return  atVectorGeneralType(atVectorVectorGeneralType(&mat->matrix, i + mat->start_line), j + mat->start_column);
    }
    assert(i < mat->lines && j < mat->columns);
    return &mat->matrix.vec[i].vec[j];
    return atVectorGeneralType(atVectorVectorGeneralType(&mat->matrix, i), j);
}
static inline const GeneralType * catMatrixEl(const Matrix * mat, int i, int j)
{
    if (mat->is_on_buffer)
    {
        if (i >= mat->allocked_lines || j >= mat->allocked_columns)
            return mat->value_beyond_allocked_space_ptr;
        return  catVectorGeneralType(catVectorVectorGeneralType(&mat->matrix, i + mat->start_line), j + mat->start_column);
    }
    assert(i < mat->lines && j < mat->columns);
    return &mat->matrix.vec[i].vec[j];
    return catVectorGeneralType(catVectorVectorGeneralType(&mat->matrix, i), j);
}
static inline void setValueToMatrix(Matrix * mat, int i, int j, GeneralType value)
{
    if (mat->is_on_buffer)
    {
        if (i >= mat->allocked_lines || j >= mat->allocked_columns)
            return;
    }
    replaceGeneralType(atMatrixEl(mat, i, j) , moveGeneralType(&value));
}

Matrix scanfMatrix();

Matrix inverseMatrix(Matrix * matrix);

GENERATE_RIGHT_VALUE_UNARY_EXTENSIONS(Matrix, Matrix, inverse, Matrix);
void printfMatrix(const Matrix * mat);

GENERATE_RIGHT_VALUE_UNARY_EXTENSIONS_TO_VOID_FUNC(Matrix, Matrix, printf)


Matrix naiveMultMatrix(const Matrix * a, const Matrix * b);




#endif //FIBONACHY_NIM_MATRIX_GENERAL_TYPE_H
