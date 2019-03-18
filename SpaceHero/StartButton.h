#pragma once
#include "eButton.h"
#include "eImage.h"
#include "GameData.h"

class StartButton : public Engine::eButton
{
public:
	StartButton(Engine::eImage * defaultImg, Engine::eImage *hoverImg = nullptr, Engine::eImage *clickImg = nullptr, int Zorder = 0);
	GameData* gData{};
private:
	virtual void init() override;
	virtual void buttonPressed() override;
};