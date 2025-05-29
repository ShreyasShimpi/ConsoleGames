#pragma once
#include "Collectible.h"

// declaring classes
class CAnimationManager;

/*
	Floating coin
*/
class CCoin : public CCollectible
{
public:
	// Constructor
	CCoin() = delete;
	CCoin(const sf::Vector2f& initialPosition, const sf::Sprite& collectibleSprite, CAnimationManager& animationManager);

	// Update
	void Update(float frameTime);
};

