#include "yaCollisionManager.h"
#include "yaScene.h"			// 해당 씬 안에 있는 레이어들을 가져와야 함
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
		Scene* activeScene = SceneManager::GetActiveScene();		// 씬을 가져옴
		for (size_t row = 0; row < LAYER_MAX; row++)
		{
			for (size_t col = row; col < LAYER_MAX; col++)
			{
				if (mLayerMasks[row][col] == true)					// 충돌되었을 때	
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
		// 씬이 넘어갔을 때 기존 충돌 정보 초기화
		// mLayerMasks->reset() for문 돌려야함
		mLayerMasks->reset();
		mCollisionMap.clear();
	}

	void CollisionManager::CollisionLayerCheck(UINT  left, UINT  right, bool enable)
	{
		// 배열을 사용하여 레이어간 충돌을 표시하는데 
		// 2차원 배열의 반만 사용하기 위한 코드

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

	// 충돌 체크하는 함수
	void CollisionManager::LayerCollision(Scene* scene, LAYER left, LAYER right)
	{
		// finds left layer objects
		//Layer& leftLayer = scene->GetLayer(left);
		//std::vector<GameObject*>& lefts = leftLayer.GetGameObjects();

		//Layer& rightLayer = scene->GetLayer(right);
		//std::vector<GameObject*>& rights = rightLayer.GetGameObjects();

		//// finds right layer Objects
		//// 충돌 체크
		//for (GameObject* left : lefts)
		//{
		//	// 충돌체가 없다면 continue
		//	Collider* leftCol = left->GetComponent<Collider>();
		//	if (leftCol == nullptr)
		//		continue;

		//	for (GameObject* right : rights)
		//	{
		//		Collider* rightCol = right->GetComponent<Collider>();

		//		// 충돌체가 없다면 continue
		//		if (rightCol == nullptr)
		//			continue;

		//		// 자기 자신과 같은 경우 continue
		//		if (left == right)
		//			continue;

		//		// 충돌연산
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
		//// 두 충돌체의 ID를 확인
		//ColliderID ID;
		//ID.left = (UINT)left->GetID();
		//ID.right = (UINT)right->GetID();

		//// 이전 충돌체의 정보를 가져와서 확인한다.
		//std::map<UINT64, bool>::iterator iter
		//	= mCollisionMap.find(ID.id);

		//// 충돌정보가 없다면 생성
		//if (iter == mCollisionMap.end())
		//{
		//	mCollisionMap.insert(std::make_pair(ID.id, false));
		//	iter = mCollisionMap.find(ID.id);
		//}

		//// 충돌함수 호출
		//// 충돌했다면 
		//if (Intersect(left, right))
		//{
		//	// 처음 충돌하는 상태
		//	if (iter->second == false)
		//	{
		//		left->OnCollisionEnter(right);
		//		right->OnCollisionEnter(left);

		//		iter->second = true;

		//	}
		//	else // 충돌 중인상태
		//	{
		//		left->OnCollisionStay(right);
		//		right->OnCollisionStay(left);
		//	}
		//}
		//else
		//{
		//	// 충돌을 빠져나간상태
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



		// 분리축 벡터 4개 구하기
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
		// 숙제 Circle vs Cirlce

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

	bool CollisionManager::Intersect(Collider* left, Collider* right)	// 충돌 상태 여부
	{
		//Vector2 leftPos = left->GetPosition();
		//Vector2 rightPos = right->GetPosition();

		//Vector2 leftSize = left->GetSize();
		//Vector2 rightSize = right->GetSize();

		//// fabs 절대값
		//// x 충돌 && y 충돌(2로 나누는 건 원에서처럼 반지름을 구하려고)
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