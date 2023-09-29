#pragma once
#include "yaComponent.h"

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

		void OnCollisionEnter(Collider* other);		// �浹 ����
		void OnCollisionStay(Collider* other);		// �浹 ��
		void OnCollisionExit(Collider* other);		// �浹 ��������

		void ColliderOff();

		Vector2 GetSize() { return mSize; }
		void SetSize(Vector2 size) { mSize = size; }
		Vector2 GetOffset() { return mOffset; }
		void SetOffset(Vector2 offset) { mOffset = offset; }
		Vector2 GetPosition() { return mPosition; }
		void  SetPosition(Vector2 position) { mPosition = position; }

		//// Collider�� �׸�, ����, �� ��ɷ� ���� Type
		//COLLIDERTYPE GetType() { return mType; }
		//void SetType(COLLIDERTYPE type) { mType = type; }

	private:

		Vector2 mSize;
		Vector2 mOffset;
		Vector2 mPosition;
		//COLLIDERTYPE mType;

		bool mbIsCollision;						// �浹�ϴ°� ���� ���̰� �ϰ� �;��� �� ����
	};
}