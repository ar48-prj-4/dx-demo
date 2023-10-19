#include "yaPlayer.h"

#include "yaBullet.h"
#include "yaInput.h"
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
	Player::Player()
		: HP(100),
		//jumptime(0.f),
		rb{ nullptr },
		mState(eState::Idle),
		LeftTileCollision(false),
		RightTileCollision(false),
		DownTileCollision(false),
		UpTileCollision(false)
	{
	}

	Player::~Player()
	{
	}

	void Player::Initialize()
	{
		GameObject::Initialize();

		AddComponent<Transform>();
		AddComponent<Rigidbody>();
		AddComponent<Collider>();
		m_shadow_ = new PlayerShadow(this);
		m_shadow_->Initialize();
		AddChildObject(m_shadow_);

		rb = GetComponent<Rigidbody>();
		rb->SetGround(true);

		m_melee_hitbox_ = new MeleeHitBox(this);
		m_melee_hitbox_->Initialize();
		AddChildObject(m_melee_hitbox_);
	}

	void Player::Update()
	{
		GameObject::Update();
		m_shadow_->Update();

		m_melee_hitbox_->GetComponent<Transform>()->SetPosition(GetComponent<Transform>()->GetPosition());

		switch (mState)
		{
		case ya::Player::eState::Live:
			Live();
			break;

		case ya::Player::eState::Idle:
			Idle();
			break;

		case ya::Player::eState::MeleeAttack:
			MeleeAttack();
			break;

		case ya::Player::eState::RangeAttack:
			RangeAttack();
			break;

		case ya::Player::eState::Shoot:
			Shoot();
			break;

		case ya::Player::eState::Hit:
			Hit();
			break;

		case ya::Player::eState::Dead:
			Dead();
			break;

		case ya::Player::eState::End:
			break;
		default:
			break;
		}
	}
	void Player::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Player::Render()
	{
		GameObject::Render();
		m_shadow_->Render();
	}
	void Player::OnCollisionEnter(Collider* other)
	{
		const auto layer = other->GetOwner()->GetLayer();

		if (layer == LAYER::ATTACK || layer == LAYER::MONSTER)
		{
			if (other->GetOwner() == m_shadow_->m_melee_hitbox_ || 
				other->GetOwner() == m_melee_hitbox_)
			{
				return;
			}

			mState = eState::Hit;
		}

		// ��Ż �浹 �� 
		else if (layer == LAYER::PORTAL)
		{
			
		}

		else if (layer == LAYER::TILE)
		{

			Vector3 playerpos = this->GetComponent<Collider>()->GetPosition();
			Vector3 playersize = this->GetComponent<Collider>()->GetSize();

			Vector3 tilepos = other->GetPosition();
			Vector3 tilesize = other->GetSize();

			float ColSum_X = (playersize.x + tilesize.x) - fabs(playerpos.x - tilepos.x);
			float ColSum_Y = (playersize.y + tilesize.y) - fabs(playerpos.y - tilepos.y);

			// 좌우
			if (ColSum_X < ColSum_Y)
			{
				// 왼쪽 충돌
				if ((playerpos.x > tilepos.x))
				{
					LeftTileCollision = true;
				}
				// 오른쪽 충돌
				if(playerpos.x <= tilepos.x)
				{
					RightTileCollision = true;
				}
			}
			// 상하
			else
			{
				// 위쪽 충돌
				if (playerpos.y < tilepos.y)
				{
					UpTileCollision = true;
				}
				// 아래쪽 충돌
				if (playerpos.y >= tilepos.y)
				{
					DownTileCollision = true;
				}
			}

		}

		else if (layer == LAYER::ITEM)
		{

		}
		else if(const auto light = dynamic_cast<Lighting*>(other->GetOwner()); layer == LAYER::LIGHT)
		{
			m_shadow_->PlayerCollisionLightEnter(light);
		}

	}
	void Player::OnCollisionStay(Collider* other)
	{
		const auto layer = other->GetOwner()->GetLayer();

		if(const auto light = dynamic_cast<Lighting*>(other->GetOwner()); layer == LAYER::LIGHT)
		{
			m_shadow_->PlayerCollisionLightEnter(light);
		}
	}

	void Player::OnCollisionExit(Collider* other)
	{
		const auto layer = other->GetOwner()->GetLayer();

		if(const auto light = dynamic_cast<Lighting*>(other->GetOwner()); layer == LAYER::LIGHT)
		{
			m_shadow_->PlayerCollisionLightExit(dynamic_cast<Lighting*>(other->GetOwner()));
		}

		if (layer == LAYER::TILE)
		{
			ExitCollider();
		}
	}

	void Player::ExitCollider()
	{
		if (LeftTileCollision == true)
		{
			LeftTileCollision = false;
		}
		if (RightTileCollision == true)
		{
			RightTileCollision = false;
		}
		if (DownTileCollision == true)
		{
			DownTileCollision = false;
		}
		if (UpTileCollision == true)
		{
			UpTileCollision = false;
		}
	}

	void Player::Idle()
	{
	}

	void Player::Live()
	{
	}

	void Player::Shoot()
	{
	}

	void Player::DispatchShadowAttack()
	{
		m_shadow_->Attack();
	}

	void Player::MeleeAttack()
	{
		DispatchShadowAttack();
		MeleeHitBox::ProcessMeleeAttack(this, m_melee_hitbox_->GetHitObjects());

		mState = eState::Idle;
	}

	void Player::RangeAttack()
	{
		DispatchShadowAttack();
		const auto mouse_pos = Input::GetCoordinationMousePosition();


		Bullet::InstantiateBullet(GetComponent<Transform>(), (mouse_pos - GetComponent<Transform>()->GetPosition()).normalize(), 1.5f);

		mState = eState::Idle;
	}

	void Player::Hit()
	{
		if(HP != 0)
		{
			HP -= 10;
		}
		else
		{
			mState = eState::Dead;
		}
	}
	void Player::Dead()
	{
		Destroy(this);
	}
}
