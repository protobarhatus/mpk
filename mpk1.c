#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>


#include "Polynom/polynom.h"

static int max(int a, int b)
{
    return a > b ? a : b;
}
static int min(int a, int b)
{
    return a < b ? a : b;
}




static void tprintfPolynom(const Polynom * p)
{
    if (p->deg == -1)
        printf("%d", 0);
    for (int i = 0; i <= p->deg; ++i)
        printf("%lld ", p->polynom[i]);
    printf("\n");
}
static Polynom tscanfPolynom(int len)
{
    Polynom res = defaultPolynom(len - 1);
    int i = 0;
    for (i = 0; i < len; ++i)
        scanf("%lld", &res.polynom[i]);
    return res;
}


int main(int argc, char * argv[])
{
    forbidToomCook();
    srand(time(NULL));
    if (argc > 1 && strcmp(argv[1], "-t"))
    {
        testPolynoms(stdin, &karatsuba);
    }
    Polynom p1, p2, res;
    setbuf(stdout, 0);




    p1 = scanfPolynom(stdin);
    p2 = scanfPolynom(stdin);

    res = karatsuba(&p1, &p2);
    tprintfPolynom(&res);

    destructPolynom(&p1);
    destructPolynom(&p2);
    destructPolynom(&res);
    return 0;
}
