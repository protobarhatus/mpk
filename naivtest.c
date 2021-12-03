#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Matrix {
    int *data;
    int x, y;
};

void addtoint(int * a, const int * b)
{
    *a += *b;
}
void destructInt(int * a)
{

}
void addToInt(int * a, int b)
{
    addtoint(a, &b);
    destructInt(&b);
}
int multInt(const int* a, const int* b)
{
    return *a * *b;
}
int * atMatrix(int ** matrix, int x, int y, int w)
{
    assert(x < 2000 && y < 2000);
    return &((*matrix)[x * w + y]);
}

// A[AX][AY] * B[AY][BY] = C[AX][BY]
void matrix_mult(const int *A, const int *B, int *C, int AX, int AY, int BY) {
    assert(A != NULL && B != NULL && C != NULL);
    assert(AX > 0 && AY > 0 && BY > 0);
    C = calloc(AX * AY, sizeof(int));
    for(int i = 0; i < AX; i++)
        for(int j = 0; j < BY; j++) {
            C[i * BY + j] = 0;
            // Multiply and accumulate the values
            // in the current row of A and column of B
            for(int k = 0; k < AY; k++)
                C[i * BY + j] += A[i * AY + k] * B[k * BY + j];
                //addToInt(&C[i * BY + j], multInt(&A[i * AY + k], &B[k * BY + j]));
                //addToInt(atMatrix(&C, i, j, BY), multInt(atMatrix(&A, i, k, AY), atMatrix(&B, k, j,   BY)));
                //*atMatrix(&C, i, j, AX) += (*atMatrix(&A, i, k, AX)) * (*atMatrix(&B, k, j, AX));
        }
}

struct Matrix readMatrix() {
    struct Matrix M;
    int res, i, j;

    M.x = 1024;
    M.y = 1024;
    //assert(res == 2 && M.x > 0 && M.y > 0);
    M.data = malloc(sizeof(int) * M.x * M.y);
    assert(M.data);
    for (i = 0; i < M.x; ++i)
        for (j = 0; j < M.y; ++j) {
            //res = scanf("%d", M.data + i * M.y + j);
            //assert(res);
            *(M.data + i * M.y + j) = rand() % 40 - 20;
        }
    return M;
}

void printMatrix(struct Matrix M) {
    int i, j;
    for (i = 0; i < M.x; ++i) {
        for (j = 0; j < M.y; ++j) {
            printf("%d ", M.data[i * M.y + j]);
        }
        printf("\n");
    }
}

int main() {
    struct Matrix A = readMatrix();
    struct Matrix B = readMatrix();
    struct Matrix C;
    assert(B.x == A.y);

    C.data = malloc(sizeof(int) * A.x * B.y);
    C.x = A.x;
    C.y = B.y;

    time_t start = clock();
    matrix_mult(A.data, B.data, C.data, A.x, A.y, B.y);
    time_t fin = clock();
    long elapsed = fin - start;
    printf("Elapsed: %ld\n", elapsed);

#ifdef DEBUG
    printMatrix(C);
#endif
    printf("r:%d\n", *(C.data+4096));
    free(A.data);
    free(B.data);
    free(C.data);
}

