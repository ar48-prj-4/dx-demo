#pragma once
#include "yaGameObject.h"
#include "yaPlayerShadow.h"
#include "yaRigidbody.h"

namespace ya
{
	class Player : public GameObject
	{
	public:
		enum class eState
		{
			Idle,
			Live,
			Shoot,
			Jump,
			Fall,
			Hit,
			Dead,
			End,
		};

		Player();
		virtual ~Player();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void Idle();
		void Live();
		void Shoot();
		void Jump();
		void Fall();
		void Hit();
		void Dead();

		int GetHP() { return HP; }
		void SetHP(int hp) { HP = hp; }
		int GetLightPower() { return m_light_power; }
		void SetLightPower(int lightpower) { m_light_power = lightpower; }

	private:
		eState mState;
		int HP;
		Rigidbody* rb;
		//float jumptime;
		PlayerShadow* m_shadow_;
		int m_light_power;
	};
}
