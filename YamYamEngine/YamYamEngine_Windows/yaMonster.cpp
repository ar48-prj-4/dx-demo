#include "yaMonster.h"
#include "yaResources.h"
#include "yaMeshRenderer.h"
#include "yaSceneManager.h"
#include "yaTime.h"
#include "yaPlayer.h"
#include "yaInput.h"
#include "yaMeshRenderer.h"
#include "yaObject.h"


namespace ya
{
	Monster::Monster()

	{

	}
	Monster::~Monster()
	{
	}
	void Monster::Initialize()
	{
		GameObject::Initialize();

		tr = this->GetComponent<Transform>();
		tr->SetPosition(Vector3(0.f, -0.5f, 0.0f));

	}
	void Monster::Update()
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

		if (Input::GetKeyDown(KEY_CODE::SPACE) /*|| Input::GetKey(KEY_CODE::SPACE*/)
		{
			//Bullet* bullet = new Bullet;
			Bullet* bullet = object::Instantiate<Bullet>(LAYERTYPE::Attack);
			Transform* bullettr = bullet->GetComponent<Transform>();
			Vector3 playerpos = this->GetComponent<Transform>()->GetPosition();
			bullettr->SetPosition(Vector3(playerpos));
			bullettr->SetScale(Vector3(0.5f, 0.5f, 0.5f));

			MeshRenderer* meshRenderer = bullet->AddComponent<MeshRenderer>();
			meshRenderer->SetMesh(Resources::Find<Mesh>(L"TriangleMesh"));
			meshRenderer->SetShader(Resources::Find<Shader>(L"TriangleShader"));

			SceneManager::GetActiveScene()->AddGameObject(bullet, LAYERTYPE::Attack);
		}

		GameObject::Update();

	}
	void Monster::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Monster::Render()
	{
		GameObject::Render();
	}
}