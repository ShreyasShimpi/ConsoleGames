#pragma once
// external includes
#include <vector>
#include <memory>

// internal includes
#include "Player.h"
#include "Fruit.h"
#include "Defines.h"

class CEngine;

class CSpawnManager
{
private:
	CEngine& m_engine;

	// winner
	bool m_isDead;
	sf::Text m_message;
	int m_score;

	// player
	std::unique_ptr<CSnake> m_snake;
	int m_lives;

	// fruit
	std::unique_ptr<CFruit> m_fruit;

	// background
	sf::Sprite m_bgSprite;
	sf::Texture m_bgTexture;
	void LoadBackground();

public:
	// constructor
	CSpawnManager(CEngine& game, unsigned int width, unsigned int height);
	~CSpawnManager();

	// Randomize Position
	void RandomizeFruit();

	// collision
	void CheckCollisionWithFruit();
	void CheckCollisionWithBoundary();
	void CheckCollisionWithItself();

	// display message
	void DisplayMessage(std::string massage, sf::Color color, sf::Vector2f position, unsigned int charSize, sf::RenderTarget& target);

	// Update and render
	void UpdateSpawns(const float& deltaTime);
	void RenderSpawns(sf::RenderTarget& target);

};

