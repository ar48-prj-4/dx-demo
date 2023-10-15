#pragma once
#include "yaGameObject.h"
#include "yaLighting.h"
#include "yaTransform.h"
#include <set>

namespace ya
{
	class Boss;

	class BossShadow : public GameObject
	{
	public:
		BossShadow(Boss* target);
		BossShadow(const BossShadow& other) = default;
		~BossShadow() override = default;

		void Initialize() override;
		void Update() override;
		void OnCollisionEnter(class Collider* other) override;
		void OnCollisionStay(class Collider* other) override;
		void OnCollisionExit(class Collider* other) override;

	private:
		friend class Boss;

		void BossCollisionLightEnter(Lighting* light);
		void BossCollisionLightExit(Lighting* light);

		Lighting* GetClosestLight();
		void FlipShadowIfLower(Transform* const tr, const Vector3 boss_pos);

		std::set<Lighting*> m_meeting_lights_;

		Boss* m_boss_;
	};
}