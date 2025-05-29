#pragma once
// external includes
#include <SFML/Graphics.hpp>

#define WIDTH 640
#define HEIGHT 480

constexpr float PI = 3.14159f;

constexpr int SCORE = 1;
constexpr int LIVES = 3;
constexpr float BALLVELOCITY = 200.0f;

static bool PointToRectCollision(sf::Vector2f point, sf::FloatRect rectangle)
{
	return (point.x >= rectangle.left && point.x <= rectangle.left + rectangle.width) &&
		(point.y >= rectangle.top && point.y <= rectangle.top + rectangle.height);
}

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

static double ToRadian(int degree)
{
	double radian = degree * PI / 180;
	return radian;
}