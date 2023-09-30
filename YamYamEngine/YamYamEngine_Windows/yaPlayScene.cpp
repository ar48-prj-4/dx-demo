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
		tr->SetScale(Vector3(0.5f, 0.5f, 1.0f));

		object1->AddComponent<Collider>();

		MeshRenderer* meshRenderer = object1->AddComponent<MeshRenderer>();
		meshRenderer->SetMesh(Resources::Find<Mesh>(L"TriangleMesh"));
		meshRenderer->SetShader(Resources::Find<Shader>(L"TriangleShader"));

		AddGameObject(object1, LAYER::PLAYER);
		object1->AddComponent<PlayerScript>();

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
