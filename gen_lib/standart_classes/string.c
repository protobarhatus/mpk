#include "string.h"

//+1 should always be for terminal sym
static inline int allocationSize(int len)
{
    //300 is random just not very big not very small. strings are not resized as often as vectors so double mem if len is like 10000
    //is excessive
    return (len > 300 ? len + 20 : 2*len + 1);
}
String defaultString(const char * string)
{
    String res = createString(strlen(string));

    for (int i = 0; i < res.length; ++i)
        res.string[i] = string[i];
    return res;
}

String createString(int length)
{
    String res;
    res.length = length;
    res.allocated_space = allocationSize(res.length);
    res.string = calloc(res.allocated_space, 1);
    res.string[res.length] = '\0';
}

String emptyString()
{
    return createString(0);
}

String copyString(const String * str)
{
    String res;
    res.length = str->length;
    res.allocated_space = str->allocated_space;
    res.string = calloc(res.allocated_space, 1);
    for (int i = 0; i <= str->length; ++i)
        res.string[i] = str->string[i];
    return res;
}

String moveString(String * str)
{
    String res = *str;
    str->string = NULL;
    str->length = -2;
    str->allocated_space = -2;
    return res;
}

void destructString(String * str)
{
    free(str->string);
    str->string = NULL;
    str->length = -2;
    str->allocated_space = -2;
}

StringRef wrapStandartString(const char * string)
{
    StringRef res;
    res.length = strlen(string);
    res.string = (char*)string;
    res.allocated_space = -2;
    return res;
}

StringRef wrapString(const String * str, int shift)
{
    assert(shift <= str->length);
    StringRef res;
    res.length = str->length - shift;
    res.allocated_space = -2;
    res.string = str->string + shift;
    return res;
}

void resizeString(String * str, int new_length)
{
    if (new_length > str->length)
        extendString(str, new_length);
    else
        shrinkString(str, new_length);
}
void shrinkString(String * str, int new_length)
{
    assert(new_length <= str->length);
    for (int i = str->length - 1; i >= new_length; --i)
        str->string[i] = '\0';
    str->length = new_length;
}
void extendString(String * str, int new_length)
{
    assert(new_length >= str->length);
    if (str->allocated_space > new_length)
    {
        for (int i = str->length + 1; i <= new_length; ++i)
            str->string[i] = '\0';
        str->length = new_length;
        return;
    }
    str->allocated_space = allocationSize(new_length);
    str->string = realloc(str->string, str->allocated_space);
    for (int i = str->length + 1; i <= new_length; ++i)
        str->string[i] = '\0';
    str->length = new_length;


}

void concatToString(String * str, const String * right)
{
    int old_length = str->length;
    extendString(str, str->length + right->length);
    for (int i = 0; i < right->length; ++i)
        str->string[old_length + i] = right->string[i];
}

String concatString(const String * a, const String * b)
{
    String res = createString(a->length + b->length);
    for (int i = 0; i < a->length; ++i)
        res.string[i] = a->string[i];
    for (int i = 0; i < b->length; ++i)
        res.string[i + a->length] = b->string[i];
    return res;
}

VectorInt makePiFunction(const String * str)
{
    VectorInt res = defaultVectorIntWithStrictSizeRV(str->length, 0);
    int i, k;
    *atVectorInt(&res, 0) = 0;

    for (i = 1; str->string[i] != '\0'; ++i)
    {
        k = *atVectorInt(&res, i - 1);

        while (k > 0 && str->string[i] != str->string[k])
        {
            k = *atVectorInt(&res, k - 1);
        }
        if (str->string[i] == str->string[k])
            ++k;
        *atVectorInt(&res, i) = k;
    }
    return res;
}

int findSubString(const String * str, const String * substr)
{
    int need_len = substr->length;
    int ind = 0, k = 0;
    VectorInt p_func = makePiFunction(substr);

    ind = 0;

    while (str->string[ind] != '\0')
    {
        while (k > 0 && str->string[ind] != substr->string[k])
        {
            k = *atVectorInt(&p_func, k - 1);
        }
        if (str->string[ind] == substr->string[k])
            k = k + 1;
        if (k == need_len)
        {
            destructVectorInt(&p_func);
            return ind - need_len + 1;
        }
        ++ind;
    }


    destructVectorInt(&p_func);
    return -1;
}