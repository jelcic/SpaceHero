#pragma once

#include <vector>
#include "eGameObject.h"
#include "eCircleCollider.h"
#include "eRectangleCollider.h"
#include "ePolygonCollider.h"

namespace Engine
{
	class CollisionManager
	{
	public:
		void Check(std::vector<eGameObject*> objectList);

		bool isCollide(eCircleCollider * c1, eCircleCollider* c2);
		bool isCollide(eRectangleCollider* b, eCircleCollider * c);
		bool isCollide(eRectangleCollider * b1, eRectangleCollider* b2);
		bool isCollide(ePolygonCollider * p, eRectangleCollider* b);
		bool isCollide(ePolygonCollider * p, eCircleCollider* c);
	private:
		bool CheckColliding(eGameObject* object1, eGameObject* object2);
		void ResolveCollisionPointVsCircle(eCircleCollider * col, Vec2 point);
		void ResolveCollisionCircleVsCircle(eCircleCollider * col1, eCircleCollider * col2);
		void ResolveCollisionBoxVsBox(eRectangleCollider * col1, eRectangleCollider * col2);
	};
}
