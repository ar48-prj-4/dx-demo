#include "yaCollider.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaScene.h"
#include "yaSceneManager.h"

//�浹�� �ϱ� ���� �ϳ��� ����
namespace ya
{
	Collider::Collider()
		:Component(COMPONENTTYPE::COLLIDER)
		, mTransform(nullptr)
		, mCollisionCount(0)
		, mbIsTrigger(false)
		, mCenter(Vector2::Zero)
		, mSize(Vector2::One)
		//, mSize(Vector2::Zero)
		//, mOffset(Vector2::Zero)
		//, mbIsCollision(false)
	{
	}

	Collider::~Collider()
	{
	}

	void Collider::Initialize()
	{
	}

	void Collider::Update()
	{
	}

	void Collider::Render()
	{
		
	}

	void Collider::OnCollisionEnter(Collider* other)
	{
		//mbIsCollision = true;
		//GetOwner()->OnCollisionEnter(other);

		mCollisionCount++;
		const std::vector<Script*>& scripts = GetOwner()->GetScripts();
		for (Script* script : scripts)
		{
			script->OnCollisionEnter(other);
		}
	}
	void Collider::OnCollisionStay(Collider* other)
	{
		//GetOwner()->OnCollisionStay(other);

		const std::vector<Script*>& scripts = GetOwner()->GetScripts();
		for (Script* script : scripts)
		{
			script->OnCollisionStay(other);
		}
	}
	void Collider::OnCollisionExit(Collider* other)		// �� ���������� ��(�浹 X)
	{
		//mbIsCollision = false;
		//GetOwner()->OnCollisionExit(other);

		mCollisionCount--;
		const std::vector<Script*>& scripts = GetOwner()->GetScripts();
		for (Script* script : scripts)
		{
			script->OnCollisionExit(other);
		}
	}

	void Collider::OnTriigerEnter(Collider* collider)
	{
		mCollisionCount++;
		const std::vector<Script*>& scripts = GetOwner()->GetScripts();
		for (Script* script : scripts)
		{
			script->OnTriigerEnter(collider);
		}
	}

	void Collider::OnTriigerStay(Collider* collider)
	{
		const std::vector<Script*>& scripts = GetOwner()->GetScripts();
		for (Script* script : scripts)
		{
			script->OnTriigerStay(collider);
		}
	}

	void Collider::OnTriigerExit(Collider* collider)
	{
		mCollisionCount--;
		const std::vector<Script*>& scripts = GetOwner()->GetScripts();
		for (Script* script : scripts)
		{
			script->OnTriigerExit(collider);
		}
	}

	//void Collider::ColliderOff()
	//{

	//}
}
