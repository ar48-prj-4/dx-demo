#include "yaPlayer.h"
#include "yaInput.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaPlayer.h"
#include "yaInput.h"
#include "yaMeshRenderer.h"
#include "yaResources.h"


namespace ya
{
	Player::Player()
		: HP(10)
	{

	}
	Player::~Player()
	{
	}
	void Player::Initialize()
	{
		GameObject::Initialize();

		tr = this->GetComponent<Transform>();
		tr->SetPosition(Vector3(0.f, -0.5f, 0.0f));

	}
	void Player::Update()
	{

		Vector3 pos = tr->GetPosition();

		if (Input::GetKeyDown(KEY_CODE::UP) || Input::GetKey(KEY_CODE::UP))
		{
			pos.y += 0.8f * Time::DeltaTime();
		}
		if (Input::GetKeyDown(KEY_CODE::LEFT) || Input::GetKey(KEY_CODE::LEFT))
		{
			pos.x -= 0.8f * Time::DeltaTime();
		}
		if (Input::GetKeyDown(KEY_CODE::RIGHT) || Input::GetKey(KEY_CODE::RIGHT))
		{
			pos.x += 0.8f * Time::DeltaTime();
		}
		if (Input::GetKeyDown(KEY_CODE::DOWN) || Input::GetKey(KEY_CODE::DOWN))
		{
			pos.y -= 0.8f * Time::DeltaTime();
		}

		tr->SetPosition(pos);

		Vector3 ScalePos = tr->GetScale();

		if (Input::GetKey(KEY_CODE::C))
		{
			ScalePos.x += 1.0f * Time::DeltaTime();
		}
		if (Input::GetKey(KEY_CODE::V))
		{
			ScalePos.x -= 1.0f * Time::DeltaTime();
		}

		tr->SetScale(ScalePos);

		
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
}