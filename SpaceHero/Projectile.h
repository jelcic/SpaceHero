#pragma once
#include "SpaceObject.h"


class Projectile : public SpaceObject
{
public:
	Projectile(Engine::eImage* mImage, Engine::Vec2 startPosition, float angle, int Zorder);

	// Object reaction on collision
	virtual void Collision(eGameObject* secondObject) override;
	// When collides as second object
	virtual void GetHitWith(int oId) override;

	// Spawning functionality
	static Projectile* Spawning(Projectile * projectileForReset, Engine::Vec2 startPosition, float angle);
	static void ResetProjectileObject(Projectile * projectileForReset, Engine::Vec2 startPosition, float angle);
	
	const float Speed{ 500.0f };
	const float imageSize{ 40.0f };
private:
	// MAIN GAME FUNCTIONS
	virtual void init() override;
	virtual void update(float dt) override;
	virtual void draw() override;
};