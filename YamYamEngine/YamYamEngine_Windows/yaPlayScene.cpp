#include "yaPlayScene.h"
#include "yaResources.h"

#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaPlayerScript.h"
#include "yaCollider.h"
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
		GameObject* object1 = new GameObject();
		Transform* tr = object1->AddComponent<Transform>();
		tr->SetPosition(Vector3(0.5f, 0.2f, 0.0f));
		tr->SetScale(Vector3(2.0f, 2.0f, 1.0f));

		object1->AddComponent<Collider>();

		MeshRenderer* meshRenderer = object1->AddComponent<MeshRenderer>();
		meshRenderer->SetMesh(Resources::Find<Mesh>(L"TriangleMesh"));
		meshRenderer->SetShader(Resources::Find<Shader>(L"TriangleShader"));

		AddGameObject(object1, LAYER::PLAYER);
		object1->AddComponent<PlayerScript>();
		//object->AddComponent<PlayerScript2>();

		GameObject* object2 = new GameObject();
		Transform* tr = object2->AddComponent<Transform>();
		tr->SetPosition(Vector3(0.5f, 0.2f, 0.0f));
		tr->SetScale(Vector3(2.0f, 2.0f, 1.0f));

		object1->AddComponent<Collider>();

		MeshRenderer* meshRenderer = object2->AddComponent<MeshRenderer>();
		meshRenderer->SetMesh(Resources::Find<Mesh>(L"TriangleMesh"));
		meshRenderer->SetShader(Resources::Find<Shader>(L"TriangleShader"));

		AddGameObject(object2, LAYER::MONSTER);
		object2->AddComponent<PlayerScript>();
		//object->AddComponent<PlayerScript2>();

		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::MONSTER, true);

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
