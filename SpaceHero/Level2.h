#pragma once
#include "eScene.h"
#include "GameData.h"

class Level2 : public Engine::eScene
{
public:
	Level2(GameData* data = nullptr);
	~Level2();

	void Init() override;

	// Persist game data
	GameData* gData;
};
