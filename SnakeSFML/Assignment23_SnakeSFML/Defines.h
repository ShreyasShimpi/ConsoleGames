#pragma once
// external includes
#include <SFML/Graphics.hpp>

#define WIDTH 640
#define HEIGHT 480
constexpr int SCORE = 10;
constexpr int LIVES = 3;

static bool PointToRectCollision(sf::Vector2f point, sf::FloatRect rectangle)
{
	return (point.x >= rectangle.left && point.x <= rectangle.left + rectangle.width) &&
		(point.y >= rectangle.top && point.y <= rectangle.top + rectangle.height);
}
