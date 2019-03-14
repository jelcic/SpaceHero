#pragma once
#include <stdlib.h>
#include "eTypes.h"
#include "Director.h"

namespace Engine
{
	const float PI{ 3.14159265359f };

	// Get random floating point number between 0 and 1
	float RandomFloat();

	// Get random floating point number between min and max
    float Random(float min, float max);
	
	// Get random integer number
	int RandomInt();

	// Get random integer number between min and max
	int RandomInt(int min, int max);
	
	// Get random value (1 or -1)
	int RandomSign();

	// Get distance between two points in 2D space
	float GetDistance(Vec2 A, Vec2 B);

	// Rotate point about origin by the given angle
	Vec2 RotatePoint(Vec2 point, float angle);

	// Clamps a value to a value within a given range
	float Clamp(float value, float min, float max);

	// Returns minimal value
	float MIN(float x1, float x2);

	// Returns maximal value
	float MAX(float x1, float x2);

	// Length of vector
	float vectorLength(Vec2 vec);

	// Check is position in visible part of the screen
	bool IsPositionOutOfScreen(Vec2 position, float screenOffset);
}

