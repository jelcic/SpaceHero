#pragma once
#include "eGameObject.h"
#include "GameData.h"


class HUD : public Engine::eGameObject
{
public:
	HUD(GameData* data);
	~HUD();
	// Health bar container image and position
	Engine::eImage* HealthBarBox;
	Engine::Vec2 hBarPosition{};

	// Health UI
	Engine::eImage* HealthBar;
	Engine::Vec2 healthPosition{};
	std::string hmessage{ "HEALTH" };
	int CurrentPlayerHealth{130};

	// Fuel bar UI
	Engine::eImage* FuelBar;
	Engine::Vec2 fuelPosition{};
	std::string fmessage{ "FUEL" };
	int CurrentShipFuel{130};
	
	// Score bar UI
	Engine::eImage* ScoreBar;
	Engine::Vec2 scorePosition{};
	std::string omessage{ "FILL IT UP" };
	float scoreCurrentX{762.0f};
	float scoreMaxX{};
	float scoreFullX{};
	float PlayerScorePercent{};

	// Level complete
	std::string completeMessage1{ "YOU WIN!" };
	std::string completeMessage2{ "Well done, soldier!" };

	// Game Over message
	std::string gameOverMessage{ "GAME OVER!" };

	// Welcome message
	std::string welcomeMessage1{ "LEVEL " };
	std::string welcomeMessage2{ "Stay alive and fill your quota!" };
	std::string welcomeMessage3{ "Good luck, soldier!" };
	std::string welcomeMessage4{ "Use arrow keys and 'D' for firing... Press 'up' key when ready." };

	// Fonts for headers
	ID3DXFont* lfont;
	ID3DXFont* hfont;

	// Player lives count 
	std::string lmessage{"3"};

	// Persist game data
	GameData* gData;
private:
	// Obeject overrides
	virtual void init() override;
	virtual void update(float dt) override;
	virtual void draw() override;
};
