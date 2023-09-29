#include "yaPlayer.h"
#include "yaInput.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaMeshRenderer.h"
#include "yaResources.h"
#include "yaCollider.h"

namespace ya
{
	Player::Player()
	{
	}
	Player::~Player()
	{
	}
	void Player::Initialize()
	{
		GameObject::Initialize();

		Collider* col = AddComponent<Collider>();

	}
	void Player::Update()
	{
		GameObject::Update();
	}
	void Player::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Player::Render()
	{
		GameObject::Render();
	}
	void Player::OnCollisionEnter(Collider* collider)
	{
		int a = 0;
	}
	void Player::OnCollisionStay(Collider* collider)
	{
		int a = 0;
	}
	void Player::OnCollisionExit(Collider* collider)
	{
		int a = 0;
	}
}