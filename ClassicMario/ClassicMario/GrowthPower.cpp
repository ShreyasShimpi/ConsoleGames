#include "GrowthPower.h"

// Global variables
constexpr short g_movementSpeed = 150;
constexpr short g_gravity = 1000;

CGrowthPower::CGrowthPower(const sf::Vector2f& initialPosition, const sf::Sprite& collectibleSprite, CAnimationManager& animationManager)
	: CCollectible(initialPosition, collectibleSprite, animationManager)
{
	this->m_timePassed = 0.f;
	this->m_velocity = {g_movementSpeed, 0};	// Collectible starts to move after completely spawned
	this->m_collectibleType = ECollectible::Growth_Power;
}

void CGrowthPower::Update(float frameTime)
{
	// Spawning animation
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

	// update sprite
	m_collectibleSprite.setPosition(m_position);
}
