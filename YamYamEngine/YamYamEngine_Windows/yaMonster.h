#pragma once
#include "yaGameObject.h"
#include "yaTransform.h"

namespace ya
{
	class Monster : public GameObject
	{
	public:

		Monster();
		virtual ~Monster();
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:
		Transform* tr;
	};
}



