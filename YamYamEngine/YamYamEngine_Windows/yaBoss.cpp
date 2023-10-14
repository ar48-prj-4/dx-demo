#include "yaBoss.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaMeshRenderer.h"
#include "yaPlayerScript.h"
#include "yaResources.h"
#include "yaRigidbody.h"
#include "yaCollider.h"
#include "yaMeleeHitBox.hpp"
#include "yaRigidbody.h"
#include "yaSceneManager.h"

namespace ya
{
	Boss::Boss()
		: HP(100)
		, rb{ nullptr }
		, mState(eState::Red)
	{
	}
	Boss::~Boss()
	{
	}
	void Boss::Initialize()
	{
		GameObject::Initialize();

		AddComponent<Transform>();
		AddComponent<Rigidbody>();
		AddComponent<Collider>();

		m_bossshadow_ = new BossShadow(this);
		m_bossshadow_->Initialize();

		rb = GetComponent<Rigidbody>();
		rb->SetGround(true);
	}
	void Boss::Update()
	{
		GameObject::Update();
		m_bossshadow_->Update();

		switch (mState)	
		{
		case ya::Boss::eState::Red:
			Red();
			break;
		case ya::Boss::eState::Green:
			Green();
			break;
		case ya::Boss::eState::Blue:
			Blue();
			break;
		case ya::Boss::eState::Hit:
			Hit();
			break;
		case ya::Boss::eState::Dead:
			Dead();
			break;
		case ya::Boss::eState::End:
			break;
		default:
			break;
		}
	}
	void Boss::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Boss::Render()
	{
		GameObject::Render();
		m_bossshadow_->Render();
	}
	void Boss::OnCollisionEnter(Collider* other)
	{
		GameObject::OnCollisionEnter(other);

		const auto layer = other->GetOwner()->GetLayer();
	}
	void Boss::OnCollisionStay(Collider* other)
	{
		GameObject::OnCollisionStay(other);

		const auto layer = other->GetOwner()->GetLayer();

	}
	void Boss::OnCollisionExit(Collider* other)
	{
		GameObject::OnCollisionExit(other);

		const auto layer = other->GetOwner()->GetLayer();

	}
	void Boss::Red()
	{
		if (HP <= 70)
		{
			mState = eState::Green;
		}
	}
	void Boss::Green()
	{
		if (HP <= 30)
		{
			mState = eState::Blue;
		}
	}
	void Boss::Blue()
	{
		if (HP <= 0)
		{
			mState = eState::Dead;
		}
	}
	void Boss::Hit()
	{
	}
	void Boss::Dead()
	{
	}
}