#pragma once
#include "yaComponent.h"
#include "yaEnums.h"
#include "yaEntity.h"
#include "yaMath.h"
#include "yaCollider.h"

namespace ya
{
	class GameObject;
	//class Script : public Entity
	class Script : public Component
	{
	public:
		friend GameObject;

		Script();
		virtual ~Script();

		virtual void Initialize(); // = 0;
		virtual void Update(); // = 0;
		virtual void LateUpdate(); // = 0;
		//virtual void Render() = 0;

		virtual void OnCollisionEnter(Collider* collider);
		virtual void OnCollisionStay(Collider* collider);
		virtual void OnCollisionExit(Collider* collider);

		virtual void OnTriigerEnter(Collider* collider);
		virtual void OnTriigerStay(Collider* collider);
		virtual void OnTriigerExit(Collider* collider);

		GameObject* GetOwner() { return mOwner; }
		void SetOwner(GameObject* obj) { mOwner = obj; }

	private:
		GameObject* mOwner;
	};
}

