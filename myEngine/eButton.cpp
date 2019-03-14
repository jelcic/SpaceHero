#include "eButton.h"

void Engine::eButton::init()
{
}

void Engine::eButton::update(float dt)
{
	if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0)
	{
		POINT cursorPoint;
		GetCursorPos(&cursorPoint);

		if (cursorPoint.x >= (Position.X - objectSize.Width / 2)
			&& cursorPoint.x <= (Position.X + objectSize.Width / 2)
			&& cursorPoint.y >= (Position.Y - objectSize.Height / 2)
			&& cursorPoint.y <= (Position.Y + objectSize.Height / 2))
			ClickEvent();
	}
}

void Engine::eButton::draw()
{
	imageButton->Draw(nullptr, Position, objectSize, rotationCenter, AnchorPoint, Angle, scale);
}
