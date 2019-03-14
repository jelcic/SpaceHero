#pragma once
#include "eCollider.h"
#include "eTypes.h"

namespace Engine
{
	class eRectangleCollider : public eCollider
	{
	public:
		// Pass bottom left and top right point and colors to draw collider
		eRectangleCollider(Vec2 dMin, Vec2 dMax, Vec2& currentPosition, unsigned long cColor = 0xffff0c0c);
		
		// Draw on the screen
		virtual void Draw() override;

		// Update base to perent object position
		virtual void Update(float angle = 0.0f) override;

		// Starting collider points
		Vec2 dMin;
		Vec2 dMax;
		Vec2 dB;
		Vec2 dD;

		// Current collider points
		Vec2 Min;
		Vec2 Max;
		Vec2 B;
		Vec2 D;

		//if bounding box rotating this is current angle
		float angle{};
		// Box center
		Vec2 boxCenter{};

		//Check collision with other collider
		virtual bool Collides(eCollider* col) override;

		virtual bool Collides(eRectangleCollider* col) override;
		virtual bool Collides(eCircleCollider* col) override;
		virtual bool Collides(ePolygonCollider* col) override;
	};
}