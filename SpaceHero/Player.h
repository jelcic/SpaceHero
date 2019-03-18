#pragma once

#include "SpaceObject.h"
#include "myMath.h"
#include "Constants.h"

class Player : public SpaceObject
{
public:
	Player(Engine::eImage* image, Engine::eImage* _explosionImage, int Zorder, GameData* data);
	~Player();

	PlayerState State{ PlayerState::invulnerable };

	// Get input from keyboard
	void ProcessInput();

	// Object reaction on collision
	virtual void Collision(eGameObject* secondObject) override;
	// Collision effect on movement
	void ResolveCollision(SpaceObject* secondObject, float speedCoef, float minSpeed) override;
	// When collides as second object
	virtual void GetHitWith(int oId) override;

	//Ship explosion
	void Explode();

	// Ship fire
	bool fire{ false };
private:
	// MAIN GAME FUNCTIONS
	virtual void init() override;
	virtual void update(float dt) override;
	virtual void draw() override;
	
	// Block constructor
	Player();
	
	// Angle increment
	void angleUpdate(float dt);

	// MOVEMENT
	// Current input thrust value (can be 0 or 1)
	float inputThrust;
	// Current input direction (can be -1, 0 or 1)
	float inputDirection; 
	float rotation;
	const float ROTATION_RATE{ Engine::PI * 0.5f };
	float speed{ 100 };

	// On level start
	bool waitingForStart{ true };

	// Ship fire
	bool wasFire{ false };

	// Hit recovering
	float recoveringInterval{ 1.0f };
	float recoveringTimer{};
	// Engine animation 
	short frameNumber{};
	float frameFrequency{ 0.1f };
	// Ship fuel decrise interval
	float decreaseFuelInterval{ 1.0f };
	float fuelInterval{};

	// Helper methods
	void WaitingForStart();
	void PlayerCrashed(float dt);
	void HitRecovering(float dt);
	void DecreaseShipFuel(float dt);
	void UpdateAngleAndPosition(float dt);
	void UpdateVelocity(float dt);
	void ShipEngineOn(float dt);
	void ShipEngineOff();
};
