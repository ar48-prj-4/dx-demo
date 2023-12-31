#pragma once
#include "yaEnums.h"
#include "yaEntity.h"
#include "yaLayer.h"

namespace ya
{
	using namespace ya::enums;

	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		Layer* GetLayer(UINT index) { return& mLayers[index]; }
		Layer& GetLayer(LAYER type) { return mLayers[(UINT)type]; }
		void AddGameObject(GameObject* gameObject, UINT layerIndex);

	private:
		Layer mLayers[LAYER::MAX];
	};
}
