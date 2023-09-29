#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Bullet : public GameObject
	{
	public:

		Bullet();
		virtual ~Bullet();
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:


	};
}



