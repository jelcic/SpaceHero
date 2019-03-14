#include "eCollider.h"

Engine::eCollider::eCollider(Vec2 & position, unsigned long cColor) : color(cColor), PerentPosition(position)
{
}

Engine::eCollider::~eCollider()
{
}

void Engine::eCollider::ShowCollider(bool show)
{
	showCollider = show;
}
