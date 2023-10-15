#include "yaBossScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaRigidbody.h"
#include "yaBoss.h"
#include "yaPlayer.h"

namespace ya
{
	Vector3 BossScript::mBossPos = Vector3::Zero;

	BossScript::BossScript()
		: mPlayerPos(Vector3::Zero)
		, mBossOrbit(Vector3::Zero)
		, mPlayerSC(nullptr)
	{
	}
	BossScript::~BossScript()
	{
	}
	void BossScript::Initialize()
	{
	}
	void BossScript::Update()
	{
		GameObject* obj = GetOwner();
		Boss* boss = dynamic_cast<Boss*>(obj);

		Transform* tr = obj->GetComponent<Transform>();
		Rigidbody* rb = obj->GetComponent<Rigidbody>();

		mPlayerPos = mPlayerSC->GetPosition();

		mBossOrbit = { (mPlayerPos.x - mBossPos.x), (mPlayerPos.y - mBossPos.y), 1.0f };
		mBossOrbit.normalize();

		mBossPos.x += mBossOrbit.x * 1.0f * Time::DeltaTime();
		mBossPos.y += mBossOrbit.y * 1.0f * Time::DeltaTime();

		tr->SetPosition(mBossPos);
	}
	void BossScript::LateUpdate()
	{
	}
	void BossScript::Render()
	{
	}
}