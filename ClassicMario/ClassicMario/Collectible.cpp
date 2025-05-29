#include "Collectible.h"
#include "CAnimationManager.h"

// Global variables
constexpr short g_growthTime = 2;		// Spawn animation duration
constexpr short g_growthSpeed = 8;		// Spawn speed in pixels/second

// Constructor
CCollectible::CCollectible(const sf::Vector2f& initialPosition, const sf::Sprite& collectibleSprite, CAnimationManager& animationManager)
{
	this->m_growthSpeed = { 0, -g_growthSpeed };
	this->m_growthTime = g_growthTime;
	this->m_creationTime = std::chrono::high_resolution_clock::now();

	this->m_collectibleSprite = collectibleSprite;
	this->m_position = initialPosition;
	this->m_collectibleSprite.setPosition(initialPosition);
	this->m_animationManager = &animationManager;
}

void CCollectible::ChangeDirection()
{
	m_velocity.x = -m_velocity.x;
}

void CCollectible::SetPosition(const sf::Vector2f& newPosition)
{
	this->m_position = newPosition;
	this->m_collectibleSprite.setPosition(newPosition);
}
