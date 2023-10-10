#include "yaBullet.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaMeshRenderer.h"

namespace ya
{
	Bullet::Bullet()
		: mBulletPos(Vector3::Zero)
		, mPlayerPos(Vector3::Zero)
		, mTrajectory(Vector3::Zero)
		, playerSC{ nullptr }
	{
	}
	Bullet::~Bullet()
	{
	}
	void Bullet::Initialize()
	{
		GameObject::Initialize();

		mPlayerPos = playerSC->GetPosition();
		mBulletPos = AddComponent<Transform>()->GetPosition();

		mTrajectory = { (mPlayerPos.x - mBulletPos.x), (mPlayerPos.y - mBulletPos.y), 1.0f };
		mTrajectory.normalize();
	}
	void Bullet::Update()
	{
		GameObject::Update();
	}
	void Bullet::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Bullet::Render()
	{
		GameObject::Render();
	}
	void Bullet::OnCollisionEnter(Collider* other)
	{
	}
	void Bullet::OnCollisionStay(Collider* other)
	{
	}
	void Bullet::OnCollisionExit(Collider* other)
	{
	}
}