#include "Goomba.h"
#include "AssetManager.h"

CGoomba::CGoomba(sf::Vector2f pos)
{
	m_enemySprite = m_assetManager.GetSprite(EItems::Goomba_1);
	m_enemySprite.setPosition(pos);
	m_velocity = { -20.0f,0 };
}

void CGoomba::SetState(EGoombaStates state)
{
	m_state = state;
}

void CGoomba::HitFromTop(CPlayer& mario)
{
	m_state = EGoombaStates::CrouchedDeath;
}

void CGoomba::HitFromBottom(CPlayer& mario)
{
	m_state = EGoombaStates::NonCrouchedDeath;
}

void CGoomba::HitFromFireball(CPlayer& mario)
{
	HitFromBottom(mario);
}

bool CGoomba::IsAlive() const
{
	if (m_state == EGoombaStates::Normal)
	{
		return true;
	}
	return false;
}

void CGoomba::ChangeDirection()
{
	m_velocity = -m_velocity;

}

void CGoomba::Update(float deltaTime)
{
	if (m_state != EGoombaStates::Deactivated)//if the goomba's state is not activated
	{
		auto position = m_enemySprite.getPosition();
		m_animationManager.GoombaAnimation(m_enemySprite, deltaTime);//Updating goomba animation accordingly
		m_enemySprite.setPosition(position);
		m_enemySprite.move(m_velocity.x * deltaTime, m_velocity.y * deltaTime);//changing position
	}
}
