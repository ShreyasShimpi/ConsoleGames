#pragma once
#include "Collectible.h"

/*
	Green Mushroom
*/
class COneUpPower : public CCollectible
{
public:
	// Constructor
	COneUpPower() = delete;
	COneUpPower(const sf::Vector2f& initialPosition, const sf::Sprite& collectibleSprite, CAnimationManager& animationManager);

	// update and render
	void Update(float frameTime);
};

