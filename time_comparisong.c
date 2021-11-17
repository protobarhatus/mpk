#include "Polynom/polynom.h"
#include <time.h>
#include <user_interacts/user_interactions.h>
#include <stdio.h>

int main()
{
    int len = getValue(stdin);
    Polynom p1 = scanfRandPolynom(len);
    Polynom p2 = scanfRandPolynom(len);

    forbidToomCook();
    clock_t t1 = clock();
    Polynom r1 = karatsuba(&p1, &p2);
    clock_t t2 = clock();
    printf("Karatsuba: %ld\n", t2 - t1);

    allowToomCook();
    t1 = clock();
    Polynom r2 = toomCookMultiplication(&p1, &p2);
    t2 = clock();
    printf("Toom cook: %ld\n", t2 - t1);

    t1 = clock();
    Polynom r3 = schonhageStrassenAlgorithm(&p1, &p2);
    t2 = clock();
    printf("Schonhage Strassen: %ld\n\n\n", t2 - t1);


    //in case if compilator decides to erase r1,r2,r3
    printf("%d %d %d", r1.deg, r2.deg, r3.deg);


    destructPolynom(&p1);
    destructPolynom(&p2);
    destructPolynom(&r1);
    destructPolynom(&r2);
    destructPolynom(&r3);
}

