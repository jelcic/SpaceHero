#include "SpaceHero.h"
#include "eTypes.h"
#include "Asteroid.h"
#include "Constants.h"
#include "Level1.h"
#include "Projectile.h"
#include "SceneManager.h"
#include "WelcomeScreen.h"


SpaceHero::SpaceHero() { }

SpaceHero::~SpaceHero()
{
	if (gData)
		delete gData;
	gData = nullptr;
}

void SpaceHero::Update()
{
	Engine::eScene* scene = GetCurrentScene();
	Player* player = dynamic_cast<Player*>(scene->GetGameObject(playerID));

	switch (gState)
	{
	case GameState::Run:
	{
		if (!player)
			return;

		// Check if the objective is reached
		if (isObjectiveReached(player))
			return;

		if (player->State == PlayerState::reset)
		{
			// Player crashed
			gState = GameState::ResetLevel;
			return;
		}
		else if (player->State == PlayerState::dead)
		{
			// Player died
			gState = GameState::GameOver;
			gData->GameOverMessageShow = true;
			return;
		}

		// Player fire
		spawnProjectile(scene, player);
		// Asteroid spawning
		spawnAsteroid(scene);
	} break;
	case GameState::LevelComplete:
		if (!player) return;
		levelComplete(player);
		break;
	case GameState::ResetLevel:
		if (!player) return;
		gData->ResetLevel();
		AddScene(SceneManager::GetNewScene(gData->GetLevelNumber(), gData));
		gState = GameState::Run;
		break;
	case GameState::GameOver:
		if (!player) return;
		gameOver();
		break;
	case GameState::MainManu:
		if (gData->GetLevelNumber() > 0)
		{
			AddScene(SceneManager::GetNewScene(gData->GetLevelNumber(), gData));
			gState = GameState::Run;
		}			
		break;
	}
}

void SpaceHero::Init()
{
	// Initialization of persist data
	gData = new GameData;

	auto director = Engine::Director::getInstance();

	// Explosion image
	Engine::eImage* explosionImage = new Engine::eImage("Resources/explosion.png", explosionID, new RECT{ 0, 128, 128, 0 });
	director->GetResourceManager()->AddImage(explosionImage);
	// Projectile image
	Engine::eImage* image = new Engine::eImage("Resources/projectile.png", projectileID, new RECT{ 0, 40, 40, 0 });
	director->GetResourceManager()->AddImage(image);
	// player sprite with explosion
	image = new Engine::eImage("Resources/rocketsheet.png", playerID, new RECT{ 0, 150, 60, 0 });
	director->GetResourceManager()->AddImage(image);
	// asteroid image
	image = new Engine::eImage("Resources/asteroidsheet.png", asteroidID);
	director->GetResourceManager()->AddImage(image);
	// start button image
	image = new Engine::eImage("Resources/buttonsheet.png", startbuttonID, new RECT{ 0, 64, 151, 0 });
	director->GetResourceManager()->AddImage(image);
	// main menu background image 
	image = new Engine::eImage("Resources/GameLogo.jpg", gameLogoID, new RECT{ 0, 400, 600, 0 });
	director->GetResourceManager()->AddImage(image);

	AddScene(SceneManager::GetNewScene(gData->GetLevelNumber(), gData));
}

// HELPER METHODS ****************************************

bool SpaceHero::isObjectiveReached(Player* player)
{
	if (gData->GetPlayerScore() >= SceneManager::GetSceneMaxScore(gData->GetLevelNumber()))
	{
		gState = GameState::LevelComplete;
		gData->CompleteMessageShow = true;
		player->State = PlayerState::pause;
		player->collide = false;
		return true;
	}
	return false;
}

void SpaceHero::spawnProjectile(Engine::eScene* scene, Player* player)
{
	if (!player->fire)
		return;

	Projectile* projectile = dynamic_cast<Projectile*>(scene->GetGameObject(projectileID, false));
	scene->AddGameObject(Projectile::Spawning(projectile, player->GetPosition(), player->Angle));
	player->fire = false;
}

void SpaceHero::spawnAsteroid(Engine::eScene * scene)
{
	Engine::eGameObject* asteroidForReset = scene->GetGameObject(asteroidID, false);
	scene->AddGameObject(Asteroid::Spawning(asteroidForReset, gData));
}

void SpaceHero::levelComplete(Player * player)
{
	float dt = Engine::Director::getInstance()->GetTimeManager()->ElapsedGameTime;

	displaymessageTimer += dt;
	if (displaymessageTimer > displayMessageInterval)
	{
		gData->NewLevelReset();
		AddScene(SceneManager::GetNewScene(gData->GetLevelNumber(), gData));
		gState = GameState::Run;
		player->State = PlayerState::invulnerable;
		player->collide = false;
		displaymessageTimer = 0.0f;
	}
}

void SpaceHero::gameOver()
{
	float dt = Engine::Director::getInstance()->GetTimeManager()->ElapsedGameTime;

	displaymessageTimer += dt;
	if (displaymessageTimer > displayMessageInterval)
	{
		gData->ResetGameData();
		AddScene(SceneManager::GetNewScene(gData->GetLevelNumber(), gData));
		gState = GameState::MainManu;
		displaymessageTimer = 0.0f;
	}
}
