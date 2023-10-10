#pragma once
#include "yaGameObject.h"
#include "yaPlayerScript.h"

namespace ya
{
	class Bullet : public GameObject
	{
	public:
		Bullet();
		virtual ~Bullet();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		Vector3 GetTrajectory()
		{
			return mTrajectory;
		}

	private:
		Vector3 mBulletPos;
		Vector3 mPlayerPos;
		Vector3 mTrajectory;

		PlayerScript* playerSC;
	};
}
