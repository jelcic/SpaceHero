#pragma once
#include "eGameObject.h"
#include "eImage.h"

namespace Engine
{
	class eButton : public eGameObject
	{
		// Image for default button state 
		eImage *defaultImage;
		// Rect for default if we use sprite sheet
		RECT* defaultRect{};

		// Image for hover button state 
		eImage *hoverImage;
		// Rect for hover if we use sprite sheet
		RECT* hoverRect{};

		// Image for clicked button state 
		eImage *clickImage;
		// Rect for clicked state if we use sprite sheet
		RECT* clickRect{};

		enum class State { default, hover, clicked }
		state{ State::default };

		// Here we define button pressed action
		virtual void buttonPressed() = 0;

		// Update and draw are sealed
		virtual void update(float dt) final;
		virtual void draw() final;

		// We need to override Init() and processMauseInput
		virtual void processMauseInput();
	public:
		eButton(eImage *defaultImg, eImage *hoverImg = nullptr, eImage *clickImg = nullptr, int Zorder = 0);
		virtual ~eButton();
		void SetDefaultRect(int left, int top, int right, int bottom);
		void SetHoverRect(int left, int top, int right, int bottom);
		void SetClickRect(int left, int top, int right, int bottom);
	};
}
