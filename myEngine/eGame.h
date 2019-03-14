#pragma once
#include <vector>
#include "Director.h"
#include "eGameObject.h"
#include "CollisionManager.h"
#include "eScene.h"

namespace Engine
{
	class eGame
	{
	public:
		bool Pause {false};
		bool IsRunning();
		eGame();
		virtual ~eGame();
		virtual void Init();

		eScene* GetCurrentScene();
		void AddScene(eScene* newScene);

		void UpdateAndDraw();
		void GameOver();
		
	protected:
		bool Running{ true };
		virtual void Update() = 0;

		bool updateScane{ true };
		bool drawScene{ true };
		bool checkGameObejctCollisions{ true };
	private:
		eScene* _currentScene{ nullptr };
	};
}