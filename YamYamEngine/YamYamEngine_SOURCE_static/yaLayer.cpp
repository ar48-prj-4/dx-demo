#include "yaLayer.h"

#include "yaSceneManager.h"
#include "yaCollisionManager.h"


namespace ya
{
	Layer::Layer() : mType(NONE)
	{
	}

	Layer::~Layer()
	{
		for (const GameObject* gameObject : mGameObjects)
		{
			delete gameObject;
			gameObject = nullptr;
		}
	}

	bool Layer::LayerItemCheck(GameObject* obj)
	{
		if (obj->GetLayer() != mType)
		{
			SceneManager::GetActiveScene()->AddGameObject(obj, obj->GetLayer());
			std::erase_if(mGameObjects, [&](const auto* cmp)
			{
				return cmp == obj;
			});

			return true;
		}

		return false;
	}

	void Layer::Initialize()
	{
		for(int i = 0; i < mGameObjects.size(); i++)
		{
			mGameObjects[i]->Initialize();
			LayerItemCheck(mGameObjects[i]);
		}
	}

	void Layer::Update()
	{
		for(int i = 0; i < mGameObjects.size(); i++)
		{
			// 객체가 죽으면 이터레이터로 순회하면서 삭제
			if (mGameObjects[i]->GetState() == GameObject::eState::Dead)
			{
				continue;
			}

			mGameObjects[i]->Update();

			if (LayerItemCheck(mGameObjects[i]))
			{
				continue;
			}
		}


		//for (std::vector<GameObject*>::iterator iter = mGameObjects.begin()
		//	; iter != mGameObjects.end()
		//	; )
		//{
		//	// 객체가 죽으면 이터레이터로 순회하면서 삭제
		//	if ((*iter)->GetState() == GameObject::eState::Dead)
		//	{
		//		iter = mGameObjects.erase(iter);
		//		GameObject* deadObj = *iter;
		//		delete deadObj;
		//		deadObj = nullptr;
		//	}
		//	else
		//	{
		//		iter++;
		//	}
		//}
	}

	void Layer::LateUpdate()
	{
		for(int i = 0; i < mGameObjects.size(); i++)
		{
			mGameObjects[i]->LateUpdate();
		}
	}

	void Layer::Render()
	{
		for(int i = 0; i < mGameObjects.size(); i++)
		{
			if (mGameObjects[i]->GetState() == GameObject::eState::Dead)
			{
				delete mGameObjects[i];
				mGameObjects[i] = nullptr;
				mGameObjects.erase(mGameObjects.begin() + i);
				i--;
				continue;
			}

			mGameObjects[i]->Render();
		}

	}

	void Layer::AddGameObject(GameObject* gameObject)
	{
		mGameObjects.push_back(gameObject);
	}
}
