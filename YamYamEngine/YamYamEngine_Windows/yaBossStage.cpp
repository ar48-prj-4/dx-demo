#include "yaBossStage.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaPlayerScript.h"
#include "yaPlayer.h"
#include "yaInput.h"
#include "yaRigidbody.h"
#include "yaCollisionManager.h"
#include "yaLight.h"
#include "yaPortal.hpp"
#include "yaTurret.h"
#include "yaTurretScript.h"
#include "IJ_Button.h"
#include "yaTile.h"
#include "yaBoss.h"
#include "yaBossScript.h"
#include "yaBossShadow.h"

namespace ya
{
	BossStage::BossStage()
	{
	}
	BossStage::~BossStage()
	{
	}
	void BossStage::Initialize()
	{
		Scene::Initialize();

		//Boss
		{
			Boss* boss = new Boss();
			boss->Initialize();

			MeshRenderer* meshRenderer = boss->AddComponent<MeshRenderer>();
			meshRenderer->SetMesh(Resources::Find<Mesh>(L"TriangleMesh"));
			meshRenderer->SetShader(Resources::Find<Shader>(L"ColorShader"));

			Transform* tr = boss->GetComponent<Transform>();
			auto bosscol = boss->GetComponent<Collider>();
			auto bossrb = boss->GetComponent<Rigidbody>();
			boss->AddComponent<BossScript>();

			tr->SetPosition(Vector3(2.5f, 0.2f, 1.0f));
			tr->SetScale(Vector3(2.0f, 2.0f, 1.0f));

			bosscol->SetSize(Vector3(1.0f, 1.0f, 1.0f));

			// ** 테스트용으로 플레이어의 중력을 없애놨음. 나중에 풀어야 함!! **
			bossrb->SetGravity(Vector3::Zero);

			bossrb->SetFriction(0.25f);

			AddGameObject(boss, LAYER::BOSS);
			AddGameObject(boss->GetBossShadow(), LAYER::BOSS);
		}


	}
	void BossStage::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::U))
		{
			BossStage::Load();
		}
	}
	void BossStage::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void BossStage::Render()
	{
		Scene::Render();
	}
	void BossStage::Load()
	{
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = L"..\\Resources\\Map\\Test.tm";

		// rb : 이진수로 파일을 읽음
		FILE* pFile = nullptr;
		_wfopen_s(&pFile, szFilePath, L"rb");

		if (pFile == nullptr)
			return;

		while (true)
		{
			int	myX = -1;
			int myY = -1;

			Tile::eTileType myType = Tile::eTileType::End;

			//Vector3 myPos = Vector3::Zero;

			if (fread(&myX, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&myY, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&myType, sizeof(Tile::eTileType), 1, pFile) == NULL)
				break;
			//if (fread(&myPos, sizeof(Vector3), 1, pFile) == NULL)
				//break;


			Vector3 offset = Vector3::Zero;

			Tile* tile = new Tile();

			tile->GetComponent<Transform>()->SetPosition(myX * (TILE_WIDTH)+offset.x + LEFT_TOP_X
				, myY * (TILE_HEIGHT)+offset.y + LEFT_TOP_Y, 1);

			//tile->GetComponent<Transform>()->SetPosition(myPos);

			tile->SetTileIdx(myX, myY);
			// 불러온 myType을 tile 객체에 텋는다
			tile->SetType(myType);

			if (tile->GetType() == Tile::eTileType::Circle)
			{
				tile->SetCircle(tile);

			}
			else if (tile->GetType() == Tile::eTileType::Triangle)
			{
				tile->SetTriangle(tile);
			}
			else if (tile->GetType() == Tile::eTileType::Square)
			{
				tile->SetSquare(tile);
			}
			else if (tile->GetType() == Tile::eTileType::Floor)
			{
				tile->SetFloor(tile);
			}

			AddGameObject(tile, LAYER::TILE);

			mTiles.push_back(tile);
		}

		// 메모리 할당된 것을 삭제해주는 함수
		fclose(pFile);
	}
}