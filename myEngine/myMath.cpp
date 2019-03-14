#include "myMath.h"
#include <math.h>

namespace Engine
{
	float RandomFloat()
	{
		return (float)rand();
	}

	float Random(float min, float max)
	{
		return min + RandomFloat() * (max - min);
	}

	int RandomInt()
	{
		return rand();
	}

	int RandomInt(int min, int max)
	{
		return RandomInt() % max + min;
	}

	int RandomSign()
	{
		if (rand() % 2 == 0)
			return 1;
		else
			return -1;
	}

	float GetDistance(Vec2 A, Vec2 B)
	{
		return sqrtf((float)pow(B.X - A.X, 2) + (float)pow(B.Y - A.Y, 2));
	}

	Vec2 RotatePoint(Vec2 point, float angle)
	{
		return Vec2 { cosf(angle) * point.X - sinf(angle) * point.Y, 
			sinf(angle) * point.X + cosf(angle) * point.Y };
	}

	float Clamp(float value, float min, float max) {
		return MAX(min, MIN(max, value));
	}

	inline float MIN(float x1, float x2)
	{
		return x1 > x2 ? x2 : x1;
	}

	inline float MAX(float x1, float x2)
	{
		return x1 > x2 ? x1 : x2;
	}

	float vectorLength(Vec2 vec)
	{
		return sqrtf(powf(vec.X, 2.0f) + powf(vec.Y,2.0f));
	}
	bool IsPositionOutOfScreen(Vec2 position, float screenOffset)
	{
		auto director = Director::getInstance();
		if (position.X < -screenOffset ||
			position.Y < -screenOffset ||
			position.X > director->GetGraphicsManager()->GetGameWidth() + screenOffset ||
			position.Y > director->GetGraphicsManager()->GetGameHeight() + screenOffset)
			return true;
		return false;
	}
}