#include "yaComponent.h"


namespace ya
{
    Component::Component(COMPONENTTYPE type)
        : mType(type), mOwner(nullptr), mIsEnabled(true)
    {
    }

    Component::~Component()
    {
    }
}
