#ifndef FIBONACHY_NIM_MATRIX_H
#define FIBONACHY_NIM_MATRIX_H
#include "../vector/vector.h"
#include "../types_and_functions_declarations/general_type.h"
struct Matrix_struct {
#define Matrix struct Matrix_struct

    VectorVectorGeneralType matrix;
    int lines, columns;
    VectorGeneralType * (*at)(Matrix * a, int i);
    CompleteTypePresenter type;

    bool is_on_buffer;
    //its for matrix that is build on buffer. allocked_* means from its current start till end without considering allocked space behind
    int start_line, start_column, allocked_lines, allocked_columns;
    //thats made only in non buffered matrix
    GeneralType value_beyond_allocked_space;
    //thats for buffered matrix. reason is that for buffered matrixes it is preferable to be Ref, but Ref
    //dont require destructor
    const GeneralType * value_beyond_allocked_space_ptr;

#undef Matrix
};



typedef struct Matrix_struct Matrix;
typedef Matrix MatrixRef;

Matrix defaultMatrix(int lines, int columns, GeneralType def_value, CompleteTypePresenter type);
Matrix makeUnitMatrix(int n, CompleteTypePresenter type);

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


Matrix inverseMatrix(Matrix * matrix);

GENERATE_RIGHT_VALUE_UNARY_EXTENSIONS(Matrix, Matrix, inverse, Matrix);
void printfMatrix(const Matrix * mat);

GENERATE_RIGHT_VALUE_UNARY_EXTENSIONS_TO_VOID_FUNC(Matrix, Matrix, printf)


Matrix naiveMultMatrix(const Matrix * a, const Matrix * b);

//Probably that's not so much reason to treat matrix on each type as separate type aside from dont messing with them, but
//it can be done just by accuracy. if all matrix are same type of structure its a little more flexible and simpler to add function cause dont need
//to write wrapping over this
//bad that division on vectors and matrix is principaly different but now its kinda experiment
//probably reason for declaring int as different structures is that its impossible to define proper scanfMatrix() function
//because type is uknown and so its impossible to declare correct IO type on matrix
#define MAKE_MATRIX(TN, UCN)                                                                                            \
typedef Matrix Matrix##UCN;                                                                                             \
static inline Matrix##UCN defaultMatrix##UCN(int lines, int columns, TN def_value)                                      \
{\
     return defaultMatrix(lines, columns, getGeneralTypeOn##UCN##RV(def_value), GET_COMPLETE_TYPE_PRESENTER(UCN));                                                                                                                       \
}                                                                                                                       \
static inline TN * atMatrix##UCN##El(Matrix##UCN * mat, int i, int j)                                                          \
{\
    return atGeneralType##UCN(atMatrixEl(mat, i, j));                                                                                                                        \
}                                                                                                                       \
static inline const TN * catMatrix##UCN##El(const Matrix##UCN * mat, int i, int j)                                      \
{\
    return catGeneralType##UCN(catMatrixEl(mat, i, j));                                                                                                                        \
}                                                                                                                       \
static inline Matrix##UCN scanfMatrix##UCN()                                       \
{\
    int lines = scanfInt(), columns = scanfInt();                                                                   \
    Matrix res = defaultMatrix##UCN(lines, columns, null##UCN());                                                       \
    for (int i = 0; i < lines; ++i)                                                                                     \
    {                                                                                                                   \
        for (int j = 0; j < columns; ++j)                                                                               \
        {                                                                                                               \
            *atMatrix##UCN##El(&res, i, j) = scanf##UCN();\
        }\
    }                                                                                                                   \
    return res;                                                                                                                        \
}





MAKE_MATRIX(int, Int);
MAKE_MATRIX(double, Double);



#endif //FIBONACHY_NIM_MATRIX_H
