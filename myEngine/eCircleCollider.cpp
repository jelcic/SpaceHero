#include "eCircleCollider.h"
#include "Director.h"
#include "CollisionManager.h"

namespace Engine
{
	eCircleCollider::eCircleCollider(Vec2 centerPoint, Vec2& currentPosition, float rad, unsigned long cColor)
		: eCollider(currentPosition, cColor), deltaCenterPoint(centerPoint), radius(rad), CenterPoint(currentPosition)
	{
	}

	void eCircleCollider::Draw()
	{
		if (!showCollider)
			return;

		auto graphicsManager = Engine::Director::getInstance()->GetGraphicsManager();
		graphicsManager->DrawCircle(CenterPoint.X, CenterPoint.Y, radius, 0.5f, color);
	}

	void eCircleCollider::Update(float angle)
	{
		CenterPoint = PerentPosition + deltaCenterPoint;
	}

	bool eCircleCollider::Collides(eCollider * col)
	{
		return col->Collides(this);
	}

	bool eCircleCollider::Collides(eRectangleCollider * col)
	{
		CollisionManager manager;
		return manager.isCollide(col, this);
	}

	bool eCircleCollider::Collides(eCircleCollider * col)
	{
		CollisionManager manager;
		return manager.isCollide(this, col);
	}

	bool eCircleCollider::Collides(ePolygonCollider * col)
	{
		CollisionManager manager;
		return manager.isCollide(col, this);
	}
}

