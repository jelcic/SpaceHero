#pragma once
#include "eGameObject.h"
#include "eImage.h"

namespace Engine
{
	class eButton : public eGameObject
	{
	public:
		eImage* imageButton;
		// ClickEvent to override
		virtual void ClickEvent() = 0;
	private:
		// FUNCTIONS TO OVERRIDE
		virtual void init() override;
		virtual void update(float dt) override;
		virtual void draw() override;
	};
}
