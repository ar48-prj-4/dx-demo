#pragma once
#include "yaGameObject.h"
#include "yaPlayer.h"


namespace IJ
{
	class Item : public ya::GameObject
	{
	public:
		Item();
		virtual ~Item();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(class ya::Collider* other);
		virtual void OnCollisionStay(class ya::Collider* other);
		virtual void OnCollisionExit(class ya::Collider* other);

		virtual void ItemEffect(ya::Player* player) = 0;

	private:

	};
}
