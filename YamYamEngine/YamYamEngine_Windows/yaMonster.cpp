#include "yaMonster.h"
#include "yaCollider.h"

namespace ya
{
	Monster::Monster()
	{
	}
	Monster::~Monster()
	{
	}
	void Monster::Initialize()
	{
		GameObject::Initialize();

		Collider* col = AddComponent<Collider>();
	}
	void Monster::Update()
	{
		GameObject::Update();
	}
	void Monster::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Monster::Render()
	{
		GameObject::Render();
	}
}