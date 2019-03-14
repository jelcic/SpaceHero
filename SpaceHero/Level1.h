#pragma once

#include "eScene.h"
#include "GameData.h"

class Level1 : public Engine::eScene
{
public:
	Level1(GameData* data = nullptr);
	~Level1();

	void Init() override;

	// Persist game data
	GameData* gData;
};
