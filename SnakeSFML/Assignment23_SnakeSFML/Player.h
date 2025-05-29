#pragma once

// external includes
#include <vector>

// internal includes
#include "EventHandler.h"
#include "InputHandler.h"

#define HEAD 0

#define DOWN 0
#define LEFT 1
#define RIGHT 2
#define UP 3

#define HORIZONTAL 0
#define VERTICAL 1

#define UP_TO_LEFT 2
#define UP_TO_RIGHT 3
#define DOWN_TO_LEFT 0
#define DOWN_TO_RIGHT 1

#define SNAKE_BLOCKSIZE 20
#define SNAKE_SPRITESIZE 64

constexpr float MAXSPEED = 100.0f;

class CEngine;

class CSnake
{
private:
	// input handler
	CButton m_input;

	// snake body sprites
	std::vector<sf::Sprite> m_snakeSprite;

	// storing all textures
	std::vector<sf::Texture> m_snakeHead;
	std::vector<sf::Texture> m_snakeTail;
	std::vector<sf::Texture> m_snakBodyStaight;
	std::vector<sf::Texture> m_snakeBodyCurve;

	// head
	sf::Vector2f m_headPosition;
	sf::Vector2i m_headDirection;
	int m_trailSize;

	// listener function objects
	// listener function objects
	FUNCTIONHANDLER m_playerKeyPressedListnerCB;
	FUNCTIONHANDLER m_playerKeyReleasedListnerCB;

	// listener functions
	void PlayerKeyPressedListner(sf::Event event);
	void PlayerKeyReleasedListner(sf::Event event);

	void KeyPressAction(const float& deltaTime);
	void KeyReleaseAction(const float& deltaTime);

	// set new added sprite properties
	void AddSnakeSprite(sf::Sprite sprite, sf::Vector2f position);

public:
	CSnake() = delete;
	CSnake(CEngine& engine);

	// initialize (override)
	sf::RectangleShape CreateSnakeBodyBlock();
	void InitTextures();
	void InitCharacter(float initialPositionX, float initialPositionY);

	// Getters
	inline CButton& GetInput() { return m_input; };
	inline sf::FloatRect GetHeadGlobalBounds() { return m_snakeSprite[HEAD].getGlobalBounds(); }
	inline sf::Vector2f GetHeadPosition() { return m_snakeSprite[HEAD].getPosition(); }
	inline int GetTrailSize() { return m_trailSize; };
	sf::FloatRect GetBodyGlobalBounds(int index);

	// Setters
	void SetSnakeHeadPosition(sf::Vector2f position);

	// player movement
	void AddTrail();
	void UpdateTrail(sf::Vector2f headPosition);
	void UpdateTextures();
	void Move(const float& deltaTime); // (override)
	void KeyAction(const float& deltaTime);

	// update and render (override)
	void Update(const float& deltaTime);
	void Render(sf::RenderTarget& target);

};