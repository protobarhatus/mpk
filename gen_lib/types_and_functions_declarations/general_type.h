#ifndef FIBONACHY_NIM_GENERAL_TYPE_H
#define FIBONACHY_NIM_GENERAL_TYPE_H
//in complex structures on unknown type like matrix it is very inconvenient to write it's logic on some void pointers.
//so, it may use this type that give all functions connected to all types of containers
//GeneralType on GeneralType is uknown behaviour and not recommended
#include "type_declaration.h"
#include "functions_extensions.h"
#include "arithmetic_type_declaration.h"
#include "complete_type_container.h"
//#include "../vector/vector.h"
//#include "../linear_algebra_elements/vector_algebraic_addendum.h"

//null and unit functions meant to be without any arguments in arithmetic_type_declaration. But, since there is no way
//to define a singular null or one value for different types, GeneralType has no way to make its value in these functions
//so, nullGeneralType() and unitGeneralType() returns object in uncertainty state. It will resolve it state into normal value
//as soon as it will able to: in any function where its argument and other argument has defined type
//(even with const breaking)
//If all arguments of function still don't know their types, then it will define special state of result object if can,
//or throw an assert otherwise.
//for example, sqrt from special states of null or ones is still null or ones,
//adding null to any x is some x
//but adding one to any x (aside null) will result in assert
//For user the best approach is to define its type as soon as possible with explicit defineStateForGeneralType() function
//or use nullGeneralTypeOfCertainType, unitGeneralTypeOfCertainType

//For this reason const marker DOES NOT guarantees that object will be unchangeable and even that there will be no callocs
enum GeneralTypeSpecialState_enum
{
    GENERAL_TYPE_SPECIAL_STATE_NONE,
    GENERAL_TYPE_SPECIAL_STATE_NULL,
    GENERAL_TYPE_SPECIAL_STATE_UNIT
};
typedef enum GeneralTypeSpecialState_enum GeneralTypeSpecialState;
struct GeneralType_struct
{
    CompleteTypePresenter type;
    void * data;
    GeneralTypeSpecialState state;

};
typedef struct GeneralType_struct GeneralType;

GeneralType defaultGeneralType(void * data, CompleteTypePresenter type);
GeneralType copyGeneralType(const GeneralType * cop);
GeneralType moveGeneralType(GeneralType * mov);
void destructGeneralType(GeneralType * obj);
bool equalGeneralType(const GeneralType * a, const GeneralType * b);

DECLARE_STRUCT_TYPE(GeneralType, GeneralType)

GeneralType addGeneralType(const GeneralType * a, const GeneralType * b);
GeneralType subGeneralType(const GeneralType * a, const GeneralType * b);
GeneralType multGeneralType(const GeneralType * a, const GeneralType * b);
GeneralType divGeneralType(const GeneralType * a, const GeneralType * b);

void addToGeneralType(GeneralType * a, const GeneralType * b);
void subToGeneralType(GeneralType * a, const GeneralType * b);
void multToGeneralType(GeneralType * a, const GeneralType * b);
void divToGeneralType(GeneralType * a, const GeneralType * b);

GeneralType sqrtGeneralType(const GeneralType * a);
GeneralType minusGeneralType(const GeneralType * a);
//better not use this functions if possible but they are needed for arithmetic type declaration and some generated code like vector addendum may call it
GeneralType nullGeneralType();
GeneralType unitGeneralType();

bool isNullGeneralType(const GeneralType * a);

DECLARE_TYPE_AS_ARITHMETIC(GeneralType, GeneralType)

void printfGeneralType(const GeneralType * type);
GeneralType scanfGeneralType();

DECLARE_IO_TYPE(GeneralType, GeneralType);

GeneralType nullGeneralTypeOfCertainType(CompleteTypePresenter type);
GeneralType unitGeneralTypeOfCertainType(CompleteTypePresenter type);

void defineStateForGeneralType(GeneralType * obj, CompleteTypePresenter type);

#define MAKE_GENERAL_TYPE_TRANSLATION_FUNCTIONS(TN, UCN) \
static inline GeneralType getGeneralTypeOn##UCN##Copied(const TN * val) {\
    TN * new_val = malloc(TYPE_##UCN()->element_size);   \
    *new_val = copy##UCN(val);\
    return defaultGeneralType((void*)new_val, GET_COMPLETE_TYPE_PRESENTER(UCN));                                                        \
}                                                        \
static inline GeneralType getGeneralTypeOn##UCN##RV(TN val) {\
    TN * new_val = malloc(TYPE_##UCN()->element_size);   \
    *new_val = move##UCN(&val);                           \
    return defaultGeneralType((void*)new_val, GET_COMPLETE_TYPE_PRESENTER(UCN));\
}\
static inline GeneralType getGeneralTypeOn##UCN##Moved(TN * val) {\
    return defaultGeneralType((void*)val, GET_COMPLETE_TYPE_PRESENTER(UCN));\
}                                                        \
static inline TN * atGeneralType##UCN(GeneralType * obj)               \
{                                                        \
    return (TN*)obj->data;                                                        \
}                                                        \
static inline const TN * catGeneralType##UCN(const GeneralType * obj)        \
{\
    return (const TN*)obj->data;                                                         \
}


MAKE_GENERAL_TYPE_TRANSLATION_FUNCTIONS(int, Int)

MAKE_GENERAL_TYPE_TRANSLATION_FUNCTIONS(double, Double)








//to forbid
static inline GeneralType getGeneralTypeOnGeneralTypeCopied(const GeneralType * val) {
    assert(false);
}

#endif //FIBONACHY_NIM_GENERAL_TYPE_H
