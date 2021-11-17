#include <stdlib.h>
#include <time.h>
#include "linear_algebra_elements/matrix.h"

MatrixInt scanfRandMatrixInt(int len, int columns)
{
    if (len == -1 && columns == -1)
        scanf("%d%d", &len, &columns);
    MatrixInt res = defaultMatrixInt(len, columns, 0);
    for (int i = 0; i < len; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            *atMatrixIntEl(&res, i, j) = rand() % 40 - 20;
        }
    }
    return res;
}


int test()
{
    for (int i = 0; i < 1000; ++i)
    {
        int l, c, w;
        l = rand() % 70 + 2;
        c = rand() % 70 + 2;
        w = rand() % 70 + 2;
        MatrixInt a = scanfRandMatrixInt(l, c), b = scanfRandMatrixInt(c, w);
        MatrixInt r1 = naiveMultMatrix(&a, &b);
        MatrixInt r2 = multMatrix(&a, &b);
        if (!equalMatrix(&r1, &r2))
        {
            printf("ERROR:\n");
            printf("A:\n");
            printfMatrix(&a);
            printf("B:\n");
            printfMatrix(&b);
            printf("Naive:\n");
            printfMatrix(&r1);
            printf("Alg:\n");
            printfMatrix(&r2);
        }
        else
            printf("TEST %d: OK\n", i);
        destructMatrix(&a);
        destructMatrix(&b);
        destructMatrix(&r1);
        destructMatrix(&r2);
    }
}


int main(int argc, char * argv[])
{
    setbuf(stdout, 0);
    srand(time(0));
    if (argc > 1)
    {
        if (strcmp(argv[1], "-test") == 0)
            test();

    }


    MatrixInt a = scanfMatrixInt(), b = scanfMatrixInt();

    MatrixInt c = multMatrix(&a, &b);

    printfMatrix(&c);

    destructMatrix(&a);
    destructMatrix(&b);
    destructMatrix(&c);
}