#pragma once
// external includes
#include <SFML/Graphics.hpp>
#include <vector>

// window
#define WIDTH 640
#define HEIGHT 480
#define DEFENCE_HEIGHT 440

// bullet
constexpr float g_playerBulletSpeed = 500.0f;
constexpr float g_enemyBulletSpeed = 100.0f;

// player
constexpr float g_playerSpeed = 200.0f;
constexpr short g_playerTotalLives = 3;

// enemy grid
#define ENEMY_GRID_ROWS 5
#define ENEMY_GRID_COLUMNS 11
#define ENEMY_GRID_SIZE 35
#define ENEMY_GRID_OFFSET_X 10
#define ENEMY_GRID_OFFSET_Y 80

// enemy moevement
constexpr float g_enemyStepTime = 1.0f; // seconds
constexpr float g_enemySidewardStep = 10.0f; 
constexpr float g_enemyDownwardStep = 10.0f; 

// enmey scores
constexpr short g_flatPoints = 10;
constexpr short g_crabPoints = 20;
constexpr short g_squidPoints = 40;

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

// custom intersect Function
static bool RectToRectCollision(sf::FloatRect rectangle1, sf::FloatRect rectangle2)
{
	return (rectangle1.left < rectangle2.left + rectangle2.width) &&
		(rectangle2.left < rectangle1.left + rectangle1.width) &&
		(rectangle1.top < rectangle2.top + rectangle2.height) &&
		(rectangle2.top < rectangle1.top + rectangle1.height);
}