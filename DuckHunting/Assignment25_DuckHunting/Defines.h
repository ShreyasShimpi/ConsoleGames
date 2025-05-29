#pragma once
// external includes
#include <SFML/Graphics.hpp>

// window
#define WIDTH 640
#define HEIGHT 480
#define SCOPE_BOTTOM 320

// used in ToRadian
constexpr float PI = 3.14159f;

// player
constexpr int SCORE = 10;
constexpr int TOTAL_SHOTS = 25;

// duck
constexpr float DUCKVELOCITY = 150.0f;
constexpr float DUCKDOWNVELOCITY = 300.0f;

constexpr float DUCK_ANIMATION_DELAY = 0.5f;


// LERP method
static float Lerp(float currentVelocity, float targetVelocity, float deltatime)
{
	float diff = targetVelocity - currentVelocity;
	if (diff > deltatime)
	{
		return currentVelocity + deltatime;
	}
	if (diff < -deltatime)
	{
		return currentVelocity - deltatime;
	}
	return targetVelocity;
}

// to radian
static double ToRadian(int degree)
{
	double radian = degree * PI / 180;
	return radian;
}