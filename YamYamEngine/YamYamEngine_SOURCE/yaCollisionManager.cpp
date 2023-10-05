#include "yaCollisionManager.h"
#include "yaScene.h"			// �ش� �� �ȿ� �ִ� ���̾���� �����;� ��
#include "yaSceneManager.h"

namespace ya
{
	std::map<UINT64, bool> CollisionManager::mCollisionMap = {};
	std::bitset<LAYER_MAX> CollisionManager::mLayerMasks[LAYER_MAX] = {};

	void CollisionManager::Initialize()
	{
		// ���� ���̾�� �浹�� �� �� �ֵ��� ����
		for (int i = 0; i < LAYER_MAX; i++)
		{
			for (int j = 0; j < LAYER_MAX; j++)
			{
				mLayerMasks[i][j] = false;
				
				// ���̾ ������
				if (i == j)
				{
					mLayerMasks[i][j] = true;
				}
			}
		}
	}

	void CollisionManager::Update()
	{
		Scene* activeScene = SceneManager::GetActiveScene();		// ���� ������
		for (size_t row = 0; row < LAYER_MAX; row++)
		{
			for (size_t col = 0; col < LAYER_MAX; col++)
			{
				if (mLayerMasks[row][col] == true)					// �浹�Ǿ��� ��	
				{
					LayerCollision(activeScene, (LAYER)row, (LAYER)col);
				}
			}
		}
	}

	void CollisionManager::LateUpdate()
	{
	}

	void CollisionManager::Render()
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

	void CollisionManager::CollisionLayerCheck(LAYER left, LAYER right, bool enable)
	{
		// �迭�� ����Ͽ� ���̾ �浹�� ǥ���ϴµ� 
		// 2���� �迭�� �ݸ� ����ϱ� ���� �ڵ�

		int row = -1;
		int col = -1;

		if (left > right)
		{
			row = (UINT)left;
			col = (UINT)right;
		}
		else
		{
			col = (UINT)left;
			row = (UINT)right;
		}
		mLayerMasks[row][col] = enable;
	}

	// �浹 üũ�ϴ� �Լ�
	void CollisionManager::LayerCollision(Scene* scene, LAYER left, LAYER right)
	{
		// finds left layer objects
		Layer& leftLayer = scene->GetLayer(left);
		std::vector<GameObject*>& lefts = leftLayer.GetGameObjects();

		Layer& rightLayer = scene->GetLayer(right);
		std::vector<GameObject*>& rights = rightLayer.GetGameObjects();

		// finds right layer Objects
		// �浹 üũ
		for (GameObject* left : lefts)
		{
			// �浹ü�� ���ٸ� continue
			Collider* leftCol = left->GetComponent<Collider>();
			if (leftCol == nullptr)
				continue;

			for (GameObject* right : rights)
			{
				Collider* rightCol = right->GetComponent<Collider>();

				// �浹ü�� ���ٸ� continue
				if (rightCol == nullptr)
					continue;

				// �ڱ� �ڽŰ� ���� ��� continue
				if (left == right)
					continue;

				// �浹����
				ColliderCollision(leftCol, rightCol);
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider* left, Collider* right)
	{
		// �� �浹ü�� ID�� Ȯ��
		ColliderID ID;
		ID.left = (UINT)left->GetID();
		ID.right = (UINT)right->GetID();

		// ���� �浹ü�� ������ �����ͼ� Ȯ���Ѵ�.
		std::map<UINT64, bool>::iterator iter
			= mCollisionMap.find(ID.id);

		// �浹������ ���ٸ� ����
		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(ID.id, false));
			iter = mCollisionMap.find(ID.id);
		}

		// �浹�Լ� ȣ��
		// �浹�ߴٸ� 
		if (Intersect(left, right))
		{
			int a = 0;
			// ó�� �浹�ϴ� ����
			if (iter->second == false)
			{
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);

				iter->second = true;

			}
			else // �浹 ���λ���
			{
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else
		{
			// �浹�� ������������
			if (iter->second == true)
			{
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);

				iter->second = false;
			}
		}
	}

	// Collider ��ġ, Transform ��ġ ����ȭ �ʿ�
	bool CollisionManager::Intersect(Collider* left, Collider* right)	// �浹 ���� ����
	{
		Vector3 LeftPos = left->GetPosition();
		Vector3 RightPos = right->GetPosition();

		Vector3 LeftSize = left->GetSize();
		Vector3 RightSize = right->GetSize();

		//�浹üũ�� �����ִ� ����ü(z�� 1�� ���� : 2D ������� ó���ϱ� ����)
		DirectX::BoundingBox LeftRect{ { LeftPos.x, LeftPos.y, 1 }, { LeftSize.x / 2, LeftSize.y / 2, 1  } };
		DirectX::BoundingBox RightRect{ { RightPos.x, RightPos.y, 1 }, { RightSize.x / 2, RightSize.y / 2 , 1 } };

		//Intersects - �浹 �� True ��ȯ
		return LeftRect.Intersects(RightRect);
	}

}