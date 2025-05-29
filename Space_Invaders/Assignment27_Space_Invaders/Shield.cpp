// internal includes
#include "Shield.h"
#include "AssetManager.h"

CShield::CShield(sf::Vector2f position, CAssetManager& assetManager)
	:m_assetManager(&assetManager)
{
	m_hitCount = 0;
	m_isDestroyed = false;

	m_shieldSprite.emplace_back(m_assetManager->GetSprite(ESprite::Shield));
	m_shieldSprite.emplace_back(m_assetManager->GetSprite(ESprite::Shield_Damaged_1));
	m_shieldSprite.emplace_back(m_assetManager->GetSprite(ESprite::Shield_Damaged_2));
	m_shieldSprite.emplace_back(m_assetManager->GetSprite(ESprite::Shield_Damaged_3));

	for (auto& shield : m_shieldSprite)
	{
		shield.setPosition(position);
	}
}

void CShield::Hit()
{
	m_hitCount++;

	if (m_hitCount >= m_shieldSprite.size())
	{
		m_isDestroyed = true;
	}
}

void CShield::Update(const float& deltaTime)
{
}

void CShield::Render(sf::RenderTarget& target)
{
	if (m_hitCount < m_shieldSprite.size()) // 3 shots allowed
	{
		target.draw(m_shieldSprite[m_hitCount]);
	}
}
