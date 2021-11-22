#ifndef FIBONACHY_NIM_STRING_H
#define FIBONACHY_NIM_STRING_H

#include "types_and_functions_declarations/type_declaration.h"
#include "types_and_functions_declarations/functions_extensions.h"
#include "vector/vector.h"

struct String_struct
{
    char * string;
    int length;
    int allocated_space;
};
typedef struct String_struct String;
typedef String StringRef;

String defaultString(const char * string);
String createString(int length);
String emptyString();

String copyString(const String * str);
String moveString(String * str);
void destructString(String * str);

StringRef wrapStandartString(const char * string);
StringRef wrapString(const String * str, int shift);

DECLARE_STRUCT_TYPE(String, String)

static inline char * atString(String * str, int i)
{
    assert(i >= 0 && i < str->length);
    return str->string + i;
}
static inline const char * catString(const String * str, int i)
{
    assert(i >= 0 && i < str->length);
    return str->string + i;
}

static inline getLengthString(const String * str)
{
    return str->length;
}

void resizeString(String * str, int new_length);
void shrinkString(String * str, int new_length);
void extendString(String * str, int new_length);

void concatToString(String * str, const String * right);
String concatString(const String * a, const String * b);

VectorInt makePiFunction(const String * str);

int findSubString(const String * str, const String * substr);

GENERATE_RIGHT_VALUE_BINARY_EXTENSIONS(String, String, findSub, int);

#endif //FIBONACHY_NIM_STRING_H
