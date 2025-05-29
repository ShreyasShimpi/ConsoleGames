// internal includes
#include "Character.h"

CCharacter::CCharacter()
{
	m_characterType = ECharacterType::NONE;
	m_position = { 0.0f,0.0f };
	m_velocity = { 0.0f, 0.0f };
	m_targetVelocity = { 0.0f, 0.0f };
	m_isAnimationRunning = false;
	m_nextFrameDelay = 0.0f;
	m_totalTime = 0.0f;
}


void CCharacter::SetVelocity(sf::Vector2f velocity)
{
	if (std::isnan(velocity.x) || std::isnan(velocity.y))
	{
		return;
	}
	m_velocity = velocity;
}

void CCharacter::SetTargetVelocityX(float velX)
{
	if (std::isnan(velX))
	{
		return;
	}
	m_targetVelocity.x = velX;
}

void CCharacter::SetTargetVelocityY(float velY)
{
	if (std::isnan(velY))
	{
		return;
	}
	m_targetVelocity.y = velY;
}