#include <time.h>
#include "Polynom/polynom.h"
#include "stdlib.h"
#include "stdio.h"


Polynom randPolynom(int size)
{
    Polynom res = defaultPolynom(size - 1);
    for (int i = 0; i < size; ++i)
    {
        *atPolynom(&res, i) = rand() % 40 - 20;
    }
    return res;
}

Polynom scanfRandPolynom(int len)
{
    if (len == -1)
        scanf("%d", &len);
    return randPolynom(len);
}

void strictTest(int len)
{
    for (int i = 0; i < 100; ++i)
    {
        Polynom p1 = scanfRandPolynom(len);
        Polynom p2 = scanfRandPolynom(len);

        Polynom r = toomCookMultiplication(&p1, &p2);
        Polynom r1 = multPolynom(&p1, &p2);
        Polynom r3 = simpleMult(&p1, &p2);
        if (!(areEqualPolynom(&r, &r1) && areEqualPolynom(&r, &r3)))
        {
            printfPolynom(&p1);
            printf("----\n");
            printfPolynom(&p2);
            printf("----\n");
            printfPolynom(&r);
            printf("----\n");
            printfPolynom(&r1);
            printf("----\n");
            printfPolynom(&r3);
            printf("----\n");
            getchar();
        }
    }
    printf("CORRECT\n");
}

void test(int len)
{
    if (len <= 1000)
    {
        strictTest(len);
        return;
    }
    for (int i = 0; i < 100; ++i)
    {
        Polynom p1 = scanfRandPolynom(len);
        Polynom p2 = scanfRandPolynom(len);

        Polynom r = toomCookMultiplication(&p1, &p2);
        Polynom r1 = karatsuba(&p1, &p2);
        if (!areEqualPolynom(&r, &r1))
        {
            printfPolynom(&p1);
            printf("----\n");
            printfPolynom(&p2);
            printf("----\n");
            printfPolynom(&r);
            printf("----\n");
            printfPolynom(&r1);
            printf("----\n");
            getchar();
        }
    }
    printf("CORRECT\n");
}

int main(int argc, char * argv[])
{
    setbuf(stdout, 0);
    srand(time(NULL));
    FILE * file;
    file = fopen("tests", "r");
    testPolynoms(file, &toomCookMultiplication);
    if (argc > 1 && strcmp(argv[1], "-t") == 0)
    {
        testPolynoms(stdin, &multPolynom);
    }
    if (argc > 1 && strcmp(argv[1], "-rt") == 0)
    {
        int len;
        scanf("%d", &len);
        test(len);
    }

    Polynom p1, p2, res;

    p1 = scanfPolynom(stdin);
    p2 = scanfPolynom(stdin);

    res = toomCookMultiplication(&p1, &p2);
    printfPolynom(&res);

    destructPolynom(&p1);
    destructPolynom(&p2);
    destructPolynom(&res);

    return 0;
}
