#include "yaCollider.h"
#include "yaGameObject.h"
#include "yaScene.h"
#include "yaSceneManager.h"

//�浹�� �ϱ� ���� �ϳ��� ����
namespace ya
{
	Collider::Collider()
		:Component(COMPONENTTYPE::COLLIDER)
		, mSize(Vector3::Zero)
		, mOffset(Vector2::Zero)
		, mbIsCollision(false)
	{

		
	}

	Collider::~Collider()
	{
	}

	void Collider::Initialize()
	{
		UpdatePosition();
	}

	void Collider::Update()
	{
		UpdatePosition();
	}

	void Collider::LateUpdate()
	{
	}

	void Collider::Render()
	{
	}

	void Collider::OnCollisionEnter(Collider* other)
	{
		GetOwner()->OnCollisionEnter(other);
	}
	void Collider::OnCollisionStay(Collider* other)
	{
		GetOwner()->OnCollisionStay(other);
	}
	void Collider::OnCollisionExit(Collider* other)		// �� ���������� ��(�浹 X)
	{
		GetOwner()->OnCollisionExit(other);
	}

	void Collider::ColliderOff()
	{

	}

	void Collider::UpdatePosition()
	{
		auto* tr = GetOwner()->GetComponent<Transform>();

		if(tr != nullptr)
		{
			SetPosition(tr->GetPosition());
			SetSize(tr->GetScale());
		}
	}
}
