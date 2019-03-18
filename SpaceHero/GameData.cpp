#include "GameData.h"
#include "SceneManager.h"

int GameData::GetLevelNumber()
{
	return levelNumber;
}

int GameData::GetPlayerScore()
{
	return (int)score;
}

int GameData::GetPlayerLives()
{
	return playerLives;
}

int GameData::GetPlayerEnergy()
{
	return playerEnergy;
}

int GameData::GetPlayerFuel()
{
	return int(playerFuel);
}

float GameData::GetPlayerScorePercent()
{
	float maxScore = 0.0f;

	return score * 100.0f / SceneManager::GetSceneMaxScore(levelNumber);
}

void GameData::ResetGameData()
{
	levelNumber = 0;
	score = 0;
	playerLives = 3;
	playerEnergy = MaxPlayerHealth;
	playerFuel = MaxShipFuel;
	GameOverMessageShow = false;
}

void GameData::ResetLevel()
{
	score = 0;
	playerEnergy = MaxPlayerHealth;
	playerFuel = MaxShipFuel;
	WelcomeMessageShow = true;
}

void GameData::NewLevelReset()
{
	CompleteMessageShow = false;
	WelcomeMessageShow = true;
	levelNumber++;
	score = 0;
	playerEnergy = MaxPlayerHealth;
	playerFuel = MaxShipFuel;
}

void GameData::NextLevel()
{
	levelNumber++;
}

void GameData::IncreaseScore(float amount)
{
	score += amount;
	float maxScore = (float)SceneManager::GetSceneMaxScore(levelNumber);
	if (score > maxScore)
		score = maxScore;
}

void GameData::IncreaseEnergy()
{
	playerEnergy = 100;
}

void GameData::DecreaseEnergy(int amount)
{
	if (playerEnergy > 0)
		playerEnergy -= amount;
}

void GameData::DecreaseFuel(int amount)
{
	if (playerFuel > 0)
		playerFuel -= amount;
}

void GameData::DecreaseLives()
{
	playerLives--;
}
