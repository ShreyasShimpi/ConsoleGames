#pragma once
#include "Collectible.h"

/*
	Red mushroom
*/
class CGrowthPower : public CCollectible
{
public:
	// Constructor
	CGrowthPower() = delete;
	CGrowthPower(const sf::Vector2f& initialPosition, const sf::Sprite& collectibleSprite, CAnimationManager& animationManager);

	// update
	void Update(float frameTime);
};

