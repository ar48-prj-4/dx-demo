#include "yaBullet.h"

#include "yaBulletScript.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaMeshRenderer.h"
#include "yaResources.h"
#include "yaRigidbody.h"
#include "yaSceneManager.h"
#include "yaCollider.h"
#include "yaPlayer.h"
#include "yaTile.h"

namespace ya
{
	Bullet::Bullet()
	{
	}

	Bullet::~Bullet()
	{
	}

	void Bullet::Initialize()
	{
		GameObject::Initialize();
	}

	void Bullet::Update()
	{
		GameObject::Update();
	}

	void Bullet::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Bullet::Render()
	{
		GameObject::Render();
	}

	void Bullet::OnCollisionEnter(Collider* other)
	{
		GameObject::OnCollisionEnter(other);

		const auto layer = other->GetOwner()->GetLayer();

		if (layer == LAYER::TILE || layer == LAYER::PLAYER)
		{
			Destroy(this);
		}
	}

	void Bullet::OnCollisionStay(Collider* other)
	{
		GameObject::OnCollisionStay(other);
	}

	void Bullet::OnCollisionExit(Collider* other)
	{
		GameObject::OnCollisionExit(other);
	}

	void Bullet::InstantiateBullet(Transform* tr, Vector3 offset, float speed)
	{
		Bullet* bullet = new Bullet();
		bullet->Initialize();

		Transform* bullettr = bullet->AddComponent<Transform>();
		bullettr->SetPosition(tr->GetPosition());
		bullettr->SetScale(Vector3(0.5f, 0.5f, 1.0f));
		bullet->AddComponent<BulletScript>();

		MeshRenderer* bulletmr = bullet->AddComponent<MeshRenderer>();
		bulletmr->SetMesh(Resources::Find<Mesh>(L"TriangleMesh"));
		bulletmr->SetShader(Resources::Find<Shader>(L"ColorShader"));

		const auto rb = bullet->AddComponent<Rigidbody>();
		rb->SetVelocity(offset * speed);
		rb->SetGravity(Vector3::Zero);
		rb->SetFriction(0.0f);

		bullet->AddComponent<Collider>();

		SceneManager::GetActiveScene()->AddGameObject(bullet, LAYER::ATTACK);
	}
}
