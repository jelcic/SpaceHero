#pragma once
#include "eCollider.h"
#include <vector>

namespace Engine
{
	class ePolygonCollider: public eCollider
	{
	public:
		ePolygonCollider(std::vector<Vec2> _points, float _radius, Vec2 & currentPosition, unsigned long bColor = 0xffffffff, unsigned long cColor = 0xffff0c0c);
		~ePolygonCollider();

		// Draw on the screen
		virtual void Draw() override;

		// Update to perent object position
		virtual void Update(float angle) override;
	
		std::vector<Vec2> points;
		float radius{};
		float angle{};
		Vec2 polygonCenter{};

		//Check collision with other collider
		virtual bool Collides(eCollider* col) override;

		virtual bool Collides(eRectangleCollider* col) override;
		virtual bool Collides(eCircleCollider* col) override;
		virtual bool Collides(ePolygonCollider* col) override;
	private:
		ePolygonCollider();
	};
}
