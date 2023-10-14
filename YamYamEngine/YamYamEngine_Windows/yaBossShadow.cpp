#include "yaBossShadow.h"

#include "yaCollider.h"
#include "yaInput.h"
#include "yaLight.h"
#include "yaLighting.h"
#include "yaBoss.h"
#include "yaMath.h"
#include "yaMeleeHitBox.hpp"
#include "yaMeshRenderer.h"
#include "yaResources.h"
#include "yaShadowMesh.hpp"
#include "yaTime.h"

namespace ya
{
	BossShadow::BossShadow(Boss* target)
		: m_boss_(target)
	{
	}
	void BossShadow::Initialize()
	{
		GameObject::Initialize();

		const auto tr = AddComponent<Transform>();
		tr->SetScale(2.0f, 2.0f, 1.0f);
		tr->SetPosition(m_boss_->GetComponent<Transform>()->GetPosition());

		const auto mesh = AddComponent<MeshRenderer>();
		mesh->SetMesh(Resources::Find<Mesh>(L"ShadowMesh"));
		mesh->SetShader(Resources::Find<Shader>(L"ColorShader"));

		// TODO: 다른 그림자 또는 광원에 충돌했을떄의 처리
		AddComponent<Collider>()->SetSize({ 1.0f, 1.0f, 1.0f });

		SetName(L"BossShadow");
	}
	void BossShadow::Update()
	{
		GameObject::Update();

		if (GetComponent<MeshRenderer>()->IsEnabled())
		{
			const auto tr = GetComponent<Transform>();
			const auto boss_pos = m_boss_->GetComponent<Transform>()->GetPosition();
			const auto boss_scale = m_boss_->GetComponent<Transform>()->GetScale();

			tr->SetPosition(boss_pos);
		}
	}
	void BossShadow::OnCollisionEnter(Collider* other)
	{
		GameObject::OnCollisionEnter(other);
	}
	void BossShadow::OnCollisionStay(Collider* other)
	{
		GameObject::OnCollisionStay(other);
	}
	void BossShadow::OnCollisionExit(Collider* other)
	{
		GameObject::OnCollisionExit(other);
	}
	void BossShadow::BossCollisionLightEnter(Lighting* light)
	{
		if (m_meeting_lights_.contains(light))
		{
			return;
		}

		const auto mesh = GetComponent<MeshRenderer>();
		mesh->SetEnabled(true);
		m_meeting_lights_.emplace(light);
	}
	void BossShadow::BossCollisionLightExit(Lighting* light)
	{
		const auto mesh = GetComponent<MeshRenderer>();
		mesh->SetEnabled(false);
		m_meeting_lights_.erase(light);
	}
	Lighting* BossShadow::GetClosestLight()
	{
		if (m_meeting_lights_.empty())
		{
			return nullptr;
		}

		Lighting* closest_light = *m_meeting_lights_.begin();
		const auto shadow_pos = GetComponent<Transform>()->GetPosition();
		float dist = Vector3::DistanceSquared(closest_light->GetComponent<Transform>()->GetPosition(), shadow_pos);

		for (const auto& light : m_meeting_lights_)
		{
			const auto pos = light->GetComponent<Transform>()->GetPosition();
			if (Vector3::DistanceSquared(pos, shadow_pos) < dist)
			{
				closest_light = light;
				dist = Vector3::DistanceSquared(pos, shadow_pos);
			}
		}

		return closest_light;
	}
	void BossShadow::FlipShadowIfLower(Transform* const tr, const Vector3 boss_pos)
	{
	}
}