#include <stdio.h>
#include <time.h>
#include <user_interacts/user_interactions.h>
#include "Polynom/fourier.h"
#include "vector/algorithms.h"
bool testRandomFourier(int size)
{
    size = findNextPower(size);
    Polynom pol = randPolynom(size);
    for (int i = 0; i < size; ++i)
    {
        *atPolynom(&pol, i) = rand() % 40 - 20;
    }

    DiscreteFourier fourier = discreteFourierTransformForPolynom(&pol);
    Polynom res = inverseFourierTransformForPolynom(&fourier);

    if (!equalPolynom(&pol, &res))
    {
        printf("ERROR\n");
        printf("orig:--------\n");
        printfPolynom(&pol);
        printf("res:-------\n");
        printfPolynom(&res);
        getchar();
        return false;
    }
    destructPolynom(&pol);
    destructPolynom(&res);
    destructVectorComplex(&fourier);
    return true;
}

void testRandom(int len)
{
    for (int i = 0; i < 1000; ++i)
    {
        if (testRandomFourier(len))
            printf("TEST %d: OK\n", i);
    }
}

int main(int argc, char *argv[])
{
    setbuf(stdout, 0);
    srand(time(0));
    if (argc > 1 && strcmp(argv[1], "-test") == 0)
    {
        testRandom(getValue(stdin));
        return 0;
    }

    // Polynom pol = scanfPolynom(stdin);
    DiscreteFourier  input = scanfVectorComplex();
    VectorComplex res = inverseFourierTransform(&input);

    printfDiscreteFourier(&res);

    destructVectorComplex(&input);
    destructVectorComplex(&res);
}


