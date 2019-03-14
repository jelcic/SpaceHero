#pragma once

#include "GraphicsManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"

namespace Engine
{
	class Director
	{
	public:
		static Director* getInstance();
		~Director();

		void StartUp(HWND window, int window_width, int window_height);
		void ShutDown();

		GraphicsManager* GetGraphicsManager();
		TimeManager* GetTimeManager();
		HWND GetWindowHandle();
		ResourceManager* GetResourceManager();
		CollisionManager* GetCollisionManager();
	private:
		Director();
		//main window Handles
		HWND _window;
		CollisionManager* _collisionManager;
		GraphicsManager* _graphicsManager;
		TimeManager* _timeManager;
		ResourceManager* _resourceManager;
	};
}