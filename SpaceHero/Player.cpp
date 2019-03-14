#include "Player.h"
#include "eTypes.h"
#include "ePolygonCollider.h"
#include "Asteroid.h"
#include "Constants.h"
#include "MyMath.h"

Player::Player(Engine::eImage * image, Engine::eImage* _explosionImage, int Zorder, GameData* data)
	: SpaceObject(image, _explosionImage, Zorder, data)
{
}

Player::~Player()
{
}

void Player::ProcessInput()
{
	// Movement input
	bool left = (GetAsyncKeyState(VK_LEFT) & 0x8000) != 0;
	bool right = (GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0;
	bool thrust = (GetAsyncKeyState(VK_UP)) != 0;

	inputThrust = thrust ? 1.f : 0.f;
	inputDirection = (left ? -1.f : 0.f) + (right ? 1.f : 0.f);

	// Fire input
	if ((GetAsyncKeyState(0x44) & 0x8000) != 0)
	{
		if (!wasFire)
			fire = wasFire = true;
	}			
	else
		wasFire = false;
}

void Player::update(float dt)
{
	switch (State)
	{
	case PlayerState::active:
	{
		// If player left the screen
		if (IsPositionOutOfScreen(Position, 0.0f))
			Explode();
		
		// Get input from user
		ProcessInput();
		
		// Check user input and ship fuel
		if (inputThrust && gData->GetPlayerFuel() > 0)
		{
			UpdateVelocity(dt);
			ShipEngineOn(dt);
		}
		else
			ShipEngineOff();

		UpdateAngleAndPosition(dt);
		DecreaseShipFuel(dt);
		HitRecovering(dt);
	} break;
	case PlayerState::crashed:
		PlayerCrashed(dt);
		break;
	case PlayerState::invulnerable:
		WaitingForStart();
		break;
	}
}

void Player::draw()
{
	if (State == PlayerState::active
		|| State == PlayerState::invulnerable
		|| State == PlayerState::pause)
	{
		mainImage->Draw(nullptr, Position, objectSize, rotationCenter, AnchorPoint, Angle, scale);
	}
	else if (State == PlayerState::crashed)
	{
		explosionImage->Draw(nullptr, Position, objectSize, rotationCenter, AnchorPoint, Angle, explosionScale);
	}
}

void Player::angleUpdate(float dt)
{
	Angle += rotation * dt;
	float fullCircle = 2 * Engine::PI;
	if (Angle > fullCircle)
		Angle -= fullCircle;
	if (Angle < -fullCircle)
		Angle += fullCircle;
}

void Player::WaitingForStart()
{
	ProcessInput();

	if (!inputThrust)
		return;

	// activating ship
	State = PlayerState::active;
	collide = true;
	gData->WelcomeMessageShow = false;
}

void Player::PlayerCrashed(float dt)
{
	if (explosionTimer < explosionInterval)
	{
		// Explosion animation
		explosionTimer += dt;
		explosionScale += 0.005f;
	}
	else
	{
		explosionTimer = 0.0f;

		if (gData->GetPlayerLives() > 0)
		{
			State = PlayerState::reset;
			collide = true;
		}
		else
			State = PlayerState::dead;
	}
}

void Player::HitRecovering(float dt)
{
	if (collide == false)
		recoveringTimer += dt;
	if (recoveringTimer > recoveringInterval)
	{
		collide = true;
	}
}

void Player::DecreaseShipFuel(float dt)
{
	fuelInterval += dt;
	if (fuelInterval > decreaseFuelInterval)
	{
		gData->DecreaseFuel(2);
		fuelInterval = 0.0f;
	}
}

void Player::UpdateAngleAndPosition(float dt)
{
	rotation += inputDirection * dt * ROTATION_RATE;
	angleUpdate(dt);
	Velocity.Y -= GravityCoef;
	Position += Velocity * dt;
}

void Player::UpdateVelocity(float dt)
{
	Velocity.X += (float)sin(Angle) * speed * dt;
	Velocity.Y += (float)cos(Angle) * speed * dt;
}

void Player::ShipEngineOn(float dt)
{
	frameFrequency -= dt;
	if (frameFrequency <= 0 && frameNumber < 5)
	{
		frameNumber++;
		*(mainImage->DrawRect) = { frameNumber * objectSize.Width, objectSize.Height, (frameNumber + 1) * objectSize.Width, 0 };
		frameFrequency = 0.1f;
	}
}

void Player::ShipEngineOff()
{
	frameNumber = 0;
	*(mainImage->DrawRect) = { frameNumber * objectSize.Width, objectSize.Height, (frameNumber + 1) * objectSize.Width, 0 };	
}

void Player::init()
{
	auto gManager = Engine::Director::getInstance()->GetGraphicsManager();
	Position = Engine::Vec2(gManager->GetGameWidth() / 2.0f, 60.0f);
	AnchorPoint = Engine::Vec2(0.5f, 0.5f);
	objectSize.Width = 60;
	objectSize.Height = 150;
	rotationCenter = Engine::Vec2(objectSize.Width * 0.5f, (-objectSize.Height) * 0.5f);
	name = playerID;
	ShipEngineOff();

	std::vector<Engine::Vec2> colliderPoints{ Engine::Vec2(-30, -45.0f), Engine::Vec2(-15.0f, -30.0f), Engine::Vec2(0.0f, -45.0f), Engine::Vec2(15.0f, -30.0f), Engine::Vec2(30.0f, -45.0f),
		Engine::Vec2(30.0f, -10.0f), Engine::Vec2(20.0f, 0.0f), Engine::Vec2(20.0f, 20.0f), Engine::Vec2(20.0f, 40.0f), Engine::Vec2(10.0f, 60.0f),
		Engine::Vec2(0.0f, 70.0f), Engine::Vec2(-10.0f, 60.0f), Engine::Vec2(-20.0f, 40.0f), Engine::Vec2(-20.0f, 20.0f), Engine::Vec2(-20.0f, 0.0f),
		Engine::Vec2(-30.0f, -10.0f) };

	AddCollider(new Engine::ePolygonCollider(colliderPoints, 75.0f, Position));
	collide = false;
	notCollidingWith.push_back(projectileID);
}

void Player::Collision(eGameObject * secondObject)
{
	if (secondObject->name != asteroidID)
		return;

	SpaceObject* object = dynamic_cast<SpaceObject*>(secondObject);
	ResolveCollision(object, 0.2f, 20.0f);
	object->GetHitWith(name);
	GetHitWith(asteroidID);
	return;
}

void Player::ResolveCollision(SpaceObject * secondObject, float speedCoef, float minSpeed)
{
	SpaceObject::ResolveCollision(secondObject, speedCoef, minSpeed);
	rotation *= -0.5f;
}

void Player::GetHitWith(std::string oName)
{
	gData->DecreaseEnergy(30);
	if (gData->GetPlayerEnergy() <= 0)
		Explode();
	else
	{
		recoveringTimer = 0.0f;
		collide = false;
	}
		
}

void Player::Explode()
{
	State = PlayerState::crashed;
	explosionTimer = 0.0f;
	explosionScale = 0.6f;
	Angle = 0.0f;
	collide = false;
	gData->DecreaseLives();
}
