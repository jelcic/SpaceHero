#pragma once
#include "Constants.h"

class GameData
{
public:
	// Return current level number
	int GetLevelNumber();
	// Return current score
	int GetPlayerScore();
	// Return players lifes left
	int GetPlayerLives();
	// Return current player health
	int GetPlayerEnergy();
	// Return current ship fuel amount 
	int GetPlayerFuel();
	// Return percent of level objective
	float GetPlayerScorePercent();

	// Reset data for a new game 
	void ResetGameData();
	// Reset data on level complited 
	void NewLevelReset();
	// Reset data on player crash
	void ResetLevel();

	void NextLevel();
	void IncreaseScore(float amount);
	void IncreaseEnergy();
	void DecreaseEnergy(int amount);
	void DecreaseFuel(int amount);
	void DecreaseLives();

	bool CompleteMessageShow{ false }; 
	bool GameOverMessageShow{ false };
	bool WelcomeMessageShow{ false };
private:
	int levelNumber{};
	float score{};
	int playerLives{ 3 };
	int playerEnergy{ MaxPlayerHealth };
	float playerFuel{ MaxShipFuel };
};
