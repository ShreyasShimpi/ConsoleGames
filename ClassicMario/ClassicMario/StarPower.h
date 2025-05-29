#pragma once
#include "Collectible.h"

// Declaring classes
class CAnimationManager;

class CStarPower : public CCollectible
{
public:
	// Constructor
	CStarPower() = delete;
	CStarPower(const sf::Vector2f& initialPosition, const sf::Sprite& collectibleSprite, CAnimationManager& animationManager);

	// update
	void Update(float frameTime);
};

