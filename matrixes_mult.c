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
        l = rand() % 150 + 2;
        c = rand() % 150 + 2;
        w = rand() % 150 + 2;
        MatrixInt a = scanfRandMatrixInt(l, c), b = scanfRandMatrixInt(c, w);
        MatrixInt r1 = naiveMultMatrixInt(&a, &b);
        MatrixInt r2 = multMatrixInt(&a, &b);
        if (!equalMatrixInt(&r1, &r2))
        {
            printf("ERROR:\n");
            printf("A:\n");
            printfMatrixInt(&a);
            printf("B:\n");
            printfMatrixInt(&b);
            printf("Naive:\n");
            printfMatrixInt(&r1);
            printf("Alg:\n");
            printfMatrixInt(&r2);
            getchar();
        }
        else
            printf("TEST %d: OK\n", i);
        destructMatrixInt(&a);
        destructMatrixInt(&b);
        destructMatrixInt(&r1);
        destructMatrixInt(&r2);

    }
}


int main(int argc, char * argv[])
{

#ifdef debug
    printf("Debug\n");
#endif
    setbuf(stdout, 0);
    srand(time(0));
    if (argc > 1)
    {
        if (strcmp(argv[1], "-test") == 0)
            test();

    }
    int size = 1024;
    time_t t1, t2;

    //MatrixInt a = scanfMatrixInt(), b = scanfMatrixInt();
   MatrixInt a = scanfRandMatrixInt(size, size), b = scanfRandMatrixInt(size, size);

    t1 = clock();

    MatrixInt c = multMatrixInt(&a, &b);
    t2 = clock();
    printf("Done %ld", t2 - t1);

    //printfMatrixInt(&c);

    destructMatrixInt(&a);
    destructMatrixInt(&b);
    destructMatrixInt(&c);
}