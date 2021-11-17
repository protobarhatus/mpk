#include "complete_type_container.h"
bool sameTypes(CompleteTypePresenter a, CompleteTypePresenter b)
{
    return (a.type == NULL && b.type == NULL) || areSameTypes(a.type, b.type);
}