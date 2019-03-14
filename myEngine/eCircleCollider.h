#pragma once
#include "eCollider.h"
#include "eTypes.h"

namespace Engine
{
	class eCircleCollider : public eCollider
	{
	public:
		// Collider center, radius and color to draw collider
		eCircleCollider::eCircleCollider(Vec2 centerPoint, Vec2 & currentPosition, float rad, unsigned long cColor = 0xffff0c0c);

		// Current collider center position
		Vec2 CenterPoint{};

		// Collider center position relative to object anchor point  
		Vec2 deltaCenterPoint{};
		
		// Collider circle radius
		float radius{};

		// Draw on the screen
		virtual void Draw() override;

		// Update base to perent object position
		virtual void Update(float angle = 0.0f) override;

		//Check collision with other collider
		virtual bool Collides(eCollider* col) override;

		virtual bool Collides(eRectangleCollider* col) override;
		virtual bool Collides(eCircleCollider* col) override;
		virtual bool Collides(ePolygonCollider* col) override;
	};
}