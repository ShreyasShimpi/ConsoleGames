#pragma once
// external includes
#include "SFML/Graphics.hpp"

// internal includes
#include "Defines.h"

class CDucks
{
	// death animation
	bool m_isDeathAnimationRunning;
	bool m_isDead;

	// sprite and textures
	sf::Sprite m_duckSprite;
	std::vector<sf::Texture> m_flightTexture;
	sf::Texture m_deathTexture;
	int m_angle;
	
	//animation
	float m_nextFrameDelay;
	float m_totalTime;

public:
	CDucks();
	void InitTexture();
	void InitSprite();
	void SetDuckProperties(float PositionX, float PositionY, int angle);

	// player movement
	void Move(const float& deltaTime); // (override)

	// animation
	void RunAnimation(const float& deltaTime);
	void RunDeathAnimation(const float& deltaTime);

	// getter
	inline sf::FloatRect GetDuckBounds() { return m_duckSprite.getGlobalBounds(); };
	inline bool IsDead() { return m_isDeathAnimationRunning; };

	// setter
	void SetDuckLife(bool state);

	// update and render (override)
	void Update(const float& deltaTime);
	void Render(sf::RenderTarget& target);
};

