#include <time.h>
#include "Polynom/polynom.h"
#include "stdlib.h"
#include "stdio.h"


int main(int argc, char * argv[])
{
    setbuf(stdout, 0);
    if (argc > 1 && strcmp(argv[1], "-t") == 0)
    {
        int len;
        scanf("%d", &len);
        testPolynoms(stdin, &simpleMult);
    }

    Polynom p1, p2, res;

    p1 = scanfPolynom(stdin);
    p2 = scanfPolynom(stdin);

    res = simpleMult(&p1, &p2);
    printfPolynom(&res);

    destructPolynom(&p1);
    destructPolynom(&p2);
    destructPolynom(&res);

    return 0;
}
