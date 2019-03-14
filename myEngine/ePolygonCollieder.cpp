#include "ePolygonCollider.h"
#include "Director.h"
#include "myMath.h"
#include "CollisionManager.h"

namespace Engine
{
	ePolygonCollider::ePolygonCollider(std::vector<Vec2> _points, float _radius, Vec2 & currentPosition, unsigned long bColor, unsigned long cColor)
		: eCollider(currentPosition), points(_points), radius(_radius)
	{
	}

	ePolygonCollider::~ePolygonCollider()
	{
	}

	void ePolygonCollider::Draw()
	{
		if (!showCollider)
			return;

		auto graphicsManager = Engine::Director::getInstance()->GetGraphicsManager();
		
		// draw collider rect
		unsigned int i = 0;
		for (; i < points.size()-1; ++i)
		{
			Vec2 point1 = Engine::RotatePoint(points[i], -angle) + polygonCenter;
			Vec2 point2 = Engine::RotatePoint(points[i+1], -angle) + polygonCenter;
			graphicsManager->DrawLine(point1.X, point1.Y, point2.X, point2.Y, 2, false, color);
		}

		Vec2 point1 = Engine::RotatePoint(points[i], -angle) + polygonCenter;
		Vec2 point2 = Engine::RotatePoint(points[0], -angle) + polygonCenter;

		graphicsManager->DrawLine(point1.X, point1.Y, point2.X, point2.Y, 2, false, color);
	}

	void ePolygonCollider::Update(float angle)
	{
		this->angle = angle;
		polygonCenter = PerentPosition;
	}
	bool ePolygonCollider::Collides(eCollider * col)
	{
		return col->Collides(this);
	}
	bool ePolygonCollider::Collides(eRectangleCollider * col)
	{
		CollisionManager manager;
		return manager.isCollide(this, col);
	}
	bool ePolygonCollider::Collides(eCircleCollider * col)
	{
		CollisionManager manager;
		return manager.isCollide(this, col);
	}
	bool ePolygonCollider::Collides(ePolygonCollider * col)
	{
		return false;
	}
}

