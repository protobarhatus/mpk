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

    DiscreteFourier naive = naiveDiscreteFourierTransformForPolynom(&pol);
    DiscreteFourier cooley = discreteFourierTransformForPolynom(&pol);

    if (!equalDiscreteFourier(&naive, &cooley))
    {
        printf("ERROR\n");
        printf("naive:--------\n");
        printfDiscreteFourier(&naive);
        printf("cooley:-------\n");
        printfDiscreteFourier(&cooley);
        getchar();
        return false;
    }
    destructPolynom(&pol);
    destructVectorComplex(&naive);
    destructVectorComplex(&cooley);
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
    Polynom pol = scanfRandPolynom(10000000);
    DiscreteFourier f = discreteFourierTransformForPolynom(&pol);
    printf("Done");
    getchar();
   // Polynom pol = scanfPolynom(stdin);
    VectorComplex  input = scanfVectorComplex();
    DiscreteFourier res = discreteFourierTransform(&input);

    printfDiscreteFourier(&res);

    destructVectorComplex(&input);
    destructVectorComplex(&res);
}
