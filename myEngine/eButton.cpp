#include "eButton.h"
#include "Director.h"

Engine::eButton::eButton(eImage * defaultImg, eImage * hoverImg, eImage * clickImg, int Zorder)
	: eGameObject(Zorder), defaultImage(defaultImg)
{
	if (hoverImg == nullptr)
		hoverImage = defaultImg;

	if (clickImg == nullptr)
		clickImage = defaultImg;
}

Engine::eButton::~eButton()
{
	if (defaultRect)
	{
		delete defaultRect;
		defaultRect = nullptr;
	}

	if (hoverRect)
	{
		delete hoverRect;
		hoverRect = nullptr;
	}

	if (clickRect)
	{
		delete clickRect;
		clickRect = nullptr;
	}
}

void Engine::eButton::SetDefaultRect(int left, int top, int right, int bottom)
{
	defaultRect = new RECT{ left, top, right, bottom };
}

void Engine::eButton::SetHoverRect(int left, int top, int right, int bottom)
{
	hoverRect = new RECT{ left, top, right, bottom };
}

void Engine::eButton::SetClickRect(int left, int top, int right, int bottom)
{
	clickRect = new RECT{ left, top, right, bottom };
}

void Engine::eButton::update(float dt)
{
	processMauseInput();
}

void Engine::eButton::draw()
{
	switch (state)
	{
	case State::default:
		defaultImage->Draw(defaultRect, Position, objectSize, rotationCenter, AnchorPoint, Angle, scale);
		break;
	case State::hover:
		hoverImage->Draw(hoverRect, Position, objectSize, rotationCenter, AnchorPoint, Angle, scale);
		break;
	case State::clicked:
		clickImage->Draw(clickRect, Position, objectSize, rotationCenter, AnchorPoint, Angle, scale);
		break;
	}
}

void Engine::eButton::processMauseInput()
{
	POINT p;
	if (!GetCursorPos(&p))
		return;

	auto director = Engine::Director::getInstance();
	ScreenToClient(director->GetWindowHandle(), &p);

	Vec2 cursorPos{ (float)p.x, (float)director->GetGraphicsManager()->GetGameHeight() - p.y };

	if (cursorPos.X < 300)
		int i = 0;

	if (cursorPos.X >= Position.X && cursorPos.X <= Position.X + objectSize.Width
		&& cursorPos.Y >= Position.Y && cursorPos.Y <= Position.Y + objectSize.Height)
	{
		if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0)
		{
			state = State::clicked;
			buttonPressed();
		}
		else
			state = State::hover;
	}
	else
		state = State::default;

}
