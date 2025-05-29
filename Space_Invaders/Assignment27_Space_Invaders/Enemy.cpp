// external includes
#include <iostream>

// internal includes
#include "Enemy.h"
#include "AssetManager.h"

CEnemy::CEnemy(sf::Vector2f position, CAssetManager& assetManager, EEnemyType enemyType)
	:m_assetManager(&assetManager), m_type(enemyType)
{
	m_isDead = false;
	m_isVisible = true;
	m_spriteIndex = 0;
	m_deadTime = 0.0f;
	
	// enemy animation
	switch (enemyType)
	{
	case EEnemyType::Squid:
		m_enemyAnimationSprites.emplace_back(m_assetManager->GetSprite(ESprite::Enemy_Squid_1));
		m_enemyAnimationSprites.emplace_back(m_assetManager->GetSprite(ESprite::Enemy_Squid_2));
		break;
	case EEnemyType::Crab:
		m_enemyAnimationSprites.emplace_back(m_assetManager->GetSprite(ESprite::Enemy_Crab_1));
		m_enemyAnimationSprites.emplace_back(m_assetManager->GetSprite(ESprite::Enemy_Crab_2));
		break;
	case EEnemyType::Flat:
		m_enemyAnimationSprites.emplace_back(m_assetManager->GetSprite(ESprite::Enemy_Flat_1));
		m_enemyAnimationSprites.emplace_back(m_assetManager->GetSprite(ESprite::Enemy_Flat_2));
		break;
	case EEnemyType::UFO:
		m_enemyAnimationSprites.emplace_back(m_assetManager->GetSprite(ESprite::Enemy_UFO));
		break;
	default:
		break;
	}

	// enemy death
	m_enemyDeathSprite = m_assetManager->GetSprite(ESprite::Enemy_Death);

	m_enemySprite = m_enemyAnimationSprites[m_spriteIndex];
	m_enemySprite.setPosition(position);
}

void CEnemy::SetPosition(const sf::Vector2f position)
{
	m_enemySprite.setPosition(position);
}

void CEnemy::Move(const sf::Vector2f offset)
{

	sf::Vector2f tempPosition = m_enemySprite.getPosition();
	m_spriteIndex = (m_spriteIndex + 1) % m_enemyAnimationSprites.size();
	m_enemySprite = m_enemyAnimationSprites[m_spriteIndex];
	m_enemySprite.setPosition(tempPosition + offset);
}

void CEnemy::Hit()
{
	m_isDead = true;
	m_deadTime = 0.0f;
	sf::Vector2f tempPosition = m_enemySprite.getPosition();
	m_enemyDeathSprite.setPosition(tempPosition);
}

void CEnemy::Update(const float& deltaTime)
{
	if(m_isDead && m_isVisible)
	{
		m_deadTime += deltaTime;
	}
}

void CEnemy::Render(sf::RenderTarget& target)
{
	if (m_isVisible)
	{
		if (!m_isDead)
		{
			target.draw(m_enemySprite);
		}
		else
		{
			// explosion animation time
			if (m_deadTime < 0.4f)
			{
				target.draw(m_enemyDeathSprite);
			}
			else
			{
				m_isVisible = false;
			}
		}
	}
}