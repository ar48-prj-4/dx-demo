#include "IJ_PlayerAim_Temp.h"
#include "yaTransform.h"
#include "yaCollider.h"

#include "yaInput.h"



namespace IJ
{
	PlayerAim_Temp::PlayerAim_Temp()
		: m_Owner_Player(nullptr)
		, Boxes_In_Collision({})
		, m_Box_Grabbing(nullptr)
	{
		Boxes_In_Collision.reserve(10);
	}

	PlayerAim_Temp::~PlayerAim_Temp()
	{
	}

	void PlayerAim_Temp::Initialize()
	{
		AddComponent<ya::Transform>();
		AddComponent<ya::Collider>();

		ya::GameObject::Initialize();
	}

	void PlayerAim_Temp::Update()
	{
		ya::GameObject::Update();

		// space�� ������ ���� ����� ���ڸ� �����ϴ�
		// �̹� ���ڸ� ����ִٸ� �����ϴ�
		// ���� ����� �� ���ϱ�� ���߿� ���� ����
		GO_Box* m_Most_Close_Box = nullptr;

		if (ya::Input::GetKeyDown(ya::eKeyCode::SPACE))
		{
			// �ƹ��͵� ������� ���� ���¶��
			if (m_Box_Grabbing == nullptr)
			{
				// ��ó�� ���ڰ� ���ٸ� ���� �ʽ��ϴ�
				if (m_Most_Close_Box != nullptr)
				{
					m_Box_Grabbing = m_Most_Close_Box;
					m_Box_Grabbing->SetBoxState(GO_Box::eBoxState::Grabbed);
					m_Box_Grabbing->SetGrabber(m_Owner_Player);
				}
			}
			// �̹� �ڽ��� ���������
			else
			{
				m_Most_Close_Box->SetBoxState(GO_Box::eBoxState::Idle);
			}
		}
	}

	void PlayerAim_Temp::LateUpdate()
	{
		ya::GameObject::LateUpdate();
	}

	void PlayerAim_Temp::Render()
	{
		ya::GameObject::Render();
	}

	void PlayerAim_Temp::OnCollisionEnter(ya::Collider* other)
	{
		ya::GameObject* other_GO = other->GetOwner();
		GO_Box* other_Box = dynamic_cast<GO_Box*>(other_GO);

		Boxes_In_Collision.push_back(other_Box);
	}

	void PlayerAim_Temp::OnCollisionStay(ya::Collider* other)
	{
	}

	void PlayerAim_Temp::OnCollisionExit(ya::Collider* other)
	{
		ya::GameObject* other_GO = other->GetOwner();
		GO_Box* other_Box = dynamic_cast<GO_Box*>(other_GO);

		for (size_t i = 0; i < Boxes_In_Collision.size(); i++)
		{
			if (Boxes_In_Collision[i] == other_Box)
				Boxes_In_Collision.erase(Boxes_In_Collision.begin() + i);
		}
	}
}