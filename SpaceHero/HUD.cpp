#include "HUD.h"
#include "Director.h"
#include "Constants.h"

HUD::HUD(GameData * data) : gData(data)
{
	id = hudID;
}

HUD::~HUD()
{
	if (lfont)
	{
		lfont->Release();
		lfont = nullptr;
	}

	if (hfont)
	{
		hfont->Release();
		hfont = nullptr;
	}
}

void HUD::init()
{
	zOrder = 10;

	auto director = Engine::Director::getInstance();
	int windowWidth = director->GetGraphicsManager()->GetGameWidth();
	int windowHeight = director->GetGraphicsManager()->GetGameHeight();

	D3DXCreateFont(director->GetGraphicsManager()->GetDevice(), 22, 0, 600, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, "Arial", &lfont);

	D3DXCreateFont(director->GetGraphicsManager()->GetDevice(), 15, 0, 700, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, "Arial", &hfont);

	HealthBarBox = new Engine::eImage("Resources/energyUI.png", energyUI_ID, new RECT{ 0, 71, 200, 0 });
	hBarPosition = { 20.0f, float(windowHeight - 80) };
	
	HealthBar = new Engine::eImage("Resources/energybar.png", energybarID, new RECT{ 0, 15, 134, 0 });
	healthPosition = { hBarPosition.X + 67, float(windowHeight - 40) };
	HealthBar->DrawRect->left = 4;

	FuelBar = new Engine::eImage("Resources/fuelbar.png", fuelbarID, new RECT{ 0, 15, 134, 0 });
	fuelPosition = { hBarPosition.X + 65, float(windowHeight - 57) };

	ScoreBar = new Engine::eImage("Resources/scoreBar.png", scoreBarID, new RECT{ 0, 20, 300, 0 });
	scorePosition = { float(windowWidth - 320), float(windowHeight - 40) };
	scoreMaxX = float(scorePosition.X + 298);
	scoreFullX = float(scorePosition.X + 3);
}

void HUD::update(float dt)
{
	if (gData)
	{
		PlayerScorePercent = gData->GetPlayerScorePercent();
		CurrentPlayerHealth = gData->GetPlayerEnergy();
		CurrentShipFuel = gData->GetPlayerFuel();
		lmessage = std::to_string(gData->GetPlayerLives());
	}

	scoreCurrentX = scoreMaxX - (PlayerScorePercent * (scoreMaxX - scoreFullX) / 100);
	if (scoreCurrentX < scoreFullX || scoreCurrentX > scoreMaxX)
		scoreCurrentX = scoreMaxX;
	
	HealthBar->DrawRect->left = MaxPlayerHealth - CurrentPlayerHealth;	
	FuelBar->DrawRect->left = MaxShipFuel - CurrentShipFuel;
}

void HUD::draw()
{
	auto gManager = Engine::Director::getInstance()->GetGraphicsManager();
	
	HealthBar->Draw(nullptr, healthPosition, HealthBar->textureSize, {}, Engine::Vec2(0.0f, 1.0f), 0.0f, 1.0f);
	gManager->DrawTextMessage(hfont, hmessage, RECT{ 110, 5, 260, 25 }, 0xff9be05c);

	FuelBar->Draw(nullptr, fuelPosition, FuelBar->textureSize, {}, Engine::Vec2(0.0f, 1.0f), 0.0f, 1.0f);
	gManager->DrawTextMessage(hfont, fmessage, RECT{ 110, 62, 260, 80 }, 0xffff0000);

	HealthBarBox->Draw(nullptr, hBarPosition, HealthBarBox->textureSize, {}, Engine::Vec2(0.0f, 1.0f), 0.0f, 1.0f);
	gManager->DrawTextMessage(lfont, lmessage, RECT{33, 51, 60, 70}, 0xff000000);

	gManager->DrawLine(scoreCurrentX, scorePosition.Y + 9, scoreMaxX, scorePosition.Y + 9, 13.0f, false, 0xffffe500);
	ScoreBar->Draw(nullptr, scorePosition, ScoreBar->textureSize, {}, Engine::Vec2(0.0f, 1.0f), 0.0f, 1.0f);
	gManager->DrawTextMessage(hfont, omessage, RECT{ gManager->GetGameWidth() - 150, 50, gManager->GetGameWidth() - 22, 70 }, 0xffffe500, 2);

	if (gData->CompleteMessageShow)
	{
		gManager->DrawTextMessage(completeMessage1, RECT{ gManager->GetGameWidth() / 2 - 150, 200, gManager->GetGameWidth() / 2 + 150, 230 }, 36, 800, 0xffffe500, 1);
		gManager->DrawTextMessage(completeMessage2, RECT{ gManager->GetGameWidth() / 2 - 150, 250, gManager->GetGameWidth() / 2 + 150, 280 }, 32, 800, 0xffffe500, 1);
	}

	if (gData->GameOverMessageShow)
	{
		gManager->DrawTextMessage(gameOverMessage, RECT{ gManager->GetGameWidth() / 2 - 150, 200, gManager->GetGameWidth() / 2 + 150, 230 }, 36, 800, 0xffff0000, 1);
	}

	if (gData->WelcomeMessageShow)
	{
		gManager->DrawTextMessage(lfont, welcomeMessage1 + std::to_string(gData->GetLevelNumber()), RECT{ gManager->GetGameWidth() / 2 - 150, 170, gManager->GetGameWidth() / 2 + 150, 200 }, 0xffff0000, 1);
		gManager->DrawTextMessage(welcomeMessage2, RECT{ gManager->GetGameWidth() / 2 - 150, 200, gManager->GetGameWidth() / 2 + 150, 230 }, 26, 800, 0xff0015ff, 1);
		gManager->DrawTextMessage(welcomeMessage3, RECT{ gManager->GetGameWidth() / 2 - 150, 250, gManager->GetGameWidth() / 2 + 150, 280 }, 26, 800, 0xff0015ff, 1);
		gManager->DrawTextMessage(hfont, welcomeMessage4, RECT{ gManager->GetGameWidth() / 2 - 300, 350, gManager->GetGameWidth() / 2 + 300, 380 }, 0xffffffff, 1);
	}
}
