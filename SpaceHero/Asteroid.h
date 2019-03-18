#pragma once

#include "SpaceObject.h"

class Asteroid : public SpaceObject
{
public:
	Asteroid(Engine::eImage* image, Engine::eImage* explosionImage, int Zorder, GameData* data);
	~Asteroid();

	enum class AsteroidState { Active, Explosion, Invulnerable, Reset }
	State{ AsteroidState::Active };

	// Object reaction on collision
	void Collision(eGameObject * secondObject);
	// When collides as second object
	virtual void GetHitWith(int oId) override;

	// Spawning functionality
	static eGameObject* Spawning(Engine::eGameObject* object, GameData* data);
	static void SetSpawnInterval(float interval);
	void ResetObject(Engine::Vec2 position, RECT newImageRect);

	//Asteroid explosion
	void Explode();

	// Asteroid energy
	float LifeEnergy{};

	// define area of sprite sheet
	RECT* imageRect{};
private:
	// Spawning properties
	static float spawnTimer;
	static float spawnInterval;
	float angleIncrement{};

	// MAIN GAME FUNCTIONS
	virtual void update(float dt) override;
	virtual void draw() override;
	virtual void init() override;
	
	// Block constructor
	Asteroid();
};
