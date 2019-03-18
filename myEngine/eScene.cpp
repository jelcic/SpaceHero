#include "eScene.h"
#include "Director.h"
#include <algorithm>

Engine::eScene::eScene() { }

Engine::eScene::~eScene()
{
	for (auto object : objectsList)
		if(object)
			delete object;
	objectsList.clear();
}

void Engine::eScene::Update()
{
	float dt = Engine::Director::getInstance()->GetTimeManager()->ElapsedGameTime;

	for (Engine::eGameObject* object : objectsList)
		if (object->active)
			object->Update(dt);
}

void Engine::eScene::Draw()
{
	auto director = Engine::Director::getInstance();
	auto gManager = director->GetGraphicsManager();
	gManager->BeginRender();

	for (auto object : objectsList)
		if(object->active)
			object->Draw();

	if (_printStatistics)
		director->GetGraphicsManager()->PrintStatistics(director->GetTimeManager()->ElapsedGameTime, (int)director->GetTimeManager()->TotalGameTime);

	gManager->EndRender();
}

void Engine::eScene::AddGameObject(eGameObject * object)
{
	if (object != nullptr)
	{
		objectsList.push_back(object);
		std::sort(objectsList.begin(), objectsList.end(), comparison);
	}
		
}

void Engine::eScene::RemoveGameObject(eGameObject * object)
{
	// to do
}

Engine::eGameObject * Engine::eScene::GetGameObject(int id)
{
	for (auto object : objectsList)
		if(object->id == id)
			return object;

	return nullptr;
}

Engine::eGameObject * Engine::eScene::GetGameObject(int id, bool state)
{
	for (auto object : objectsList)
		if (object->id == id && object->active == state)
			return object;

	return nullptr;
}

void Engine::eScene::CheckCollisionsOnScene()
{
	auto collisionManager = Director::getInstance()->GetCollisionManager();
	collisionManager->Check(objectsList);
}

void Engine::eScene::PrintGameStatistics(bool s)
{
	_printStatistics = s;
}

bool Engine::eScene::comparison(const eGameObject * object1, const eGameObject * object2)
{
	return object1->zOrder < object2->zOrder;
}


