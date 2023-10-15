#pragma once
#include "yaGameObject.h"
#include "yaRigidbody.h"
#include "yaMeleeHitBox.hpp"
#include "yaBossShadow.h"
#include "yaRigidbody.h"

namespace ya
{
	class Boss : public GameObject
	{
	public:
		enum class eState
		{
			Red,
			Green,
			Blue,
			Hit,
			Dead,
			End
		};

		Boss();
		virtual ~Boss();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void Red();
		void Green();
		void Blue();
		void Hit();
		void Dead();

		void SetState(eState state) { mState = state; }

		BossShadow* GetBossShadow() const { return m_bossshadow_; }

	private:
		eState mState;
		int HP;
		Rigidbody* rb;

		BossShadow* m_bossshadow_;
	};
}