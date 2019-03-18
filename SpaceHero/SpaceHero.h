#pragma once

#include "eGame.h"
#include "GameData.h"
#include "Player.h"

class SpaceHero : public Engine::eGame
{
public:
	SpaceHero();
	~SpaceHero();

	void Init() override;

	GameData* gData;
	GameState gState{GameState::MainManu};
private:
	void Update() override;

	// Level complete message 
	float displaymessageTimer{};
	float displayMessageInterval{ 5.0f };

	// Helper methods
	bool isObjectiveReached(Player* player);
	void spawnProjectile(Engine::eScene* scene, Player* player);
	void spawnAsteroid(Engine::eScene* scene);
	void levelComplete(Player* player);
	void gameOver();
};

