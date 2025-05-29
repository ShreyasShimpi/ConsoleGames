#pragma once
#include "Collectible.h"

// Declaring classes
class CAnimationManager;

class CFireFlower : public CCollectible
{
public:
	// Constructor
	CFireFlower() = delete;
	CFireFlower(const sf::Vector2f& initialPosition, const sf::Sprite& collectibleSprite, CAnimationManager& animationManager);

	// update
	void Update(float frameTime);

};