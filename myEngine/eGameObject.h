#pragma once
#include <string>
#include <vector>
#include "eTypes.h"
#include "eImage.h"
#include "eCollider.h"

namespace Engine
{
	class eGameObject
	{
	public:
		eGameObject(int Zorder);
		eGameObject();
		virtual ~eGameObject();

		// Instance name
		std::string name;
		// Active true we updating and drawing an object
		bool active{ true };

		// Public set of main functions
		void Init();
		void Update(float dt);
		void Draw();

		// Object reaction on collision
		virtual void Collision(eGameObject* secondObject);

		// PUBLIC INTERFACE
		// Setters
		void SetObjectSize(int width, int height);
		void SetAnchorPoint(Vec2 anchorPoint);
		void SetGameObjectScale(float scale);
		void SetRotationCenter(float x, float y);
		void AddCollider(Engine::eCollider* _collider);
		void DrawCollider(bool draw);
		
		// Getters
		Size GetObjectSize();
		Vec2& GetPosition();
		Vec2 GetRotationCenter();
		Engine::eCollider* GetCollider();

		// If true we check for collision with other objects
		bool collide{ false };

		// Object mass
		float Mass{};
		// Angle of rotating objects
		float Angle{};
		// Order of objects along the Z-axis on the screen
		int zOrder{};

		// Names of objects which do not collide with this object
		std::vector<std::string> notCollidingWith;
	protected:
		// Transform properties
		Vec2 AnchorPoint{ Vec2(0,0) };
		Vec2 rotationCenter{0.5f, 0.5f};
		Vec2 Position{};
		float scale{ 1.0f };
		Size objectSize{};

	private:
		// FUNCTIONS TO OVERRIDE
		// Use this for object initialization
		virtual void init() = 0;
		// Update is called once per frame for every object
		virtual void update(float dt) = 0;
		// Draw is called once per frame to draw object on the screen
		virtual void draw() = 0;

		// Bound collision object
		eCollider* collider{ nullptr };
		// Function to resolve collision from inside of collider
		void _setPosition(Vec2 newPosition);
	};
}