#include "SceneManager.h"
#include "Level1.h"
#include "Level2.h"

int SceneManager::GetSceneMaxScore(int currentscene)
{
	switch (currentscene)
	{
	case 1:
		return 600;
	case 2:
		return 700;
	default:
		return 800;
	}
}

Engine::eScene * SceneManager::GetNewScene(int currentscene, GameData* gData)
{
	Engine::eScene* scene = nullptr;

	switch (currentscene)
	{
	case 1:
	{
		scene = new Level1(gData);
		scene->Init();		
	} break;
	case 2:
	{
		scene = new Level2(gData);
		scene->Init();
	} break;
	default:
		scene = new Level1(gData);
		scene->Init();
	}

	return scene;
}
