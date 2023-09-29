#include "yaComponent.h"


namespace ya
{
    Component::Component(COMPONENTTYPE type)
        : mType(type)
        , mOwner(nullptr)
    {
    }

    Component::~Component()
    {
    }

    void Component::Initialize()
    {
    }
    void Component::Update()
    {
    }
    void Component::LateUpdate()
    {
    }
    void Component::Render()
    {
    }
}
