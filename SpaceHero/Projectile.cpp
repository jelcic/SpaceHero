#include "Projectile.h"
#include "eCircleCollider.h"
#include "Director.h"
#include "Constants.h"
#include "myMath.h"

Projectile::Projectile(Engine::eImage* mImage, Engine::Vec2 startPosition, float angle, int Zorder) : SpaceObject(mImage, Zorder)
{
	Position = startPosition;
	Angle = angle;
	name = projectileID;
	Velocity.X = (float)sin(Angle) * Speed;
	Velocity.Y = (float)cos(Angle) * Speed;
	SetObjectSize((int)imageSize, (int)imageSize);
	SetAnchorPoint(Engine::Vec2(0.5f, 0.5f));
	SetRotationCenter(imageSize*0.5f, -imageSize*0.5f);
	AddCollider(new Engine::eCircleCollider(Engine::Vec2(0.0f, 10.0f), Position, 10.0f));
	notCollidingWith.push_back(playerID);
}

void Projectile::Collision(eGameObject * secondObject)
{
	SpaceObject* object = dynamic_cast<SpaceObject*>(secondObject);

	if (object)
	{
		GetHitWith("");
		object->GetHitWith(name);
	}
}

void Projectile::GetHitWith(std::string oName)
{
	active = false;
	collide = false;
}

Projectile * Projectile::Spawning(Projectile * projectileForReset, Engine::Vec2 startPosition, float angle)
{
	if (!projectileForReset)
	{
		auto resource = Engine::Director::getInstance()->GetResourceManager();
		projectileForReset = new Projectile(resource->GetImage(projectileID), startPosition, angle, 2);
		return projectileForReset;
	}		

	ResetProjectileObject(projectileForReset, startPosition, angle);
	return nullptr;
}

void Projectile::ResetProjectileObject(Projectile * projectileForReset, Engine::Vec2 startPosition, float angle)
{
	projectileForReset->Position = startPosition;
	projectileForReset->Angle = angle;
	projectileForReset->Velocity.X = (float)sin(angle) * projectileForReset->Speed;
	projectileForReset->Velocity.Y = (float)cos(angle) * projectileForReset->Speed;
	projectileForReset->active = true;
	projectileForReset->collide = true;
}

void Projectile::init()
{
}

void Projectile::update(float dt)
{
	// Update position
	Position += Velocity * dt;

	// Make projectile inactive if it is out of the screen
	if (Engine::IsPositionOutOfScreen(Position, 10.0f))
	{
		active = false;
		collide = false;
	}
		
}

void Projectile::draw()
{
	mainImage->Draw(nullptr, Position, objectSize, rotationCenter, AnchorPoint, Angle, scale);
}
