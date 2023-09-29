#include "yaCollisionManager.h"
#include "yaScene.h"			// �ش� �� �ȿ� �ִ� ���̾���� �����;� ��
#include "yaSceneManager.h"
#include "yaTransform.h"

namespace ya
{
	std::map<UINT64, bool> CollisionManager::mCollisionMap = {};
	std::bitset<LAYER_MAX> CollisionManager::mLayerMasks[LAYER_MAX] = {};

	void CollisionManager::Initialize()
	{
	}

	void CollisionManager::Update()
	{
		Scene* activeScene = SceneManager::GetActiveScene();		// ���� ������
		for (size_t row = 0; row < LAYER_MAX; row++)
		{
			for (size_t col = row; col < LAYER_MAX; col++)
			{
				if (mLayerMasks[row][col] == true)					// �浹�Ǿ��� ��	
				{
					LayerCollision(activeScene, (LAYER)row, (LAYER)col);
				}
			}
		}
	}

	void CollisionManager::Render(HDC hdc)
	{
	}

	void CollisionManager::Release()
	{
	}

	void CollisionManager::Clear()
	{
		// ���� �Ѿ�� �� ���� �浹 ���� �ʱ�ȭ
		// mLayerMasks->reset() for�� ��������
		mLayerMasks->reset();
		mCollisionMap.clear();
	}

	void CollisionManager::CollisionLayerCheck(UINT  left, UINT  right, bool enable)
	{
		// �迭�� ����Ͽ� ���̾ �浹�� ǥ���ϴµ� 
		// 2���� �迭�� �ݸ� ����ϱ� ���� �ڵ�

		//int row = -1;
		//int col = -1;

		//if (left > right)
		//{
		//	row = (UINT)left;
		//	col = (UINT)right;
		//}
		//else
		//{
		//	col = (UINT)left;
		//	row = (UINT)right;
		//}
		//mLayerMasks[row][col] = enable;

		int row = 0;
		int column = 0;
		if (left <= right)
		{
			row = left;
			column = right;
		}
		else
		{
			row = right;
			column = left;
		}

		mLayerMasks[row][column] = enable;
	}

	bool CollisionManager::GetCollisionID(Collider* left, Collider* right)
	{
		return false;
	}

	void CollisionManager::SetCollisionID(Collider* left, Collider* right, bool enable)
	{
	}

