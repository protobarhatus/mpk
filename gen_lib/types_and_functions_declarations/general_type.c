#include "general_type.h"

GeneralType defaultGeneralType(void * data, CompleteTypePresenter type)
{
    GeneralType res;
    res.type = type;
    res.data = data;
    res.state = GENERAL_TYPE_SPECIAL_STATE_NONE;
    return res;
}
GeneralType nullGeneralType()
{
    GeneralType res;
    res.type = GET_UNKNOWN_TYPE_PRESENTER;
    res.data = NULL;
    res.state = GENERAL_TYPE_SPECIAL_STATE_NULL;
    return res;
}
GeneralType unitGeneralType()
{
    GeneralType res;
    res.type = GET_UNKNOWN_TYPE_PRESENTER;
    res.data = NULL;
    res.state = GENERAL_TYPE_SPECIAL_STATE_UNIT;
    return res;
}

GeneralType copyGeneralType(const GeneralType * cop)
{
    void * data_cop = NULL;
    if (cop->data != NULL)
    {
        data_cop = calloc(1, cop->type.type->element_size);
        cop->type.type->cpy_func(data_cop, cop->data, cop->type.type->element_size);
    }
    GeneralType res = defaultGeneralType(data_cop, cop->type);

    return res;
}
GeneralType moveGeneralType(GeneralType * mov)
{
    GeneralType res = defaultGeneralType(mov->data, mov->type);
    mov->data = NULL;
    return res;
}
void destructGeneralType(GeneralType * obj)
{
    if (obj->data != NULL)
        obj->type.type->destruct_function(obj->data);
    free(obj->data);
}

bool isSpecialCase(const GeneralType * a)
{
    return a->state != GENERAL_TYPE_SPECIAL_STATE_NONE;
}

void printfGeneralType(const GeneralType * type)
{
    switch (type->state)
    {
        case GENERAL_TYPE_SPECIAL_STATE_NULL:
            printf("<UNDEF>(0) ");
            break;
        case GENERAL_TYPE_SPECIAL_STATE_UNIT:
            printf("<UNDEF>(1) ");
            break;
        case GENERAL_TYPE_SPECIAL_STATE_NONE:
            type->type.io_type->out(type->data);
            break;
        default:
            assert(false);
    }
}
GeneralType scanfGeneralType()
{
    //theoreticly there could be interesting logic but no
    assert(false);
    return nullGeneralType();
}

//yes its breaking const but its nesseccary
static void tryToResolveTypeForOneOfArguments(const GeneralType * a, const GeneralType * b)
{
    if (isSpecialCase(a) && !isSpecialCase(b))
        defineStateForGeneralType((GeneralType *)a, b->type);
    if (!isSpecialCase(a) && isSpecialCase(b))
        defineStateForGeneralType((GeneralType *)b, a->type);
}

