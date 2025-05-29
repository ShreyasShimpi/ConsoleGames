
#include "Enemy.h"

void CEnemy::SetDirection(EDirection direction)
{
	m_direction = direction;
}

void CEnemy::SetPosition(sf::Vector2f pos)
{
	m_enemySprite.setPosition(pos);
}

void CEnemy::SetVelocity(sf::Vector2f speed)
{
	m_velocity = speed;
}

void CEnemy::SetSprite(sf::Sprite enemySprite)
{
	m_enemySprite = enemySprite;
}

void CEnemy::SetScore(int score)
{
	m_deathScore = score;
}

void CEnemy::Draw(sf::RenderWindow& window)
{
	window.draw(m_enemySprite);
}
