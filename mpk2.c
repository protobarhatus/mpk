#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct Polynom_struct
{
    int deg;
    int * pol;

};

typedef struct Polynom_struct Polynom;
Polynom defaultPolynom(int deg)
{
    Polynom res;
    res.deg = deg;
    res.pol = (int *)calloc(deg + 1, sizeof(int));
    return res;
}
typedef Polynom PolynomRef;

void destructPolynom(Polynom * obj)
{
    free(obj->pol);
    obj->pol = NULL;
}

void shrinkLeadZeroez(Polynom * p)
{
    while (p->pol[p->deg] == 0 && p->deg > 0)
        p->deg--;
}

void cumulativeAdd(Polynom * a, const Polynom * b)
{
    int i = 0;
    if (a->deg < b->deg)
    {
        // a->pol = (int *)realloc(a, (b->deg + 1) * sizeof(int));
        for (i = 0; i <= a->deg; ++i)
            a->pol[i] += b->pol[i];
        for (i = a->deg + 1; i < b->deg + 1; ++i)
            a->pol[i] = b->pol[i];
        a->deg = b->deg;
    }
    else
    {
        for (i = 0; i <= b->deg; ++i)
            a->pol[i] += b->pol[i];
    }
    shrinkLeadZeroez(a);
}

Polynom copyPolynom(const Polynom * a)
{
    Polynom res = defaultPolynom(a->deg);
    int i = 0;
    for (i = 0; i <= a->deg; ++i)
        res.pol[i] = a->pol[i];
    return res;
}

static int max(int a, int b)
{
    return a > b ? a : b;
}
static int min(int a, int b)
{
    return a < b ? a : b;
}

Polynom add(const Polynom * a, const Polynom * b)
{
    int deg_max = max(a->deg, b->deg);
    Polynom res = defaultPolynom(deg_max);
    int i = 0;
    if (a->deg >= b->deg)
    {
        for (i = 0; i <= b->deg; ++i)
            res.pol[i] = a->pol[i] + b->pol[i];
        for (i = b->deg + 1; i <= a->deg; ++i)
            res.pol[i] = a->pol[i];
    }
    else
    {
        for (i = 0; i <= a->deg; ++i)
            res.pol[i] = a->pol[i] + b->pol[i];
        for (i = a->deg + 1; i <= b->deg; ++i)
            res.pol[i] = b->pol[i];
    }
    shrinkLeadZeroez(&res);
    return res;
}
Polynom addRV(Polynom a, Polynom b)
{
    Polynom res = add(&a, &b);
    destructPolynom(&a);
    destructPolynom(&b);
    return res;
}

void cumulativeMultOnNum(Polynom * a, int n)
{
    int i = 0;
    for (i = 0; i <= a->deg; ++i)
        a->pol[i] *= n;
    shrinkLeadZeroez(a);
}

Polynom multOnNum(const Polynom * a, int k)
{
    Polynom res = defaultPolynom(a->deg);
    int i = 0;
    for (i = 0; i <= a->deg; ++i)
        res.pol[i] = a->pol[i] * k;
    shrinkLeadZeroez(&res);
    return res;
}

void cumulativeSubtract(Polynom * a, const Polynom * b)
{
    int i = 0;
    if (a->deg < b->deg)
    {
        //a->pol = (int *)realloc(a->pol, (b->deg + 1) * sizeof(int));
        for (i = 0; i <= a->deg; ++i)
            a->pol[i] -= b->pol[i];
        for (i = a->deg + 1; i <= b->deg; ++i)
            a->pol[i] = -b->pol[i];
        a->deg = b->deg;
    }
    else
    {
        for (i = 0; i <= b->deg; ++i)
            a->pol[i] -= b->pol[i];
    }
    shrinkLeadZeroez(a);
}

Polynom subtract(const Polynom * a, const Polynom * b)
{
    Polynom res = copyPolynom(a);
    cumulativeSubtract(&res, b);
    return res;
}
Polynom subtractRV(Polynom a, Polynom b)
{
    Polynom res = subtract(&a, &b);
    destructPolynom(&a);
    destructPolynom(&b);
    return res;
}
#define bool int
#define true 1
#define false 0
bool isZeroPolynom(const Polynom * a)
{
    return (a->deg == -1 || (a->deg == 0 && a->pol[0] == 0));
}
Polynom getZeroPolynom()
{
    return defaultPolynom(0);
}
bool isUnitPolynom(const Polynom * a)
{
    return a->deg == 0 && a->pol[0] == 1;
}

static int getXDeg(const Polynom * a, const Polynom * b)
{
    return max(a->deg / 2, b->deg / 2);
    return min(max(a->deg, b->deg) / 2, min(a->deg, b->deg));
}

Polynom getXInDegPolynom(int deg)
{
    Polynom res = defaultPolynom(deg);
    res.pol[deg] = 1;
    return res;
}
Polynom getXInDegPolynomMult(const Polynom * a, const Polynom * b)
{
    return getXInDegPolynom(a->deg + b->deg);
}