GeneralType addGeneralType(const GeneralType * a, const GeneralType * b)
{
    tryToResolveTypeForOneOfArguments(a, b);
    if (isSpecialCase(a) || isSpecialCase(b))
    {
        if (a->state == GENERAL_TYPE_SPECIAL_STATE_NULL)
            return copyGeneralType(b);
        if (b->state == GENERAL_TYPE_SPECIAL_STATE_NULL)
            return copyGeneralType(a);
        assert(false);
    }
    //with no hacks by users and no attempts to access it not via interface, arithm_type is guaranteed to be same as type
    assert(areSameTypes(a->type.type, b->type.type));
    assert(a->data != NULL && b->data != NULL);
    void * new_data = calloc(1, a->type.type->element_size);
    assert(new_data != NULL);
    GeneralType res = defaultGeneralType(new_data, a->type);
    a->type.arithm_type->add(res.data, a->data, b->data);
    return res;
}
GeneralType subGeneralType(const GeneralType * a, const GeneralType * b)
{
    tryToResolveTypeForOneOfArguments(a, b);
    if (isSpecialCase(a) || isSpecialCase(b))
    {
        if (a->state == GENERAL_TYPE_SPECIAL_STATE_NULL)
            return copyGeneralType(b);
        if (b->state == GENERAL_TYPE_SPECIAL_STATE_NULL)
            return copyGeneralType(a);
        assert(false);
    }
    //with no hacks by users and no attempts to access it not via interface, arithm_type is guaranteed to be same as type
    assert(areSameTypes(a->type.type, b->type.type));
    assert(a->data != NULL && b->data != NULL);
    void * new_data = calloc(1, a->type.type->element_size);
    assert(new_data != NULL);
    GeneralType res = defaultGeneralType(new_data, a->type);
    a->type.arithm_type->sub(res.data, a->data, b->data);
    return res;
}
GeneralType multGeneralType(const GeneralType * a, const GeneralType * b)
{
    tryToResolveTypeForOneOfArguments(a, b);
    if (isSpecialCase(a) || isSpecialCase(b))
    {
        if (a->state == GENERAL_TYPE_SPECIAL_STATE_NULL)
            return isSpecialCase(b) ? nullGeneralType() : nullGeneralTypeOfCertainType(b->type);
        if (b->state == GENERAL_TYPE_SPECIAL_STATE_NULL)
            return isSpecialCase(a) ? nullGeneralType() : nullGeneralTypeOfCertainType(a->type);
        if (a->state == GENERAL_TYPE_SPECIAL_STATE_UNIT)
            return copyGeneralType(b);
        if (b->state == GENERAL_TYPE_SPECIAL_STATE_UNIT)
            return copyGeneralType(a);
        assert(false);
    }
    //with no hacks by users and no attempts to access it not via interface, arithm_type is guaranteed to be same as type
    assert(areSameTypes(a->type.type, b->type.type));
    assert(a->data != NULL && b->data != NULL);
    void * new_data = calloc(1, a->type.type->element_size);
    assert(new_data != NULL);
    GeneralType res = defaultGeneralType(new_data, a->type);
    a->type.arithm_type->mult(res.data, a->data, b->data);
    return res;
}
GeneralType divGeneralType(const GeneralType * a, const GeneralType * b)
{
    tryToResolveTypeForOneOfArguments(a, b);
    if (isSpecialCase(a) || isSpecialCase(b))
    {
        if (b->state == GENERAL_TYPE_SPECIAL_STATE_NULL)
            assert(false);
        if (a->state == GENERAL_TYPE_SPECIAL_STATE_NULL)
            return isSpecialCase(b) ? nullGeneralType() : nullGeneralTypeOfCertainType(b->type);
        if (b->state == GENERAL_TYPE_SPECIAL_STATE_UNIT)
            return copyGeneralType(a);
        assert(false);
    }
    //with no hacks by users and no attempts to access it not via interface, arithm_type is guaranteed to be same as type
    assert(areSameTypes(a->type.type, b->type.type));
    assert(a->data != NULL && b->data != NULL);
    void * new_data = calloc(1, a->type.type->element_size);
    assert(new_data != NULL);
    GeneralType res = defaultGeneralType(new_data, a->type);
    a->type.arithm_type->div(res.data, a->data, b->data);
    return res;
}

void addToGeneralType(GeneralType * a, const GeneralType * b)
{
    tryToResolveTypeForOneOfArguments(a, b);
    //expecting that they are both unresolved
    if (isSpecialCase(a))
    {
        if (b->state == GENERAL_TYPE_SPECIAL_STATE_NULL)
            return;
        if (a->state == GENERAL_TYPE_SPECIAL_STATE_NULL)
        {
            replaceGeneralType(a, copyGeneralType(b));
            return;
        }
        assert(false);
    }
    assert(areSameTypes(a->type.type, b->type.type));
    assert(a->data != NULL && b->data != NULL);
    a->type.arithm_type->addTo(a->data, b->data);
}
void subToGeneralType(GeneralType * a, const GeneralType * b)
{
    tryToResolveTypeForOneOfArguments(a, b);
    //expecting that they are both unresolved
    if (isSpecialCase(a))
    {
        if (b->state == GENERAL_TYPE_SPECIAL_STATE_NULL)
            return;
        if (a->state == GENERAL_TYPE_SPECIAL_STATE_NULL)
        {
            replaceGeneralType(a, copyGeneralType(b));
            return;
        }
        assert(false);
    }
    assert(areSameTypes(a->type.type, b->type.type));
    assert(a->data != NULL && b->data != NULL);
    a->type.arithm_type->subTo(a->data, b->data);
}
void multToGeneralType(GeneralType * a, const GeneralType * b)
{
    tryToResolveTypeForOneOfArguments(a, b);
    //expecting that they are both unresolved
    if (isSpecialCase(a))
    {
        if (a->state == GENERAL_TYPE_SPECIAL_STATE_NULL)
            return;
        if (b->state == GENERAL_TYPE_SPECIAL_STATE_NULL)
        {
            replaceGeneralType(a, copyGeneralType(b));
            return;
        }
        if (b->state == GENERAL_TYPE_SPECIAL_STATE_UNIT)
            return;
        if (a->state == GENERAL_TYPE_SPECIAL_STATE_UNIT)
        {
            replaceGeneralType(a, copyGeneralType(b));
            return;
        }

        assert(false);
    }
    assert(areSameTypes(a->type.type, b->type.type));
    assert(a->data != NULL && b->data != NULL);
    a->type.arithm_type->multTo(a->data, b->data);
}
void divToGeneralType(GeneralType * a, const GeneralType * b)
{
    tryToResolveTypeForOneOfArguments(a, b);
    //expecting that they are both unresolved
    if (isSpecialCase(a))
    {
        if (b->state == GENERAL_TYPE_SPECIAL_STATE_NULL)
            assert(false);
        if (a->state == GENERAL_TYPE_SPECIAL_STATE_NULL)
            return;
        if (b->state == GENERAL_TYPE_SPECIAL_STATE_UNIT)
            return;
        assert(false);
    }
    assert(areSameTypes(a->type.type, b->type.type));
    assert(a->data != NULL && b->data != NULL);
    a->type.arithm_type->divTo(a->data, b->data);
}

