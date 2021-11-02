#include "polynom.h"
#include "../gen_lib/linear_algebra_elements/matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
/* so, toom-cook algorithm requires splitting numbers into polynoms with base no more then k. Since i am
 * working with polynoms, i will assume these are numbers in base 2^(64) (2^(sizeof(long long int)*CHAR_BIT))
 * (amount of digits equall amount of coefficients) (and i will hope there will be no overflow)
 * and that negative digits wont mess up it*/

typedef struct Polynom_struct Polynom;
Polynom defaultPolynom(int deg)
{
    Polynom res;
    res.deg = deg;
    if (deg + 1 > 0)
        res.polynom = (long long int *)calloc(deg + 1, sizeof(long long int));
    return res;
}
typedef Polynom PolynomRef;

void destructPolynom(Polynom * obj)
{
    free(obj->polynom);
    obj->polynom = NULL;
}
Polynom movePolynom(Polynom * pol)
{
    Polynom res;
    res.deg = pol->deg;
    res.polynom = pol->polynom;
    pol->polynom = NULL;
    return res;
}

void shrinkLeadZeroez(Polynom * p)
{
    while (*atPolynom(p, p->deg) == 0 && p->deg > 0)
        p->deg--;
}

void addToPolynom(Polynom * a, const Polynom * b)
{
    int i = 0;
    if (a->deg < b->deg)
    {
         a->polynom = (long long int *)realloc(a->polynom, (b->deg + 1) * sizeof(long long int));
         int old_deg = a->deg;
        a->deg = b->deg;
        for (i = 0; i <= old_deg; ++i)
            *atPolynom(a, i) += *catPolynom(b, i);
        for (i = old_deg + 1; i < b->deg + 1; ++i)
            *atPolynom(a, i) = *catPolynom(b, i);

    }
    else
    {
        for (i = 0; i <= b->deg; ++i)
            *atPolynom(a, i) += *catPolynom(b, i);
    }
    shrinkLeadZeroez(a);
}

