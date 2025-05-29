#include "Coin.h"
#include "CAnimationManager.h"

constexpr int g_movementSpeed = 10;
constexpr int g_gravity = 10;

CCoin::CCoin(const sf::Vector2f& initialPosition, const sf::Sprite& collectibleSprite, CAnimationManager& animationManager)
	: CCollectible(initialPosition, collectibleSprite, animationManager)
{
	this->m_velocity = { 0, 0 };
	this->m_collectibleType = ECollectible::Coin;
}

void CCoin::Update(float frameTime)
{
	// animation
	m_animationManager->CoinAnimation(this->m_collectibleSprite, frameTime);
	m_collectibleSprite.setPosition(m_position);
}
