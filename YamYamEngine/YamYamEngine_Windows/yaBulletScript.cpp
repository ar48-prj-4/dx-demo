#include "yaBulletScript.h"
#include "yaMeshRenderer.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaBullet.h"
#include "yaPlayerScript.h"
#include "yaTurretScript.h"

namespace ya
{
	BulletScript::BulletScript()
		: mBulletPos(Vector3::Zero)
		, playerSC{ nullptr }
	{
	}
	BulletScript::~BulletScript()
	{
	}
	void BulletScript::Initialize()
	{
	}
	void BulletScript::Update()
	{
		GameObject* obj = GetOwner();
		Bullet* bullet = dynamic_cast<Bullet*>(obj);

		Vector3 pPos = playerSC->GetPosition();
		Vector3 bPos = GetOwner()->GetComponent<Transform>()->GetPosition();
		Vector3 TestPos = { (pPos.x - bPos.x), (pPos.y - bPos.y), 1.0f };

		TestPos.normalize();

		Transform* tr = obj->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		pos.x += TestPos.x * 2.0f * Time::DeltaTime();
		pos.y += TestPos.y * 2.0f * Time::DeltaTime();

		tr->SetPosition(pos);
	}
	void BulletScript::LateUpdate()
	{
	}
	void BulletScript::Render()
	{
	}
}