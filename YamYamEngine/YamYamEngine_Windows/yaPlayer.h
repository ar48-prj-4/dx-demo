#pragma once
#include "yaGameObject.h"
#include "yaTransform.h"

namespace ya
{
	class Player : public GameObject
	{
	public:

		Player();
		virtual ~Player();
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:
		Transform* tr;
		int HP;
	};
}




