#include "SpaceObject.h"
#include "MyMath.h"

SpaceObject::SpaceObject(Engine::eImage * mImage, Engine::eImage * _explosionImage, int Zorder, GameData* data)
	: eGameObject(Zorder), mainImage(mImage), explosionImage(_explosionImage), gData(data) { }

SpaceObject::SpaceObject(Engine::eImage * mImage, int Zorder, GameData* data)
	: Engine::eGameObject(Zorder), mainImage(mImage), gData(data) { }

SpaceObject::SpaceObject(int Zorder, GameData* data)
	: Engine::eGameObject(Zorder), gData(data) { }

SpaceObject::~SpaceObject() { }

void SpaceObject::update(float dt) { }

void SpaceObject::draw()
{
	mainImage->Draw(nullptr, Position, objectSize, rotationCenter, AnchorPoint, Angle, scale);
}

void SpaceObject::init() { }

void SpaceObject::GetHitWith(std::string oName) { }

void SpaceObject::Collision(eGameObject * secondObject) { }

void SpaceObject::ResolveCollision(SpaceObject * secondObject, float speedCoef, float minSpeed)
{
	Engine::Vec2 secPosition = secondObject->GetPosition();
	float distance = Engine::GetDistance(Position, secPosition);

	float nx = (secPosition.X - Position.X) / distance;
	float ny = (secPosition.Y - Position.Y) / distance;

	float kx = (Velocity.X - secondObject->Velocity.X);
	float ky = (Velocity.Y - secondObject->Velocity.Y);
	float p = 2.0f * (nx * kx + ny * ky);
	Velocity.X = (Velocity.X - p * nx);
	Velocity.Y = (Velocity.Y - p *ny);
	secondObject->Velocity.X = (secondObject->Velocity.X + p * nx);
	secondObject->Velocity.Y = (secondObject->Velocity.Y + p * ny);

	if (abs(Velocity.Y) > minSpeed)
		Velocity *= speedCoef;

	if (abs(secondObject->Velocity.Y) > minSpeed)
		secondObject->Velocity *= speedCoef;
}

Engine::Size SpaceObject::GetImageSize()
{
	return Engine::Size(mainImage->textureSize.Width, mainImage->textureSize.Height);
}
