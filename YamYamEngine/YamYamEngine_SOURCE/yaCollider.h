#pragma once
#include "yaComponent.h"
#include "yaTransform.h"

namespace ya
{
	using namespace math;
	class Collider : public Component
	{
	public:
		Collider();
		//Collider(Scene* Scene);
		~Collider();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider* other);		// 충돌 시작
		virtual void OnCollisionStay(Collider* other);		// 충돌 중
		virtual void OnCollisionExit(Collider* other);		// 충돌 빠져나감

		virtual void OnTriigerEnter(Collider* collider);
		virtual void OnTriigerStay(Collider* collider);
		virtual void OnTriigerExit(Collider* collider);

		COLLIDERTYPE GetType() { return mType; }
		void SetType(COLLIDERTYPE type) { mType = type; }
		bool IsTrigger() { return mbIsTrigger; }
		Vector3 GetColliderPos() { return mColliderPosition; }
		void SetSize(Vector2 size) { mSize = size; }
		void SetCenter(Vector2 center) { mCenter = center; }
		Vector2 GetSize() { return mSize; }
		Vector2 GetCenter() { return mCenter; }


		//void ColliderOff();

		//Vector2 GetSize() { return mSize; }
		//void SetSize(Vector2 size) { mSize = size; }
		//Vector2 GetOffset() { return mOffset; }
		//void SetOffset(Vector2 offset) { mOffset = offset; }
		//Vector2 GetPosition() { return mPosition; }
		//void  SetPosition(Vector2 position) { mPosition = position; }

	protected:
		COLLIDERTYPE mType;
		Transform* mTransform;
		bool mbIsTrigger;
		UINT mCollisionCount;
		Vector3 mColliderPosition;
		Vector2 mSize;
		Vector2 mCenter;

	private:

		//Vector2 mSize;
		//Vector2 mOffset;
		//Vector2 mPosition;

		//bool mbIsCollision;						// 충돌하는게 눈에 보이게 하고 싶었을 때 변수
	};
}