	// �浹 üũ�ϴ� �Լ�
	void CollisionManager::LayerCollision(Scene* scene, LAYER left, LAYER right)
	{
		// finds left layer objects
		//Layer& leftLayer = scene->GetLayer(left);
		//std::vector<GameObject*>& lefts = leftLayer.GetGameObjects();

		//Layer& rightLayer = scene->GetLayer(right);
		//std::vector<GameObject*>& rights = rightLayer.GetGameObjects();

		//// finds right layer Objects
		//// �浹 üũ
		//for (GameObject* left : lefts)
		//{
		//	// �浹ü�� ���ٸ� continue
		//	Collider* leftCol = left->GetComponent<Collider>();
		//	if (leftCol == nullptr)
		//		continue;

		//	for (GameObject* right : rights)
		//	{
		//		Collider* rightCol = right->GetComponent<Collider>();

		//		// �浹ü�� ���ٸ� continue
		//		if (rightCol == nullptr)
		//			continue;

		//		// �ڱ� �ڽŰ� ���� ��� continue
		//		if (left == right)
		//			continue;

		//		// �浹����
		//		ColliderCollision(leftCol, rightCol);
		//	}
		//}

		const std::vector<GameObject*>& lefts = scene->GetLayer(left)->GetGameObjects();
		const std::vector<GameObject*>& rights = scene->GetLayer(right)->GetGameObjects();

		for (GameObject* left : lefts)
		{
			GameObject::eState state = left->GetActive();
			if (state == GameObject::eState::Dead
				|| state == GameObject::eState::Paused)
				continue;

			Collider* leftCollider
				= left->GetComponent<Collider>();
			if (leftCollider == nullptr)
				continue;

			for (GameObject* right : rights)
			{
				GameObject::eState state = right->GetActive();
				if (state == GameObject::eState::Dead
					|| state == GameObject::eState::Paused)
					continue;

				Collider* rightCollider
					= right->GetComponent<Collider>();
				if (rightCollider == nullptr)
					continue;
				if (right == left)
					continue;

				ColliderCollision(leftCollider, rightCollider);
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider* left, Collider* right)
	{
		//// �� �浹ü�� ID�� Ȯ��
		//ColliderID ID;
		//ID.left = (UINT)left->GetID();
		//ID.right = (UINT)right->GetID();

		//// ���� �浹ü�� ������ �����ͼ� Ȯ���Ѵ�.
		//std::map<UINT64, bool>::iterator iter
		//	= mCollisionMap.find(ID.id);

		//// �浹������ ���ٸ� ����
		//if (iter == mCollisionMap.end())
		//{
		//	mCollisionMap.insert(std::make_pair(ID.id, false));
		//	iter = mCollisionMap.find(ID.id);
		//}

		//// �浹�Լ� ȣ��
		//// �浹�ߴٸ� 
		//if (Intersect(left, right))
		//{
		//	// ó�� �浹�ϴ� ����
		//	if (iter->second == false)
		//	{
		//		left->OnCollisionEnter(right);
		//		right->OnCollisionEnter(left);

		//		iter->second = true;

		//	}
		//	else // �浹 ���λ���
		//	{
		//		left->OnCollisionStay(right);
		//		right->OnCollisionStay(left);
		//	}
		//}
		//else
		//{
		//	// �浹�� ������������
		//	if (iter->second == true)
		//	{
		//		left->OnCollisionExit(right);
		//		right->OnCollisionExit(left);

		//		iter->second = false;
		//	}
		//}

		bool check = GetCollisionID(left, right);

		if (Intersect(left, right))
		{
			if (check == false)
			{
				CollisionEnter(left, right);
				SetCollisionID(left, right, true);
			}
			else if (check == true)
			{
				CollisionStay(left, right);
			}
		}
		else
		{
			if (check == true)
			{
				CollisionExit(left, right);
				SetCollisionID(left, right, false);
			}
		}
	}

	bool CollisionManager::RectToRect(Collider* left, Collider* right)
	{
		// Rect vs Rect 
			// 0 --- 1
			// |     |
			// 3 --- 2
		Vector3 arrLocalPos[4] =
		{
		   Vector3{-0.5f, 0.5f, 0.0f}
		   ,Vector3{0.5f, 0.5f, 0.0f}
		   ,Vector3{0.5f, -0.5f, 0.0f}
		   ,Vector3{-0.5f, -0.5f, 0.0f}
		};

		Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
		Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

		Matrix leftMat = leftTr->GetWorldMatrix();
		Matrix rightMat = rightTr->GetWorldMatrix();



		// �и��� ���� 4�� ���ϱ�
		Vector3 Axis[4] = {};

		Vector3 leftScale = Vector3(left->GetSize().x, left->GetSize().y, 1.0f);

		Matrix finalLeft = Matrix::CreateScale(leftScale);
		finalLeft *= leftMat;

		Vector3 rightScale = Vector3(right->GetSize().x, right->GetSize().y, 1.0f);
		Matrix finalRight = Matrix::CreateScale(rightScale);
		finalRight *= rightMat;

		Axis[0] = Vector3::Transform(arrLocalPos[1], finalLeft);
		Axis[1] = Vector3::Transform(arrLocalPos[3], finalLeft);
		Axis[2] = Vector3::Transform(arrLocalPos[1], finalRight);
		Axis[3] = Vector3::Transform(arrLocalPos[3], finalRight);

		Axis[0] -= Vector3::Transform(arrLocalPos[0], finalLeft);
		Axis[1] -= Vector3::Transform(arrLocalPos[0], finalLeft);
		Axis[2] -= Vector3::Transform(arrLocalPos[0], finalRight);
		Axis[3] -= Vector3::Transform(arrLocalPos[0], finalRight);

		for (size_t i = 0; i < 4; i++)
			Axis[i].z = 0.0f;

		Vector3 vc = leftTr->GetPosition() - rightTr->GetPosition();
		vc.z = 0.0f;

		Vector3 centerDir = vc;
		for (size_t i = 0; i < 4; i++)
		{
			Vector3 vA = Axis[i];
			//vA.Normalize();

			float projDist = 0.0f;
			for (size_t j = 0; j < 4; j++)
			{
				projDist += fabsf(Axis[j].Dot(vA) / 2.0f);
			}

			if (projDist < fabsf(centerDir.Dot(vA)))
			{
				return false;
			}
		}
		// ���� Circle vs Cirlce

		return true;
	}

	void CollisionManager::CollisionEnter(Collider* left, Collider* right)
	{
		if (left->IsTrigger())
			left->OnTriigerEnter(right);
		else
			left->OnCollisionEnter(right);

		if (right->IsTrigger())
			right->OnTriigerEnter(left);
		else
			right->OnCollisionEnter(left);
	}

	void CollisionManager::CollisionStay(Collider* left, Collider* right)
	{
		if (left->IsTrigger())
			left->OnTriigerStay(right);
		else
			left->OnCollisionStay(right);

		if (right->IsTrigger())
			right->OnTriigerStay(left);
		else
			right->OnCollisionStay(left);
	}

	void CollisionManager::CollisionExit(Collider* left, Collider* right)
	{
		if (left->IsTrigger())
			left->OnTriigerExit(right);
		else
			left->OnCollisionExit(right);

		if (right->IsTrigger())
			right->OnTriigerExit(left);
		else
			right->OnCollisionExit(left);
	}

	bool CollisionManager::Intersect(Collider* left, Collider* right)	// �浹 ���� ����
	{
		//Vector2 leftPos = left->GetPosition();
		//Vector2 rightPos = right->GetPosition();

		//Vector2 leftSize = left->GetSize();
		//Vector2 rightSize = right->GetSize();

		//// fabs ���밪
		//// x �浹 && y �浹(2�� ������ �� ������ó�� �������� ���Ϸ���)
		//if (fabs(leftPos.x - rightPos.x) < fabs(leftSize.x / 2.0f + rightSize.x / 2.0f)
		//	&& fabs(leftPos.y - rightPos.y) < fabs(leftSize.y / 2.0f + rightSize.y / 2.0f))
		//{
		//	return true;
		//}

		//return false;

		if (left->GetType() == COLLIDERTYPE::RECT
			&& right->GetType() == COLLIDERTYPE::RECT)
		{
			return RectToRect(left, right);
		}

		return false;
	}

}