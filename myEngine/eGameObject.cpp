#include "eGameObject.h"
#include "Director.h"

namespace Engine
{
	eGameObject::eGameObject(int Zorder)
		: zOrder(Zorder)	{}

	eGameObject::~eGameObject() {	}

	void eGameObject::Init()
	{
		init();
	}

	void eGameObject::Update(float dt)
	{
		update(dt);

		if (collider)
			collider->Update(Angle);
	}

	void eGameObject::Draw()
	{
		draw();

		if (collider)
			collider->Draw();
	}

	void eGameObject::SetAnchorPoint(Vec2 anchorPoint)
	{
		AnchorPoint = anchorPoint;
	}

	void eGameObject::SetGameObjectScale(float scale)
	{
		this->scale = scale;
	}

	void eGameObject::SetRotationCenter(float x, float y)
	{
		rotationCenter.X = x;
		rotationCenter.Y = y;
	}

	void eGameObject::AddCollider(Engine::eCollider * _collider)
	{
		if (collider)
			delete collider;

		collider = _collider;
		collide = true;
	}

	void eGameObject::DrawCollider(bool draw)
	{
		if(collider)
			collider->ShowCollider(draw);
	}

	Engine::eCollider * eGameObject::GetCollider()
	{
		return collider;
	}

	Size eGameObject::GetObjectSize()
	{
		return objectSize;
	}

	Vec2& eGameObject::GetPosition()
	{
		return Position;
	}

	Vec2 eGameObject::GetRotationCenter()
	{
		return rotationCenter;
	}

	void eGameObject::_setPosition(Vec2 newPosition)
	{
		Position = newPosition;
	}

	void eGameObject::Collision(eGameObject * secondObject) {	}

	void eGameObject::SetObjectSize(int width, int height)
	{
		objectSize.Width = width;
		objectSize.Height = height;
	}

	eGameObject::eGameObject() {}
}