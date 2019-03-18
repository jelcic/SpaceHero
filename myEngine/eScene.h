#pragma once

#include <vector>
#include "eGameObject.h"

namespace Engine
{
	class eScene
	{
	public:
		eScene();

		// Clear all game objects 
		virtual ~eScene();

		// MAIN GAME FUNCTIONS

		// Init is a place where we build our scene
		// by adding game objects
		virtual void Init() = 0;

		// In update we update all game objects from the list
		// if we override this function we need to call base
		// functionality in appropriate place
		virtual void Update();

		// Here we draw all active objects from list to the screen
		void Draw();

		virtual void AddGameObject(eGameObject* object);		
		// to do
		virtual void RemoveGameObject(eGameObject* object);

		eGameObject* GetGameObject(int id);
		eGameObject* GetGameObject(int id, bool state);

		void CheckCollisionsOnScene();
		void PrintGameStatistics(bool s);
	protected:
		std::vector<eGameObject*> objectsList;
	private:
		bool _printStatistics{false};

		// Sorting mechanism
		static bool comparison(const eGameObject* object1, const eGameObject* object2);
	};
}
