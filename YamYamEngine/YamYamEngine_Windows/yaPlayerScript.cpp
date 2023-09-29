#include "yaPlayerScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaInput.h"

namespace ya
{

	PlayerScript::PlayerScript()
	{
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{
	}

	void PlayerScript::Update()
	{
		GameObject* obj = GetOwner();
		Transform* tr = obj->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		//Player 이동
		if (Input::GetKey(eKeyCode::W))
		{
			pos.y += 0.0005f;
		}
		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= 0.0005f;
		}
		if (Input::GetKey(eKeyCode::S))
		{
			pos.y -= 0.0005f;
		}
		if (Input::GetKey(eKeyCode::D))
		{
			pos.x += 0.0005f;
		}

		//Mouse
		if (Input::GetKeyDown(eKeyCode::LBTN))
		{

		}
		if (Input::GetKeyDown(eKeyCode::RBTN))
		{

		}

		//상호작용
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{

		}

		tr->SetPosition(pos);
	}

	void PlayerScript::LateUpdate()
	{
	}

	void PlayerScript::Render()
	{
	}

}
