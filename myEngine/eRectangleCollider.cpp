#include "eRectangleCollider.h"
#include "Director.h"
#include "myMath.h"
#include "CollisionManager.h"

namespace Engine
{
	eRectangleCollider::eRectangleCollider(Vec2 dmin, Vec2 dmax, Vec2 & currentPosition, unsigned long cColor)
		: eCollider(currentPosition, cColor), dMin(dmin), dMax(dmax), dB(dmax.X, dmin.Y), dD(dmin.X, dMax.Y)
	{
	}

	void eRectangleCollider::Draw()
	{
		if (!showCollider)
			return;

		auto graphicsManager = Engine::Director::getInstance()->GetGraphicsManager();

		// draw collider rect
		graphicsManager->DrawLine(Min.X, Min.Y, B.X, B.Y, 3, false, color);
		graphicsManager->DrawLine(B.X, B.Y, Max.X, Max.Y, 3, false, color);
		graphicsManager->DrawLine(Max.X, Max.Y, D.X, D.Y, 3, false, color);
		graphicsManager->DrawLine(D.X, D.Y, Min.X, Min.Y, 3, false, color);
	}

	void eRectangleCollider::Update(float angle)
	{
		// Setting current bounding box points 
		Min = PerentPosition + Engine::RotatePoint(dMin, -angle);
		B = PerentPosition + Engine::RotatePoint(dB, -angle);
		Max = PerentPosition + Engine::RotatePoint(dMax, -angle);
		D = PerentPosition + Engine::RotatePoint(dD, -angle);

		// Update angle
		this->angle = angle;
		boxCenter = PerentPosition;
	}

	bool eRectangleCollider::Collides(eCollider * col)
	{
		return col->Collides(this);
	}

	bool eRectangleCollider::Collides(eRectangleCollider * col)
	{
		CollisionManager manager;
		return manager.isCollide(this, col);
	}

	bool eRectangleCollider::Collides(eCircleCollider * col)
	{
		CollisionManager manager;
		return manager.isCollide(this, col);
	}

	bool eRectangleCollider::Collides(ePolygonCollider * col)
	{
		CollisionManager manager;
		return manager.isCollide(col, this);
	}
}
