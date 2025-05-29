#pragma once

// internal includes
#include "Character.h"

constexpr float ENEMYSPEED = 20.0f;
constexpr float ENEMY_ANIMATION_DELAY = 0.5f;
#define ENEMYRUNSPRITES 3

class CEnemy : public CCharacter
{
private:
	std::vector<sf::Texture> m_rightTexture;
	std::vector<sf::Texture> m_leftTexture;
public:
	CEnemy();
	void InitTexture();
	void InitSprite();
	void InitCharacter(float initialPositionX, float initialPositionY);

	// player movement
	void Move(const float& deltaTime); // (override)

	// animation
	void RunAnimation(float animationDelay, const float& deltaTime);


	// update and render (override)
	void Update(const float& deltaTime);
	void Render(sf::RenderTarget& target);
};

