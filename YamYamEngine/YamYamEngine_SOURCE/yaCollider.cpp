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
	}

	void Collider::Update()
	{
	
	}

	void Collider::LateUpdate()
	{
	}

	void Collider::Render()
	{
		/*tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		mPosition = pos + mOffset;

		pos.x -= mSize.x / 2.0f;
		pos.y -= mSize.y / 2.0f;
		pos.x += mOffset.x;
		pos.y += mOffset.y;*/
		
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
}
