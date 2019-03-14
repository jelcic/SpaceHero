#include "CollisionManager.h"
#include "myMath.h"
#include <algorithm>

namespace Engine
{
	void CollisionManager::Check(std::vector<eGameObject*> objectList)
	{
		for (unsigned int i = 0; i < objectList.size(); ++i)
		{
			if (!objectList[i]->active || !objectList[i]->collide)
				continue;

			for (unsigned int j = i + 1; j < objectList.size(); ++j)
			{
				const std::vector<std::string> v1 = objectList[i]->notCollidingWith;
				const std::vector<std::string> v2 = objectList[j]->notCollidingWith;

				if (!objectList[j]->active || !objectList[j]->collide
					|| std::find(v1.begin(), v1.end(), objectList[j]->name) != v1.end()
					|| std::find(v2.begin(), v2.end(), objectList[j]->name) != v2.end())
					continue;

				if (CheckColliding(objectList[i], objectList[j]))
					objectList[i]->Collision(objectList[j]);
			}
		}
	}

	bool CollisionManager::isCollide(eCircleCollider * c1, eCircleCollider * c2)
	{
		float distance = Engine::GetDistance(c1->CenterPoint, c2->CenterPoint);

		if (distance < c1->radius + c2->radius)
		{
			ResolveCollisionCircleVsCircle(c1, c2);
			return true;
		}			
		return false;
	}

	bool CollisionManager::isCollide(eRectangleCollider* b, eCircleCollider * c)
	{
		bool collision = false;

		// If the rectangle does not rotate this would be circle position
		Vec2 unrotatedCircle = Engine::RotatePoint(c->CenterPoint - b->boxCenter, b->angle);

		// Get difference vector between both centers
		Vec2 difference = c->CenterPoint - b->boxCenter;

		// Add clamped value to AABB_center and we get the value of box closest to circle
		float clampedX = Clamp(difference.X, -(b->dMax.X - b->dMin.X) / 2, (b->dMax.X - b->dMin.X) / 2);
		float clampedY = Clamp(difference.Y, -(b->dMax.Y - b->dMin.Y) / 2, (b->dMax.Y - b->dMin.Y) / 2);
		Vec2 closest = b->boxCenter + Vec2(clampedX, clampedY);

		// Retrieve vector between center circle and closest point AABB and check if length <= radius
		difference = closest - c->CenterPoint;

		// Determine collision
		collision = vectorLength(difference) < c->radius;

		ResolveCollisionPointVsCircle(c, closest);

		return collision;
	}

	bool CollisionManager::isCollide(eRectangleCollider * b1, eRectangleCollider * b2)
	{
		bool test = (b1->Max.X < b2->Min.X) || (b2->Max.X < b1->Min.X)
			|| (b1->Max.Y < b2->Min.Y) || (b2->Max.Y < b1->Min.Y);

		return !test;
	}

	bool CollisionManager::isCollide(ePolygonCollider * p, eRectangleCollider * b)
	{
		return false;
	}

	bool CollisionManager::isCollide(ePolygonCollider * p, eCircleCollider * c)
	{
		// first check
		float distance = Engine::GetDistance(p->polygonCenter, c->CenterPoint);

		if (distance > p->radius + c->radius)
			return false;

		// main check
		for (unsigned int i = 0; i < p->points.size(); ++i)
		{
			Vec2 point = Engine::RotatePoint(p->points[i], -p->angle) + p->polygonCenter;

			if (Engine::GetDistance(point, c->CenterPoint) <= c->radius)
			{
				ResolveCollisionPointVsCircle(c, point);
				return true;
			}
		}
		return false;
	}

	void CollisionManager::ResolveCollisionPointVsCircle(eCircleCollider * col, Vec2 point)
	{
		float distance = GetDistance(col->CenterPoint, point);
		float delta = distance - col->radius;
		col->CenterPoint.X += delta  * (point.X - col->CenterPoint.X) / distance;
		col->CenterPoint.Y += delta  * (point.Y - col->CenterPoint.Y) / distance;
		
		// Set parent object new position
		col->PerentPosition = col->CenterPoint;
	}

	void CollisionManager::ResolveCollisionCircleVsCircle(eCircleCollider * col1, eCircleCollider * col2)
	{
		float distance = GetDistance(col1->CenterPoint, col2->CenterPoint);
		float delta = (distance - col1->radius - col2->radius) * 0.5f;
		col1->CenterPoint.X -= delta * (col1->CenterPoint.X - col2->CenterPoint.X) / distance;
		col1->CenterPoint.Y -= delta * (col1->CenterPoint.Y - col2->CenterPoint.Y) / distance;
		col2->CenterPoint.X += delta * (col1->CenterPoint.X - col2->CenterPoint.X) / distance;
		col2->CenterPoint.Y += delta * (col1->CenterPoint.Y - col2->CenterPoint.Y) / distance;

		// Set parent objects new positions
		col1->PerentPosition = col1->CenterPoint;
		col2->PerentPosition = col2->CenterPoint;
	}

	void CollisionManager::ResolveCollisionBoxVsBox(eRectangleCollider * col1, eRectangleCollider * col2)
	{
	}

	bool CollisionManager::CheckColliding(eGameObject* object1, eGameObject* object2)
	{
		eCollider* collider1 = object1->GetCollider();
		eCollider* collider2 = object2->GetCollider();

		return collider1->Collides(collider2);
	}
}