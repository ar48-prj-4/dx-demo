#pragma once
#include "yaGameObject.h"


namespace IJ
{
	class GO_Box : public ya::GameObject
	{
	public:
		// ���� ���� �׳� bool ������ ó���� �� ���� �� ����
		enum eBoxState
		{
			Idle,
			Grabbed,
			END,
		};

		GO_Box();
		virtual ~GO_Box();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		eBoxState GetBoxState() { return e_Current_Box_State; }
		void SetBoxState(eBoxState box_state) { e_Current_Box_State = box_state; }
		GameObject* GetGrabber() { return m_Grabber; }
		void SetGrabber(GameObject* grabber) { m_Grabber = grabber; }

	private:
		eBoxState e_Current_Box_State;
		GameObject* m_Grabber;
	};
}
