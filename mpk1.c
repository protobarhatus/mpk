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
        printf("%d ", p->pol[i]);
    printf("\n");
}
static Polynom tscanfPolynom(int len)
{
    Polynom res = defaultPolynom(len - 1);
    int i = 0;
    for (i = 0; i < len; ++i)
        scanf("%d", &res.pol[i]);
    return res;
}


int main()
{
    srand(time(NULL));
    int len1, len2;
    Polynom p1, p2, res;
    setbuf(stdout, 0);
    if (!scanf("%d%d", &len1, &len2))
        abort();



    p1 = tscanfPolynom(len1);
    p2 = tscanfPolynom(len2);

    res = multPolynom(&p1, &p2);
    tprintfPolynom(&res);

    destructPolynom(&p1);
    destructPolynom(&p2);
    destructPolynom(&res);
    return 0;
}
