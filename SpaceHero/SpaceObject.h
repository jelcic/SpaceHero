#pragma once
#include "eGameObject.h"
#include "eCollider.h"
#include "GameData.h"

class SpaceObject : public Engine::eGameObject
{
public:
	SpaceObject(Engine::eImage* mImage, Engine::eImage* _explosionImage, int Zorder, GameData* data = nullptr);
	SpaceObject(Engine::eImage * mImage, int Zorder, GameData* data = nullptr);
	SpaceObject(int Zorder, GameData* data = nullptr);

	virtual ~SpaceObject();

	// MOVEMENT
	Engine::Vec2 Velocity{};

	// Object reaction on collision
	virtual void Collision(eGameObject* secondObject) override;
	// Collision effect on movement
	virtual void ResolveCollision(SpaceObject* secondObject, float speedCoef, float minSpeed);
	// When collides as second object
	virtual void GetHitWith(int oId);

	// Main image to drawn on the screen
	Engine::eImage* mainImage;

	// Gat main image size
	Engine::Size SpaceObject::GetImageSize();

	// Explosion image
	Engine::eImage* explosionImage;
	float explosionTimer{};
	const float explosionInterval{ 1.2f };
	float explosionScale{};
	//*********************

	// Persist game data
	GameData* gData;
private:
	// MAIN GAME FUNCTIONS
	virtual void init() override;
	virtual void update(float dt) override;
	virtual void draw() override;
};
