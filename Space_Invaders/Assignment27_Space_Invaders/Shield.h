#pragma once

// internal includes
#include "Defines.h"
class CAssetManager;

class CShield
{

private:
	// asset manager
	CAssetManager* m_assetManager;

	// shield
	std::vector<sf::Sprite> m_shieldSprite;
	short m_hitCount;
	bool m_isDestroyed;

public:
	CShield() = delete;
	CShield(sf::Vector2f position, CAssetManager& assetManager);

	// getter
	inline const bool& IsDestroyed() { return m_isDestroyed; };
	inline const sf::FloatRect& GetShieldBounds() { return m_shieldSprite[0].getGlobalBounds(); };
	void Hit();

	// update and render
	void Update(const float& deltaTime);
	void Render(sf::RenderTarget& target);
};

