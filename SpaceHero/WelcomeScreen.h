#pragma once
#include "eScene.h"
#include "GameData.h"

class WelcomeScreen : public Engine::eScene
{
public:
	WelcomeScreen(GameData* data);
	~WelcomeScreen();

	void Init() override;

	// Persist game data
	GameData* gData;
};
