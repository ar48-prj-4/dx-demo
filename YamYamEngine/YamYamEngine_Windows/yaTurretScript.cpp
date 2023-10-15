#include "yaTurretScript.h"
#include "yaTransform.h"
#include "yaBullet.h"
#include "yaBulletScript.h"
#include "yaTime.h"
#include "yaMeshRenderer.h"
#include "yaResources.h"
#include "yaGameObject.h"
#include "yaSceneManager.h"
#include "yaTurret.h"

namespace ya
{
	Vector3 TurretScript::mTurretPos = Vector3::Zero;

	TurretScript::TurretScript()
		: mTime(0.0f)
	{
	}
	TurretScript::~TurretScript()
	{
	}
	void TurretScript::Initialize()
	{
	}
	void TurretScript::Update()
	{
		GameObject* obj = GetOwner();
		Transform* tr = obj->GetComponent<Transform>();
		Vector3 turretPos = tr->GetPosition();
		Vector3 turretScale = tr->GetScale();

		mTime += Time::DeltaTime();

		if (mTime >= 2.0f)
		{
			const auto turret = dynamic_cast<Turret*>(obj);

			const auto player_pos = ya::PlayerScript::GetPosition();
			const auto turret_pos = tr->GetPosition();
			const auto offset = (player_pos - turret_pos).normalize();

			GetOwner()->AddChildObject(Bullet::InstantiateBullet(tr, offset, 5.0f));

			mTime = 0.0f;
		}

		tr->SetPosition(turretPos);
		tr->SetScale(turretScale);
	}
	void TurretScript::LateUpdate()
	{
	}
	void TurretScript::Render()
	{
	}
}
