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
		tr->SetScale(1.0f, 1.0f, 1.0f);
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
	}
	void BossShadow::BossCollisionLightExit(Lighting* light)
	{
		const auto mesh = GetComponent<MeshRenderer>();
		mesh->SetEnabled(false);
	}
	Lighting* BossShadow::GetClosestLight()
	{
		return nullptr;
	}
	void BossShadow::FlipShadowIfLower(Transform* const tr, const Vector3 boss_pos)
	{
	}
}