#include "IJ_Item.h"
#include "yaTransform.h"
#include "yaCollider.h"
#include "yaPlayer.h"


namespace IJ
{
	Item::Item()
	{
	}

	Item::~Item()
	{
	}

	void Item::Initialize()
	{
		ya::GameObject::Initialize();

		ya::Transform* tr = AddComponent<ya::Transform>();
		tr->SetRotation(0.0f, 0.0f, 0.0f);
		tr->SetScale(1.0f, 1.0f, 1.0f);

		AddComponent<ya::Collider>();
	}

	void Item::Update()
	{
		ya::GameObject::Update();
	}

	void Item::LateUpdate()
	{
		ya::GameObject::LateUpdate();
	}

	void Item::Render()
	{
		ya::GameObject::Render();
	}

	void Item::OnCollisionEnter(ya::Collider* other)
	{
		ya::GameObject::OnCollisionEnter(other);

		ya::GameObject* gameobject = other->GetOwner();
		ya::Player* player = dynamic_cast<ya::Player*>(gameobject);

		if (player != nullptr)
		{
			ItemEffect(player);
			ya::Destroy(this);
		}
	}

	void Item::OnCollisionStay(ya::Collider* other)
	{
		ya::GameObject::OnCollisionStay(other);
	}

	void Item::OnCollisionExit(ya::Collider* other)
	{
		ya::GameObject::OnCollisionExit(other);
	}
}