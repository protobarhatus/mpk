#ifndef FIBONACHY_NIM_COMPLETE_TYPE_CONTAINER_H
#define FIBONACHY_NIM_COMPLETE_TYPE_CONTAINER_H
#include "type_declaration.h"
#include "arithmetic_type_declaration.h"
#include "io_type_declaration.h"


struct CompleteTypePresenter_struct
{
    const TypePresenterContainer * type;
    const ArithmeticTypePresenter * arithm_type;
    const IOTypeContainer * io_type;
};
typedef struct CompleteTypePresenter_struct CompleteTypePresenter;
static inline CompleteTypePresenter defaultCompleteTypePresenter(const TypePresenterContainer * type, const ArithmeticTypePresenter * arithm_type,
                                                                 const IOTypeContainer * io_type)
{
    CompleteTypePresenter res = {type, arithm_type, io_type};
    return res;
}

bool sameTypes(CompleteTypePresenter a, CompleteTypePresenter b);

#define GET_COMPLETE_TYPE_PRESENTER(UCN) \
defaultCompleteTypePresenter(TYPE_##UCN(), ARITHM_TYPE_##UCN(), IO_TYPE_##UCN())
#define GET_UNKNOWN_TYPE_PRESENTER defaultCompleteTypePresenter(NULL, NULL, NULL)
#endif //FIBONACHY_NIM_COMPLETE_TYPE_CONTAINER_H
