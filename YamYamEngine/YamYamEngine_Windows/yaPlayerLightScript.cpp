#include "yaPlayerLightScript.h"
#include "yaSceneManager.h"
#include "yaInput.h"
#include "yaPlayer.h"
#include "yaLight_TimeLimit.h"


namespace ya
{
	PlayerLightScript::PlayerLightScript()
	{
	}

	PlayerLightScript::~PlayerLightScript()
	{
	}

	void PlayerLightScript::Initialize()
	{
	}

	void PlayerLightScript::Update()
	{
		GameObject* gameobject = GetOwner();
		Player* player = dynamic_cast<Player*>(gameobject);
		Transform* tr = player->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		if (Input::GetKeyDown(eKeyCode::RBTN) && player->GetLightPower() >= 3)
		{
			player->SetLightPower(player->GetLightPower() - 3);

			Light_TimeLimit* light = new Light_TimeLimit(5.0f);
			light->Initialize();
			light->GetComponent<Transform>()->SetPosition(pos.x, pos.y + 5.0f, pos.z);

			SceneManager::GetActiveScene()->AddGameObject(light, LAYER::LIGHT);
		}
	}

	void PlayerLightScript::LateUpdate()
	{
	}

	void PlayerLightScript::Render()
	{
	}
}