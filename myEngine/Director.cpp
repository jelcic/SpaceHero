#include "Director.h"

namespace Engine
{
	Director* Director::getInstance()
	{
		static Director* director = nullptr;
		if (director == nullptr)
			director = new Director;

		return director;
	}

	void Director::StartUp(HWND window, int window_width, int window_height)
	{
		_window = window;
		_graphicsManager = new GraphicsManager;
		_graphicsManager->Init(_window, true, window_width, window_height);
		_timeManager = new TimeManager;
		_timeManager->Init();
		_resourceManager = new ResourceManager;
		_collisionManager = new CollisionManager;
	}

	void Director::ShutDown()
	{
		if(_timeManager)
			delete _timeManager;
		_timeManager = nullptr;

		if (_graphicsManager)
			delete _graphicsManager;
		_graphicsManager = nullptr;

		if (_resourceManager)
			delete _resourceManager;
		_resourceManager = nullptr;

		if (_collisionManager)
			delete _collisionManager;
		_collisionManager = nullptr;
	}

	GraphicsManager * Director::GetGraphicsManager()
	{
		return _graphicsManager;
	}

	TimeManager * Director::GetTimeManager()
	{
		return _timeManager;
	}

	HWND Director::GetWindowHandle()
	{
		return _window;
	}

	ResourceManager * Director::GetResourceManager()
	{
		return _resourceManager;
	}

	CollisionManager * Director::GetCollisionManager()
	{
		return _collisionManager;
	}


	Director::Director()
	{
	}

	Director::~Director()
	{
	}
}