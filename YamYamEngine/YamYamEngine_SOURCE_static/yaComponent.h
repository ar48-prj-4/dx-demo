#pragma once
#include "yaEnums.h"
#include "yaEntity.h"
#include "yaMath.h"

namespace ya
{
	using namespace enums;
	using namespace math;

	class GameObject;
	class Component : public Entity
	{
	public:
		friend GameObject;

		Component(COMPONENTTYPE type);
		virtual ~Component();

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void LateUpdate() = 0;
		virtual void Render() = 0;

		bool IsEnabled() const { return mIsEnabled; }
		void SetEnabled(bool isEnabled) { mIsEnabled = isEnabled; }

		GameObject* GetOwner() { return mOwner; }
		UINT GetUpdateOrder() { return (UINT)mType; }

	private:
		bool mIsEnabled;
		const COMPONENTTYPE mType;
		GameObject* mOwner;
	};
}
