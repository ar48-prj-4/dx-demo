#include "yaPlayScene.h"
#include "yaResources.h"

#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaPlayerScript.h"
#include "yaPlayer.h"
#include "yaInput.h"
#include "yaRigidbody.h"
#include "yaMonster.h"
#include "yaCollisionManager.h"

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
		tr->SetPosition(Vector3(0.8f, 0.5f, 0.0f));
		tr->SetScale(Vector3(0.5f, 0.5f, 0.5f));

		MeshRenderer* meshRenderer = player->AddComponent<MeshRenderer>();
		meshRenderer->SetMesh(Resources::Find<Mesh>(L"TriangleMesh"));
		meshRenderer->SetShader(Resources::Find<Shader>(L"TriangleShader"));

		AddGameObject(player, LAYER::PLAYER);
		player->AddComponent<PlayerScript>();

		Monster* mon = new Monster();
		Transform* tr1 = mon->AddComponent<Transform>();
		tr1->SetPosition(Vector3::Zero);
		tr1->SetScale(Vector3(0.5f, 0.5f, 0.5f));

		MeshRenderer* meshRenderer1 = mon->AddComponent<MeshRenderer>();
		meshRenderer1->SetMesh(Resources::Find<Mesh>(L"TriangleMesh"));
		meshRenderer1->SetShader(Resources::Find<Shader>(L"TriangleShader"));

		AddGameObject(mon, LAYER::MONSTER);
		//mon->AddComponent<PlayerScript>();

		CollisionManager::CollisionLayerCheck(6, 8, false);
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
