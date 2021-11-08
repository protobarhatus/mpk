#include <stdio.h>
#include "Polynom/fourier.h"

int main()
{
    setbuf(stdout, 0);
    Polynom pol = scanfPolynom(stdin);

    DiscreteFourier res = countDiscreteFourierTransform(&pol);

    for (int i = 0; i < res.getSize(&res); ++i)
    {
        printfComplex(atVectorComplex(&res, i));
        printf("; ");
    }



    destructPolynom(&pol);
    destructVectorComplex(&res);
}
