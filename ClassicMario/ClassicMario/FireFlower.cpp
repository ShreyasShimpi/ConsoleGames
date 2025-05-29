#include "FireFlower.h"
#include "CAnimationManager.h"

CFireFlower::CFireFlower(const sf::Vector2f& initialPosition, const sf::Sprite& collectibleSprite, CAnimationManager& animationManager)
	: CCollectible(initialPosition, collectibleSprite, animationManager)
{
	this->m_timePassed = 0;
	this->m_velocity = { 0, 0 };	// Fire flower is stationary
	this->m_collectibleType = ECollectible::FireFlower;
}

void CFireFlower::Update(float frameTime)
{
	// spawning animation
	if (m_timePassed < m_growthTime)
	{
		m_timePassed += frameTime;
		m_position.y += m_growthSpeed.y * frameTime;
	}

	// animation
	m_animationManager->FireFlowerAnimation(this->m_collectibleSprite, frameTime);
	m_collectibleSprite.setPosition(m_position);
}
