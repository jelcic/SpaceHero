#include "eGame.h"

namespace Engine
{
	eGame::eGame() { }

	eGame::~eGame() 
	{
		if (_currentScene)
			delete _currentScene;
		_currentScene = nullptr;
	}

	void eGame::Init() {	}

	void eGame::UpdateAndDraw()
	{
		// If a game doesn't have a scene throw an error
		if(!_currentScene)
			throw 101;
		
		// Time update
		Director::getInstance()->GetTimeManager()->Update();
		
		if(updateScane)
			_currentScene->Update();

		// Specific game update
		Update();
		
		// Check collisions on current scene
		if (checkGameObejctCollisions)
			_currentScene->CheckCollisionsOnScene();
		
		// Draw the scene
		if(drawScene)
			_currentScene->Draw();
	}

	eScene * eGame::GetCurrentScene()
	{
		return _currentScene;
	}

	void eGame::AddScene(eScene * newScene)
	{
		if (_currentScene)
			delete _currentScene;

		_currentScene = newScene;
	}

	bool eGame::IsRunning()
	{
		return Running;
	}

	void eGame::GameOver()
	{
		Running = false;
	}


}