Polynom copyPolynom(const Polynom * a)
{

    Polynom res = defaultPolynom(a->deg);
    int i = 0;
    if (a->polynom == NULL)
    {
        res.polynom = NULL;
        return res;
    }
    for (i = 0; i <= a->deg; ++i)
        res.polynom[i] = a->polynom[i];
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

Polynom emptyPolynom()
{
    Polynom res;
    res.deg = -1;
    res.polynom = NULL;
    return res;
}

Polynom addPolynom(const Polynom * a, const Polynom * b)
{
    int deg_max = max(a->deg, b->deg);
    Polynom res = defaultPolynom(deg_max);
    int i = 0;
    if (a->deg >= b->deg)
    {
        for (i = 0; i <= b->deg; ++i)
            *atPolynom(&res, i) = *catPolynom(a, i) + *catPolynom(b, i);
        for (i = b->deg + 1; i <= a->deg; ++i)
            *atPolynom(&res, i) = *catPolynom(a, i);
    }
    else
    {
        for (i = 0; i <= a->deg; ++i)
            *atPolynom(&res, i) = *catPolynom(a, i) + *catPolynom(b, i);
        for (i = a->deg + 1; i <= b->deg; ++i)
            *atPolynom(&res, i) = *catPolynom(b, i);
    }
    shrinkLeadZeroez(&res);
    return res;
}
Polynom addRV(Polynom a, Polynom b)
{
    Polynom res = addPolynom(&a, &b);
    destructPolynom(&a);
    destructPolynom(&b);
    return res;
}

void cumulativeMultOnNum(Polynom * a, int n)
{
    int i = 0;
    for (i = 0; i <= a->deg; ++i)
        *atPolynom(a, i) *= n;
    shrinkLeadZeroez(a);
}

Polynom multOnNum(const Polynom * a, long long int k)
{
    Polynom res = defaultPolynom(a->deg);
    int i = 0;
    for (i = 0; i <= a->deg; ++i)
        *atPolynom(&res, i) = *catPolynom(a, i) * k;
    shrinkLeadZeroez(&res);
    return res;
}

void cumulativeSubtract(Polynom * a, const Polynom * b)
{
    int i = 0;
    if (a->deg < b->deg)
    {
        //assert(false);
        a->polynom = (long long int *)realloc(a->polynom, (b->deg + 1) * sizeof(long long int));
        for (int j = a->deg + 1; j <= b->deg; ++j)
            a->polynom[j] = 0;
        int old_deg = a->deg;
        a->deg = b->deg;
        for (i = 0; i <= old_deg; ++i)
            *atPolynom(a, i) -= *catPolynom(b, i);
        for (i = old_deg + 1; i <= b->deg; ++i)
            *atPolynom(a, i) = -(*catPolynom(b, i));

    }
    else
    {
        for (i = 0; i <= b->deg; ++i)
            *atPolynom(a, i) -= *catPolynom(b, i);
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

bool isZeroPolynom(const Polynom * a)
{
    return (a->deg == -1 || (a->deg == 0 && *catPolynom(a, 0) == 0));
}
Polynom getZeroPolynom()
{
    return defaultPolynom(0);
}
bool isUnitPolynom(const Polynom * a)
{
    return a->deg == 0 && *catPolynom(a, 0) == 1;
}



Polynom getXInDegPolynom(int deg)
{
    Polynom res = defaultPolynom(deg);
    *atPolynom(&res, deg) = 1;
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
long long int polynomToConstantNumber(const Polynom * p)
{
    assert(isPolynomConstantNumber(p));
    return *catPolynom(p, 0);
}

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
    a.polynom = &p->polynom[x_deg];
    a.deg = p->deg - x_deg;
    b.polynom = p->polynom;
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
            *atPolynom(&res, i + j) += *catPolynom(a, i) * *catPolynom(b, j);
    }
    shrinkLeadZeroez(&res);
    return res;
}
void simpleMultOnBuff(Polynom * res, const Polynom * a, const Polynom * b)
{
    int i = 0, j = 0;
    res->deg = a->deg + b->deg;

    for (i = 0; i <= res->deg; ++i)
        *atPolynom(res, i) = 0;
    for (i = 0; i <= a->deg; ++i)
    {
        for (j = 0; j <= b->deg; ++j)
            *atPolynom(res, i + j) += *catPolynom(a, i) * (*catPolynom(b, j));
    }
    shrinkLeadZeroez(res);
    // checkBoundry();
}
void addShiftedOnBuff(Polynom * buff, const Polynom * a, int shift_a, const Polynom * b, int shift_b)
{
    int i = 0;
    assert(buff->deg >= a->deg + shift_a);
    buff->deg = a->deg + shift_a;
    for (i = 0; i < shift_b; ++i)
        *atPolynom(buff, i) = 0;
    for (i = shift_b; i < shift_a; ++i)
        *atPolynom(buff, i) = *catPolynom(b, i - shift_b);
    for (i = shift_a; i <= buff->deg; ++i)
        *atPolynom(buff, i) = (i - shift_b <= b->deg ? *catPolynom(b, i - shift_b) : 0) + *catPolynom(a, i - shift_a);
    // checkBoundry();
}
static int getXDeg(const Polynom * a, const Polynom * b)
{
    return max(a->deg / 2, b->deg / 2);
    return min(max(a->deg, b->deg) / 2, min(a->deg, b->deg));
}

void printfAsWolfram(const Polynom * pol)
{
    for (int i = 0; i <= pol->deg; ++i)
    {
        printf("+%lld*x^%d ", *catPolynom(pol, i), i);
    }
    printf("\n\n\n\n\n");
}

Polynom karatsuba(const Polynom * ap, const Polynom * bp)
{
    PairPolynom a_split, b_split;
    PolynomRef a, b, c, d;
    Polynom ac, bd, res, a_plus_b, c_plus_d;
    Polynom a_plus_b_mult_c_plus_d_minus_stuff;
    int x_deg = getXDeg(ap, bp);
    a_split = splitPolynomOnXInDeg(ap, x_deg);
    b_split = splitPolynomOnXInDeg(bp, x_deg);

    a = a_split.first;
    b = a_split.second;
    c = b_split.first;
    d = b_split.second;

    ac = multPolynom(&a, &c);

    bd = multPolynom(&b, &d);

    a_plus_b = addPolynom(&a, &b);
    c_plus_d = addPolynom(&c, &d);
    a_plus_b_mult_c_plus_d_minus_stuff = multPolynom(&a_plus_b, &c_plus_d);

    cumulativeSubtract(&a_plus_b_mult_c_plus_d_minus_stuff, &ac);
    cumulativeSubtract(&a_plus_b_mult_c_plus_d_minus_stuff, &bd);

    res = defaultPolynom(ap->deg + bp->deg);
    addShiftedOnBuff(&res, &ac, x_deg * 2, &a_plus_b_mult_c_plus_d_minus_stuff, x_deg);
    addToPolynom(&res, &bd);

    destructPolynom(&ac);
    destructPolynom(&bd);
    destructPolynom(&a_plus_b_mult_c_plus_d_minus_stuff);
    destructPolynom(&a_plus_b);
    destructPolynom(&c_plus_d);

    return res;
}
Polynom multPolynom(const Polynom * ap, const Polynom * bp)
{

    if (isZeroPolynom(ap) || isZeroPolynom(bp))
        return getZeroPolynom();
    if (isPolynomConstantNumber(ap))
        return multOnNum(bp, polynomToConstantNumber(ap));
    if (isPolynomConstantNumber(bp))
        return multOnNum(ap, polynomToConstantNumber(bp));
    if (ap->deg <= 100 && bp->deg <= 100)
        return simpleMult(ap, bp);
    if (ap->deg <= 7000 && bp->deg <= 7000)
        return karatsuba(ap, bp);
    return toomCookMultiplication(ap, bp);
}


bool areEqualPolynom(const Polynom * a, const Polynom * b)
{
    if (a->deg != b->deg)
        return false;
    for (int i = 0; i < a->deg; ++i)
        if (*catPolynom(a, i) != *catPolynom(b, i))
            return false;

    return true;
}

struct PolynomOfPolynoms_struct
{
    int deg;
    VectorPolynomRef polynoms;
};
typedef struct PolynomOfPolynoms_struct PolynomOfPolynoms;
PolynomOfPolynoms defaultPolynomOfPolynoms(int deg)
{
    Polynom empty_polynom;
    empty_polynom.deg = 0;
    PolynomOfPolynoms res;
    res.deg = deg;
    res.polynoms = defaultVectorPolynomRefCalloc(deg + 1, empty_polynom);
    return res;
}
void destructPolynomOfPolynoms(PolynomOfPolynoms * pol)
{
    destructVectorPolynomRef(&pol->polynoms);
}



static Matrix makeCoefficientMatrixForToomCook(int final_deg)
{
    Matrix coef_matrix = defaultMatrix(final_deg + 1, final_deg + 1, nullRational());
    *coef_matrix.at(&coef_matrix, 0, 0) = unitRational();
    int point = 1;
    for (int i = 1; i < final_deg; ++i)
    {
        int cumul_point_power = 1;
        for (int j = 0; j <= final_deg; ++j)
        {
            *coef_matrix.at(&coef_matrix, i, j) = defaultRational(cumul_point_power, 1);
            cumul_point_power *= point;
        }
        if (point > 0)
            point *= -1;
        else
            point = -point + 1;
    }
    *coef_matrix.at(&coef_matrix, final_deg, final_deg) = unitRational();
    return coef_matrix;
}



static int chooseBaseExponent(const Polynom * a, const Polynom * b, int ka, int kb)
{
    return max((a->deg + 1) / ka + ((a->deg + 1) % ka != 0 ? 1 : 0), (b->deg + 1)/kb + ((b->deg + 1) % kb != 0 ? 1 : 0));
}

static void splitPolynom(PolynomOfPolynoms * p, Polynom * orig, int base_exponent, int k)
{
    *p = defaultPolynomOfPolynoms(k - 1);
    for (int i = 0; i < k; ++i)
    {
        if (i == k - 1)
        {
            p->polynoms.at(&p->polynoms, i)->polynom = atPolynom(orig, i * base_exponent);
            if ((orig->deg + 1) % base_exponent == 0)
            {
                p->polynoms.at(&p->polynoms, i)->deg = (base_exponent) - 1;
            }
            else
            {
                /*Polynom * last_polynom = p->polynoms.at(&p->polynoms, i);
                *last_polynom = defaultPolynom(base_exponent - 1);
                for (int ind = i * base_exponent; ind <= orig->deg; ++ind)
                    last_polynom->pol[ind - i * base_exponent] = orig->pol[ind];*/

                p->polynoms.at(&p->polynoms, i)->deg = (orig->deg + 1) % base_exponent - 1;
            }

        }
        else
        {
            p->polynoms.at(&p->polynoms, i)->deg = base_exponent - 1;
            p->polynoms.at(&p->polynoms, i)->polynom = atPolynom(orig, i * base_exponent);
        }
    }
}

static void split(PolynomOfPolynoms * p, PolynomOfPolynoms * q, Polynom * a_orig, Polynom * b_orig, int base_exponent, int ka, int kb)
{
    splitPolynom(p, a_orig, base_exponent, ka);
    splitPolynom(q, b_orig, base_exponent, kb);
}

//inverse matrix have rational nums in it. wikipedia says result coefficient will be integers any way,
//but i'm afraid i may lose something in between in this multiplication, as there is no guarantee (idk?)
//that all coefficients divides onto all denominators that they will face
struct PolynomRational_struct
{
    int deg;
    VectorRational pol;
};
typedef struct PolynomRational_struct PolynomRational;
PolynomRational defaultPolynomRational(int deg, Rational def_value)
{
    PolynomRational res;
    res.deg = deg;
    res.pol = defaultVectorRationalCalloc(deg + 1, def_value);
    return res;
}
PolynomRational emptyPolynomRational()
{
    PolynomRational res;
    res.deg = 0;
    res.pol = emptyVectorRational();
    return res;
}
PolynomRational copyPolynomRational(const PolynomRational * cop)
{
    PolynomRational res;
    res.deg = cop->deg;
    res.pol = copyVectorRational(&cop->pol);
    return res;
}
PolynomRational movePolynomRational(PolynomRational * mov)
{
    PolynomRational res;
    res.deg = mov->deg;
    res.pol = moveVectorRational(&mov->pol);
    return res;
}
void destructPolynomRational(PolynomRational * pol)
{
    pol->deg = 0;
    destructVectorRational(&pol->pol);
}
PolynomRational toPolynomRationalFromPolynom(const Polynom * pol)
{
    PolynomRational res = defaultPolynomRational(pol->deg, unitRational());
    for (int i = 0; i <= res.deg; ++i)
        *res.pol.at(&res.pol, i) = defaultRational(*catPolynom(pol, i), 1);
    return res;
}
void addToPolynomRational(PolynomRational * pol, const PolynomRational * sec)
{
    assert(pol->deg >= sec->deg);
    for (int i = 0; i <= sec->deg; ++i)
        addToRational(atVectorRational(&pol->pol, i), catVectorRational(&sec->pol, i));
}
void multPolynomRationalOn(PolynomRational * pol, Rational koe)
{
    for (int i = 0; i <= pol->deg; ++i)
        multToRational(atVectorRational(&pol->pol, i), &koe);
}

GENERATE_RIGHT_VALUE_UNARY_EXTENSIONS(Polynom, Polynom, toPolynomRationalFrom, PolynomRational);

DECLARE_STRUCT_TYPE(PolynomRational, PolynomRational);

MAKE_VECTOR(PolynomRational, PolynomRational);

static Polynom getValueInPointOfPolynomOfPolynom(const PolynomOfPolynoms * pol, int point, int base_exponent)
{
    Polynom res = defaultPolynom(base_exponent - 1);
    int mult_coe = 1;
    for (int i = 0; i <= pol->deg; ++i)
    {
        Polynom res_mult = multOnNum(pol->polynoms.cat(&pol->polynoms, i), mult_coe);
        addToPolynom(&res, &res_mult);
        destructPolynom(&res_mult);
        mult_coe *= point;
    }
    return res;
}

static Polynom toPolynomFromPolynomRational(const PolynomRational * pol)
{
    Polynom res = defaultPolynom(pol->deg);
    for (int i = 0; i <= pol->deg; ++i)
    {
        assert(catVectorRational(&pol->pol, i)->denom == 1);
        *atPolynom(&res, i) = catVectorRational(&pol->pol, i)->num;
    }
    return res;
}

static VectorPolynom multMatrixOfRationalOnVectorOfPolynoms(const Matrix * mat, const VectorPolynomRational * vec, int base_exponent)
{
    int lines = vec->getSize(vec);
    VectorPolynomRational preresult = defaultVectorPolynomRationalCalloc(lines,
                                                                         defaultPolynomRational((base_exponent - 1)*2 + 1, nullRational()));
    for (int i = 0; i < lines; ++i)
    {
        for (int j = 0; j < lines; ++j)
        {
            PolynomRational buff = copyPolynomRational(catVectorPolynomRational(vec, j));
            multPolynomRationalOn(&buff, *catMatrixEl(mat, i, j));
            addToPolynomRational(atVectorPolynomRational(&preresult, i), &buff);
            destructPolynomRational(&buff);
        }
    }
    VectorPolynom result = defaultVectorPolynomCalloc(lines, emptyPolynom());
    for (int i = 0; i < lines; ++i)
        *atVectorPolynom(&result, i) = toPolynomFromPolynomRational(atVectorPolynomRational(&preresult, i));
    destructVectorPolynomRational(&preresult);
    return result;
}

void printfPolynomRational(const PolynomRational * pol)
{
    printf("%d| ", pol->deg);
    for (int i = 0; i <= pol->deg; ++i)
        printfRational(catVectorRational(&pol->pol, i));
    printf("\n");
}

Polynom toomCookMultiplication(const Polynom * a, const Polynom * b)
{

    int ka = 3, kb = 3;
    int I = chooseBaseExponent(a, b, ka, kb);

    PolynomOfPolynoms p, q;
    split(&p, &q, a, b, I, ka, kb);

    int res_deg_of_dig = p.deg + q.deg;

    Matrix coe_matrix = inverseMatrixRV(makeCoefficientMatrixForToomCook(res_deg_of_dig));

    VectorPolynomRational values_at_points = defaultVectorPolynomRationalCalloc(res_deg_of_dig + 1, emptyPolynomRational());
    int point = 0;
    for (int i = 0; i < res_deg_of_dig; ++i)
    {

        *values_at_points.at(&values_at_points, i) = toPolynomRationalFromPolynomRV(multPolynomRV(
                getValueInPointOfPolynomOfPolynom(&p, point, I),
                getValueInPointOfPolynomOfPolynom(&q, point, I)));
        if (point <= 0)
            point = -point + 1;
        else
            point = -point;
    }
    *values_at_points.at(&values_at_points, res_deg_of_dig) = toPolynomRationalFromPolynomRV(multPolynom(
            p.polynoms.cat(&p.polynoms, p.deg), q.polynoms.cat(&q.polynoms, q.deg)
            )) ;


    //well, its better to write multiplication of matrix on vector as normal, but
    //i don't wanna think how to correctly generalize multiplication of different types
    VectorPolynom coefficients_of_result = multMatrixOfRationalOnVectorOfPolynoms(&coe_matrix, &values_at_points, I);
    int coe_size = coefficients_of_result.getSize(&coefficients_of_result);
    Polynom result = defaultPolynom(a->deg + b->deg);

    for (int i = 0; i < coe_size; ++i)
    {

        Polynom * this_coe = atVectorPolynom(&coefficients_of_result, i);
        shrinkLeadZeroez(this_coe);
        int this_coe_deg = this_coe->deg;

        for (int j = 0; j <= this_coe_deg; ++j)
        {
            if (j + i * I > result.deg)
                assert(false);
            *atPolynom(&result, j + i * I) += *atPolynom(this_coe, j);
        }

    }

    //destruction is unneeded because they actually didnt calloc anythinq, but i better write it just fo rules
    destructPolynomOfPolynoms(&p);
    destructPolynomOfPolynoms(&q);

    destructMatrix(&coe_matrix);
    destructVectorPolynomRational(&values_at_points);
    destructVectorPolynom(&coefficients_of_result);

    shrinkLeadZeroez(&result);

    return result;
}


void printfPolynom(const Polynom * p)
{
    if (p->deg == -1)
        printf("%d", 0);
    for (int i = 0; i <= p->deg; ++i)
        printf("%lld ", *catPolynom(p, i));
    printf("\n");
}
Polynom scanfPolynom()
{
    int len = 0;
    scanf("%d", &len);
    Polynom res = defaultPolynom(len - 1);
    int i = 0;
    for (i = 0; i < len; ++i)
        scanf("%lld", atPolynom(&res, i));
    return res;
}
