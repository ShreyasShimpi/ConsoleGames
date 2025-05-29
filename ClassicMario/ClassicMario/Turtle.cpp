#include "Turtle.h"


CTurtle::CTurtle(sf::Vector2f pos)
{
	m_enemySprite = m_assetManager.GetSprite(EItems::Goomba_1);
	m_enemySprite.setPosition(pos);
	m_velocity = { -30.0f,0 };

}

void CTurtle::SetState(ETurtleStates state)
{
	m_state = state;
}

void CTurtle::HitFromTop(CPlayer& mario)
{
	m_state = ETurtleStates::StaticShellForm;
}

void CTurtle::HitFromBottom(CPlayer& mario)
{
	m_state = ETurtleStates::Dead;
}

void CTurtle::HitFromFireball(CPlayer& mario)
{
	HitFromBottom(mario);
}

bool CTurtle::IsAlive() const
{
	if (m_state == ETurtleStates::Dead)
	{
		return true;
	}
	return false;
}

//void CTurtle::TouchFromSide(CPlayer& mario)
//{
//	if (m_state == EStates::StaticShellForm)
//	{
//		m_state = EStates::MovingShellForm;
//	}
//
//	//else mario damage;
//}

void CTurtle::Update(float deltaTime)
{
	m_enemySprite.move(m_velocity.x*deltaTime, m_velocity.y*deltaTime);

	auto position = m_enemySprite.getPosition();
	if (m_direction == EDirection::Left)
	{
		m_animationManager.KoopaTroopaLeftAnimation(m_enemySprite, deltaTime);
	}
	else
	{
		m_animationManager.KoopaTroopaRightAnimation(m_enemySprite, deltaTime);
	}
	m_enemySprite.setPosition(position);
}

void CTurtle::ChangeDirection()
{
	m_velocity = -m_velocity;

	if (m_direction == EDirection::Left)
	{
		m_direction = EDirection::Right;
	}
	else
	{
		m_direction = EDirection::Left;
	}
}
