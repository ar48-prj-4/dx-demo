#include "yaPlayScene.h"
#include "yaResources.h"

#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaPlayerScript.h"
#include "yaPlayer.h"
#include "yaInput.h"
#include "yaRigidbody.h"

namespace ya
{
	PlayScene::PlayScene()
	{
	}


	PlayScene::~PlayScene()
	{

	}

	void PlayScene::Initialize()
	{
		Scene::Initialize();

		Player* player = new Player();

		Transform* tr = player->AddComponent<Transform>();
		tr->SetPosition(Vector3(0.8f, 0.2f, 0.0f));
		tr->SetScale(Vector3(0.5f, 0.5f, 1.0f));

		MeshRenderer* meshRenderer = player->AddComponent<MeshRenderer>();
		meshRenderer->SetMesh(Resources::Find<Mesh>(L"TriangleMesh"));
		meshRenderer->SetShader(Resources::Find<Shader>(L"TriangleShader"));

		AddGameObject(player, LAYER::PLAYER);
		player->AddComponent<PlayerScript>();

		Player* player2 = new Player();

		Transform* tr2 = player2->AddComponent<Transform>();
		tr2->SetPosition(Vector3(0.2f, 0.2f, 0.0f));
		tr2->SetScale(Vector3(0.5f, 0.5f, 1.0f));

		MeshRenderer* meshRenderer2 = player2->AddComponent<MeshRenderer>();
		meshRenderer2->SetMesh(Resources::Find<Mesh>(L"TriangleMesh"));
		meshRenderer2->SetShader(Resources::Find<Shader>(L"TriangleShader"));

		AddGameObject(player2, LAYER::PLAYER);
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}
}
