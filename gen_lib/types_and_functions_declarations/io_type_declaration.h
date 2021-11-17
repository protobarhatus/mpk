#ifndef FIBONACHY_NIM_IO_TYPE_DECLARATION_H
#define FIBONACHY_NIM_IO_TYPE_DECLARATION_H
#include <stdio.h>
#include <stdlib.h>
#include "functions_extensions.h"
#include "../user_interacts/user_interactions.h"
#include "type_declaration.h"
//definitions of exact functions of standart types will be in user_interacts
typedef void (*output_function)(const void * data);
typedef void * (*input_function)();
struct IOTypeContainer_struct
{
    input_function in;
    output_function out;
};
typedef struct IOTypeContainer_struct IOTypeContainer;

#define GEN_WRAPPING_OF_STANDART_FUNCTIONS(TN, UCN) \
static inline void * get##UCN##Func()\
{\
    TN * data = malloc(sizeof(TN));                 \
    *data = scanf##UCN();                           \
    return (void*)data;                                                    \
}                                                   \
static inline void print##UCN##Func(const void * data)    \
{\
    printf##UCN((const TN*)data);                                                    \
}

#define GEN_DUMMY_FUNCS(TN, UCN) \
static inline void * get##UCN##Func() \
{                                \
    printf("Attempt of scanfing non io type %s\n", #UCN);                             \
    return NULL;                             \
}                                \
static inline void print##UCN##Func(const void * data)                                \
{\
    printf("Attempt of printing non io type %s\n", #UCN);                                 \
}

#define MAKE_IO_CONTAINER(TN, UCN) \
static inline const IOTypeContainer * IO_TYPE_##UCN() {\
    static IOTypeContainer c = {&get##UCN##Func, &print##UCN##Func}; \
    return &c;\
}

#define DECLARE_IO_TYPE(TN, UCN) \
TN scanf##UCN();                 \
void printf##UCN(const TN * );   \
GENERATE_RIGHT_VALUE_UNARY_EXTENSIONS_TO_VOID_FUNC(TN, UCN, printf) \
GEN_WRAPPING_OF_STANDART_FUNCTIONS(TN, UCN)                                 \
MAKE_IO_CONTAINER(TN, UCN)


#define DECLARE_NON_IO_TYPE(TN, UCN) \
GEN_DUMMY_FUNCS(TN, UCN)             \
MAKE_IO_CONTAINER(TN, UCN)


DECLARE_IO_TYPE(int, Int);
DECLARE_IO_TYPE(double, Double);


#endif //FIBONACHY_NIM_IO_TYPE_DECLARATION_H
