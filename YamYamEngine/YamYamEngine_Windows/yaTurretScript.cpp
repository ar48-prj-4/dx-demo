#include "yaTurretScript.h"
#include "yaMeshRenderer.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaBullet.h"

namespace ya
{
	float TurretScript::mTime = 0.0f;

	TurretScript::TurretScript()
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
		mTime += Time::DeltaTime();

		if (mTime >- 0.5f)
		{
			Bullet* bullet = new Bullet();



			mTime = 0.0f;
		}
	}
	void TurretScript::LateUpdate()
	{
	}
	void TurretScript::Render()
	{
	}
}