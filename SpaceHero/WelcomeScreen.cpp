#include "WelcomeScreen.h"
#include "Director.h"
#include "StartButton.h"
#include "Constants.h"
#include "SpaceObject.h"

WelcomeScreen::WelcomeScreen(GameData* data) : gData(data)
{
}

WelcomeScreen::~WelcomeScreen()
{
}

void WelcomeScreen::Init()
{
	auto director = Engine::Director::getInstance();

	Engine::eImage* image = director->GetResourceManager()->GetImage(startbuttonID);
	StartButton* button = new StartButton(image, nullptr, nullptr, 2);
	button->gData = gData;
	button->Init();
	AddGameObject(button);

	image = director->GetResourceManager()->GetImage(gameLogoID);
	Engine::eGameObject* background = new SpaceObject(image, 0);
	background->SetAnchorPoint({ 0.5f, 0.5f });
	background->SetObjectSize(600, 400);
	background->GetPosition().X = director->GetGraphicsManager()->GetGameWidth() * 0.5f;
	background->GetPosition().Y = director->GetGraphicsManager()->GetGameHeight() * 0.5f;
	AddGameObject(background);
}
