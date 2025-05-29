#pragma once

// internal includes
#include "Defines.h"

class CAssetManager;
	
enum class EEnemyType
{
	Squid, 
	Crab, 
	Flat,
	UFO
};

class CEnemy
{
private:
	// asset manager
	CAssetManager* m_assetManager;

	// enemy
	sf::Sprite m_enemySprite;
	sf::Sprite m_enemyDeathSprite;
	std::vector<sf::Sprite> m_enemyAnimationSprites;
	short m_spriteIndex;

	bool m_isDead;
	bool m_isVisible;
	float m_deadTime;
	EEnemyType m_type;

public:
	CEnemy() = delete;
	CEnemy(sf::Vector2f position, CAssetManager& assetManager, EEnemyType enemyType);

	// getter
	inline const sf::Vector2f& GetPlayerPosition() { return m_enemySprite.getPosition(); };
	inline const sf::FloatRect& GetEnemyBounds() { return m_enemySprite.getGlobalBounds(); };
	inline const sf::Vector2f& GetEnemyPosition() { return m_enemySprite.getPosition(); };
	inline const EEnemyType& GetEnemyType() { return m_type; };
	inline const bool& IsDead() { return m_isDead; };

	// setter
	void SetPosition(const sf::Vector2f position);
	void Move(const sf::Vector2f offset);

	void Hit();

	// update and render
	void Update(const float& deltaTime);
	void Render(sf::RenderTarget& target);

};

