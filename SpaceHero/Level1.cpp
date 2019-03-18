#include "Level1.h"
#include "Director.h"
#include "Player.h"
#include "Constants.h"
#include "HUD.h"
#include "Asteroid.h"

Level1::Level1(GameData* data) : gData(data) { }

Level1::~Level1() { }

void Level1::Init()
{
	gData->WelcomeMessageShow = true;
	auto director = Engine::Director::getInstance();

	// Explosion image
	Engine::eImage* explosionImage = director->GetResourceManager()->GetImage(explosionID);

	// player sprite with explosion
	Engine::eImage*image = director->GetResourceManager()->GetImage(playerID);
	Engine::eGameObject* object = new Player(image, explosionImage, 3, gData);
	object->Init();
	AddGameObject(object);

	object = new HUD(gData);
	object->Init();
	AddGameObject(object);

	// Make game harder
	Asteroid::SetSpawnInterval(1.2f - (float)gData->GetLevelNumber() / 10.0f);
}
