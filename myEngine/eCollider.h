#pragma once

#include "eTypes.h"

namespace Engine
{
	class eRectangleCollider;
	class eCircleCollider;
	class ePolygonCollider;

	class eCollider
	{
	public:
		// Colors to draw collider in base state and collision state
		eCollider(Vec2 & position, unsigned long cColor = 0xffff0c0c);
		virtual ~eCollider();

		// Draw on the screen
		virtual void Draw() = 0;

		// Update base to perent object position
		virtual void Update(float angle) = 0;

		//Check collision with other collider
		virtual bool Collides(eCollider* col) = 0;
		//Check collision with other collider
		virtual bool Collides(eRectangleCollider* col) = 0;
		virtual bool Collides(eCircleCollider* col) = 0;
		virtual bool Collides(ePolygonCollider* col) = 0;

		// Set to see collier on the screen
		void ShowCollider(bool show);

		// Set parent position callback
		Vec2 & PerentPosition;
	protected:
		bool showCollider{ false };

		// Color for drawing collider on the screen
		unsigned long color{};


	};
}