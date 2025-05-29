#include "StarPower.h"
#include "CAnimationManager.h"

// Global variables
constexpr short g_movementSpeed = 150;
constexpr short g_gravity = 1000;

CStarPower::CStarPower(const sf::Vector2f& initialPosition, const sf::Sprite& collectibleSprite, CAnimationManager& animationManager)
	: CCollectible(initialPosition, collectibleSprite, animationManager)
{
	this->m_timePassed = 0;
	this->m_velocity = { float(g_movementSpeed * std::sqrt(2)), float(g_movementSpeed * std::sqrt(2)) };	// launched as a projectile
	this->m_collectibleType = ECollectible::Growth_Power;
}

void CStarPower::Update(float frameTime)
{
	// spawning animation
	if (m_timePassed < m_growthTime)
	{
		m_timePassed += frameTime;
		m_position.y += m_growthSpeed.y * frameTime;
		m_collectibleSprite.setPosition(m_position);
		return;
	}

	// update velocity
	m_velocity.y += g_gravity * frameTime;

	// update position
	m_position.x += m_velocity.x * frameTime;
	m_position.y += m_velocity.y * frameTime;

	// animation
	m_animationManager->StarAnimation(this->m_collectibleSprite, frameTime);
	m_collectibleSprite.setPosition(m_position);
}
