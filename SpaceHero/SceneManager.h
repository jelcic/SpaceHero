#pragma once
#include "eScene.h"
#include "GameData.h"

class SceneManager
{
public:
	static int GetSceneMaxScore(int currentLevel);
	static Engine::eScene* GetNewScene(int currentLevel, GameData* gData);
};