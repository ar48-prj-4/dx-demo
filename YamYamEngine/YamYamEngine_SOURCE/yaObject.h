#pragma once
#include "yaScene.h"
#include "yaGameObject.h"
#include "yaSceneManager.h"
#include "yaTransform.h"

namespace ya::object
{
	template <typename T>
	static __forceinline T* Instantiate(LAYER type)
	{
		T* gameObject = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(gameObject, type);
		gameObject->Initialize();
		gameObject->SetLAYER(type);

		return gameObject;
	}


	template <typename T>
	static __forceinline T* Instantiate(LAYER type, Vector2 position)
	{
		T* gameObject = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(gameObject, type);
		gameObject->Initialize();
		gameObject->SetLAYER(type);
		gameObject->GetComponent<Transform>()->SetPosition(position);

		return gameObject;
	}

}