GeneralType sqrtGeneralType(const GeneralType * a)
{
    if (isSpecialCase(a))
    {
        if (a->state == GENERAL_TYPE_SPECIAL_STATE_NULL)
            return nullGeneralType();
        if (a->state == GENERAL_TYPE_SPECIAL_STATE_UNIT)
            return unitGeneralType();
        assert(false);
    }
    assert(a->data != NULL);
    void * new_data = calloc(1, a->type.type->element_size);
    assert(new_data != NULL);
    a->type.arithm_type->sqrt(new_data, a->data);
    GeneralType res = defaultGeneralType(new_data, a->type);
    return res;
}
GeneralType minusGeneralType(const GeneralType * a)
{
    if (isSpecialCase(a))
    {
        if (a->state == GENERAL_TYPE_SPECIAL_STATE_NULL)
            return copyGeneralType(a);
        assert(false);
    }
    void * data = calloc(1, a->type.type->element_size);
    assert(data != NULL);
    a->type.arithm_type->minus(data, a->data);
    GeneralType res = defaultGeneralType(data, a->type);
    return res;
}



void defineStateForGeneralType(GeneralType * obj, CompleteTypePresenter type)
{
    obj->type = type;
    switch (obj->state)
    {
        case GENERAL_TYPE_SPECIAL_STATE_NONE:
            break;
        case GENERAL_TYPE_SPECIAL_STATE_NULL:
            replaceGeneralType(obj, nullGeneralTypeOfCertainType(type));
            break;
        case GENERAL_TYPE_SPECIAL_STATE_UNIT:
            replaceGeneralType(obj, unitGeneralTypeOfCertainType(type));
            break;
        default:
            assert(false);
    }
    obj->state = GENERAL_TYPE_SPECIAL_STATE_NONE;
}


GeneralType nullGeneralTypeOfCertainType(CompleteTypePresenter type)
{
    void * data = type.arithm_type->callocZeroValue();
    assert(data != NULL);
    return defaultGeneralType(data, type);
}
GeneralType unitGeneralTypeOfCertainType(CompleteTypePresenter type)
{
    void * data = type.arithm_type->callocUnitValue();
    assert(data != NULL);
    return defaultGeneralType(data, type);
}
bool isNullGeneralType(const GeneralType * a)
{
    GeneralType null = nullGeneralTypeOfCertainType(a->type);
    bool res =  a->state == GENERAL_TYPE_SPECIAL_STATE_NULL || a->type.type->equal_function(a->data, null.data, a->type.type->element_size);
    destructGeneralType(&null);
    return res;
}
bool equalGeneralType(const GeneralType * a, const GeneralType * b)
{
    tryToResolveTypeForOneOfArguments(a, b);
    if (isSpecialCase(a))
        return a->state == b->state;
    assert(areSameTypes(a->type.type, b->type.type));
    return a->type.type->equal_function(a->data, b->data, a->type.type->element_size);
}