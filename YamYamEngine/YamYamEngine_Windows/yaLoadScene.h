#pragma once
#include "yaSceneManager.h"
#include "yaPlayScene.h"
#include "yaToolScene.h"
#include "yaBossStage.h"


//#ifdef  _DEBUG
//#pragma comment(lib, "..\\x64\\Debug\\YamYamEngine_Windows.lib")
//#else
//#pragma comment(lib, "..\\x64\\Release\\YamYamEngine_Windows.lib")
//#endif //  _DEBUG

namespace ya
{
	void InitializeScenes()
	{
		SceneManager::CreateScene<ToolScene>(L"ToolScene");
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<BossStage>(L"BossStage");

		SceneManager::LoadScene(L"PlayScene");
	}
}