bool isPolynomConstantNumber(const Polynom * p)
{
    return p->deg == 0;
}
int polynomToConstantNumber(const Polynom * p)
{
    assert(isPolynomConstantNumber(p));
    return p->pol[0];
}
struct PairPolynom_struct
{
    PolynomRef first, second;
};
typedef struct PairPolynom_struct PairPolynom;
PairPolynom defaultPairPolynom(Polynom * a, Polynom * b)
{
    PairPolynom res;
    res.first = *a;
    res.second = *b;
    return res;
}

PairPolynom splitPolynomOnXInDeg(const Polynom * p, int x_deg)
{

    Polynom a;
    Polynom b;
    a.pol = &p->pol[x_deg];
    a.deg = p->deg - x_deg;
    b.pol = p->pol;
    b.deg = x_deg - 1;

    return defaultPairPolynom(&a, &b);
}


Polynom simpleMult(const Polynom * a, const Polynom * b)
{
    Polynom res = defaultPolynom(a->deg + b->deg);
    int i = 0, j = 0;
    for (i = 0; i <= a->deg; ++i)
    {
        for (j = 0; j <= b->deg; ++j)
            res.pol[i + j] += a->pol[i] * b->pol[j];
    }
    shrinkLeadZeroez(&res);
    return res;
}
void simpleMultOnBuff(Polynom * res, const Polynom * a, const Polynom * b)
{
    int i = 0, j = 0;
    res->deg = a->deg + b->deg;

    for (i = 0; i <= res->deg; ++i)
        res->pol[i] = 0;
    for (i = 0; i <= a->deg; ++i)
    {
        for (j = 0; j <= b->deg; ++j)
            res->pol[i + j] += a->pol[i] * b->pol[j];
    }
    shrinkLeadZeroez(res);
    // checkBoundry();
}
void addShiftedOnBuff(Polynom * buff, const Polynom * a, int shift_a, const Polynom * b, int shift_b)
{
    int i = 0;
    buff->deg = a->deg + shift_a;
    for (i = 0; i < shift_b; ++i)
        buff->pol[i] = 0;
    for (i = shift_b; i < shift_a; ++i)
        buff->pol[i] = b->pol[i - shift_b];
    for (i = shift_a; i <= buff->deg; ++i)
        buff->pol[i] = (i - shift_b <= b->deg ? b->pol[i - shift_b] : 0) + a->pol[i - shift_a];
    // checkBoundry();
}

void mult(Polynom * res, const Polynom * ap, const Polynom * bp)
{
    PairPolynom a_split, b_split;
    PolynomRef a, b, c, d;
    Polynom ac, bd, a_plus_b, c_plus_d, adsa;
    int x_deg = getXDeg(ap, bp);

    if (ap->deg <= 32 && bp->deg <= 32)
    {
        simpleMultOnBuff(res, ap, bp);

        return;
    }
    a_split = splitPolynomOnXInDeg(ap, x_deg);
    b_split = splitPolynomOnXInDeg(bp, x_deg);

    a = a_split.first;
    b = a_split.second;
    c = b_split.first;
    d = b_split.second;

    ac.pol = res->pol + x_deg * 2;
    ac.deg = a.deg + c.deg;
    mult(&ac, &a, &c);
    bd.pol = res->pol;
    bd.deg = b.deg + d.deg;
    mult(&bd, &b, &d);

    a_plus_b = add(&a, &b);
    c_plus_d = add(&c, &d);

    adsa = defaultPolynom(max(a_plus_b.deg + c_plus_d.deg, ac.deg));
    mult(&adsa, &a_plus_b, &c_plus_d);
    cumulativeSubtract(&adsa, &ac);
    cumulativeSubtract(&adsa, &bd);

    res->deg = ap->deg + bp->deg;
    for (int i = 0; i <= adsa.deg; ++i)
        res->pol[i + x_deg] += adsa.pol[i];

    shrinkLeadZeroez(res);
    destructPolynom(&a_plus_b);
    destructPolynom(&c_plus_d);

}


void printfPolynom(const Polynom * p)
{
    if (p->deg == -1)
        printf("%d", 0);
    for (int i = 0; i <= p->deg; ++i)
        printf("%d ", p->pol[i]);
    printf("\n");
}
Polynom scanfPolynom(int len)
{
    Polynom res = defaultPolynom(len - 1);
    int i = 0;
    for (i = 0; i < len; ++i)
        scanf("%d", &res.pol[i]);
    return res;
}


int main()
{
    int len1, len2;
    Polynom p1, p2, res;
    setbuf(stdout, 0);
    if (!scanf("%d%d", &len1, &len2))
        abort();

    p1 = scanfPolynom(len1);
    p2 = scanfPolynom(len2);

    res = defaultPolynom(p1.deg + p2.deg);
    mult(&res, &p1, &p2);
    shrinkLeadZeroez(&res);
    printfPolynom(&res);

    destructPolynom(&p1);
    destructPolynom(&p2);
    destructPolynom(&res);
    return 0;
}
