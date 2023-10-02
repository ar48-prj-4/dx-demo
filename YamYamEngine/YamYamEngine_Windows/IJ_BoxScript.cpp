#include "IJ_BoxScript.h"
#include "IJ_Box.h"

#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaRigidbody.h"
#include "yaTime.h"

#include "yaPlayer.h"


namespace IJ
{
	BoxScript::BoxScript()
	{
	}

	BoxScript::~BoxScript()
	{
	}

	void BoxScript::Initialize()
	{
	}

	void BoxScript::Update()
	{
		ya::GameObject* gameobject = GetOwner();
		GO_Box* box = dynamic_cast<GO_Box*>(gameobject);

		if (box != nullptr)
		{
			GO_Box::eBoxState e_Box_State;
			e_Box_State = box->GetBoxState();

			switch (e_Box_State)
			{
			case GO_Box::Idle:
				Idle();
				break;
			case GO_Box::Grabbed:
				Grabbed();
				break;
			case GO_Box::END:
				break;
			default:
				break;
			}
		}
	}

	void BoxScript::LateUpdate()
	{
	}

	void BoxScript::Render()
	{
	}

	void BoxScript::Idle()
	{
		// ���� ������ ���� �⺻������ �ƹ��͵� ���ϱ�
	}

	void BoxScript::Grabbed()
	{
		ya::GameObject* m_Owner = GetOwner();
		GO_Box* m_Owner_Box = dynamic_cast<GO_Box*>(m_Owner);

		// ���𰡰� ���� ��Ҵٸ�
		ya::GameObject* m_Grabber = m_Owner_Box->GetGrabber();
		ya::Player* m_Grabber_Player = dynamic_cast<ya::Player*>(m_Grabber);

		// �ƹ��� ���� ���� �ʾҴµ� �� ���¿� ���Դٸ� idle�� ���ư�
		if (m_Grabber == nullptr)
			m_Owner_Box->SetBoxState(GO_Box::eBoxState::Idle);

		if (m_Grabber_Player != nullptr)
		{
			ya::Rigidbody* rigidbody = m_Owner->GetComponent<ya::Rigidbody>();

			// ���ڿ� �÷��̾���� �Ÿ� ���ϱ�
			ya::Transform* tr_Box = m_Owner->GetComponent<ya::Transform>();
			ya::Vector3 pos_Box = tr_Box->GetPosition();
			ya::Transform* tr_Player = m_Grabber->GetComponent<ya::Transform>();
			ya::Vector3 pos_Player = tr_Player->GetPosition();

			float m_Distance = sqrtf(powf(pos_Box.x - pos_Player.x, 2) +
								powf(pos_Box.y - pos_Player.y, 2));

			// ���߿� ���� ����
			// ���𰡿� ��� �������� ���� ���� ���� �÷��̾�� �Ÿ��� �־����� idle�� ���ư�
			//if (fabsf(m_Distance) > 0.5f)
			//{
			//	m_Owner_Box->SetGrabber(nullptr);
			//}

			// ���ÿ� �÷��̾� ������ �̵��ϰ� �Ϸ��� ������
			// �ӽ÷� �÷��̾� �ٷ� ���� �̵��ϰ� �߽��ϴ�
			ya::Vector3 pos_Target = { pos_Player.x, pos_Player.y + 0.1f, pos_Player.z };
			ya::Vector3 m_Direction = pos_Target - pos_Box;
			m_Direction.normalize();
			ya::Vector2 m_Direction_2 = { m_Direction.x, m_Direction.y };
			rigidbody->AddForce(m_Direction_2 * 1.0f * ya::Time::DeltaTime());

			// ���� �߷��� ����ϱ� ���� �߷��� ũ�⸸ŭ ���� ���� �޽��ϴ�
			// �ϴ��� �⺻���� 800.0f ��ŭ�� ���� �ݴϴ�
			rigidbody->AddForce({ 0.0f, -800.0f });
		}
	}
}