#include "Asteroid.h"
#include "Director.h"
#include "myMath.h"
#include "Constants.h"
#include "eCircleCollider.h"

float Asteroid::spawnInterval{};
float Asteroid::spawnTimer{};

Asteroid::Asteroid(Engine::eImage * image, Engine::eImage* _explosionImage, int Zorder, GameData* data)
	: SpaceObject(image, _explosionImage, Zorder, data) { }

Asteroid::~Asteroid() { }

void Asteroid::update(float dt)
{
	// Make asteroid inactive if it is out of the screen
	if (Position.Y < -64.0f && active == true)
	{
		active = false;
		collide = false;
		return;
	}

	if (State == AsteroidState::Active)
	{
		Velocity.Y -= 0.5f;
		Position += Velocity * dt;
		Angle += angleIncrement;
	}
	else if (State == AsteroidState::Explosion)
	{
		if (explosionTimer < explosionInterval)
		{
			explosionTimer += dt;
			explosionScale += 0.005f;
		}
		else
		{
			explosionTimer = 0.0f;
			active = false;
		}
	}
}

void Asteroid::draw()
{
	if (State == AsteroidState::Active)
		mainImage->Draw(imageRect, Position, objectSize, rotationCenter, AnchorPoint, Angle, scale);
	else if (State == AsteroidState::Explosion)
		explosionImage->Draw(nullptr, Position, objectSize, rotationCenter, AnchorPoint, Angle, explosionScale);
}

Engine::eGameObject* Asteroid::Spawning(Engine::eGameObject* object, GameData* data)
{
	auto director = Engine::Director::getInstance();
	spawnTimer += director->GetTimeManager()->ElapsedGameTime;

	if (spawnTimer > spawnInterval)
	{
		spawnTimer -= spawnInterval;

		if (object == nullptr)
		{
			auto resourceManager = director->GetResourceManager();
			object = new Asteroid(resourceManager->GetImage(asteroidID),
				resourceManager->GetImage(explosionID), 2, data);
			object->Init();
			return object;
		}
		else
			object->Init();
	}
	return nullptr;
}

void Asteroid::SetSpawnInterval(float interval)
{
	spawnInterval = interval;
}

void Asteroid::ResetObject(Engine::Vec2 position, RECT newImageRect)
{
	Position = position;
	*imageRect = newImageRect;
	State = AsteroidState::Active;
	active = true;
}

void Asteroid::init()
{
	auto director = Engine::Director::getInstance();

	// Generate random x position of sprite on spritesheet 
	int x{ Engine::RandomInt(0, 5) };
	// Generate random y position of sprite on spritesheet 
	int y{ Engine::RandomInt(0, 3) };

	const int spriteSize{ 128 };

	// Generate random X screen position of sprite 
	int posX = Engine::RandomInt(0, director->GetGraphicsManager()->GetGameWidth() - 60);
	Position = Engine::Vec2{ (float)(posX), (float)(director->GetGraphicsManager()->GetGameWidth() + 1.5f * spriteSize) };

	// Set new image RECT based on new random x and y
	if (imageRect == nullptr)
		imageRect = new RECT;
	*imageRect = RECT{ x * spriteSize, y * spriteSize, (x + 1) * spriteSize, (y + 1) * spriteSize };

	// Set object properties
	objectSize = { spriteSize , -spriteSize };
	rotationCenter = Engine::Vec2{ spriteSize* 0.5f, spriteSize * 0.5f };
	angleIncrement = Engine::RandomSign() * 0.05f + y / 100;
	Velocity = Engine::Vec2{ Engine::RandomSign() * x * 10.0f, -90.0f + (float)y * 10.0f };
	AnchorPoint = Engine::Vec2(0.5f, 0.5f);
	active = true;
	State = AsteroidState::Active;
	id = asteroidID;

	// Set mass based on object size
	if (y == 2)
		Mass = xlAsteroidMass;
	else if (y == 1)
		Mass = mAsteroidMass;
	else if (y == 0)
		Mass = sAsteroidMass;

	LifeEnergy = Mass * 2.0f;
	AddCollider(new Engine::eCircleCollider(Engine::Vec2(0.0f, 0.0f), Position, Mass));
}

void Asteroid::Collision(eGameObject* secondObject)
{
	SpaceObject* object = dynamic_cast<SpaceObject*>(secondObject);

	if (!object)
		return;

	if (object->id != projectileID)
		ResolveCollision(object, 0.2f, 5.0f);
	else
		ResolveCollision(object, 0.02f, 5.0f);

	GetHitWith(object->id);
	object->GetHitWith(id);
}

void Asteroid::GetHitWith(int oId)
{
	if (projectileID == oId)
		LifeEnergy -= 30.0f;

	if (LifeEnergy <= 0 || 
		Mass == sAsteroidMass && oId == playerID)
		Explode();
}

void Asteroid::Explode()
{
	State = AsteroidState::Explosion;
	explosionTimer = 0.0f;
	explosionScale = 0.3f;
	Angle = 0.0f;
	collide = false;
	objectSize.Height *= -1;

	// Add score
	gData->IncreaseScore(Mass);
}