#include "StartButton.h"

StartButton::StartButton(Engine::eImage * defaultImg, Engine::eImage * hoverImg, Engine::eImage * clickImg, int Zorder)
	: Engine::eButton(defaultImg, hoverImg, clickImg, Zorder)
{

}

void StartButton::init()
{
	Position = { 500.0f, 200.0f };
	objectSize = { 151, 64 };
	SetDefaultRect(0, objectSize.Height, objectSize.Width, 0);
	SetHoverRect(0, objectSize.Height * 2, objectSize.Width, objectSize.Height);
	SetClickRect(0, objectSize.Height * 3, objectSize.Width, objectSize.Height * 2);
}

void StartButton::buttonPressed()
{
	gData->NextLevel();
}
