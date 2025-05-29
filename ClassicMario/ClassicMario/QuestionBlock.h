#pragma once

// internal includes
#include "Collectible.h"
#include "CAnimationManager.h"
#include "AssetManager.h"

// external includes
#include "SFML/Graphics.hpp"

class CQuestionBlock
{
private:
	// sprites
	sf::Vector2f m_position;
	sf::Sprite m_emptyBlockSprite;
	sf::Sprite m_questionBlockSprite;
	sf::Sprite m_questionBlockCoinSprite;
	bool m_isOpened;

	// collectible stored in block
	ECollectible m_collectibleInside;

	// dependencies
	CAnimationManager* m_animationManager;
	CAssetManager* m_assetManager;

	// for coin animation
	bool m_coinFlag;
	float m_timePassed;

public:
	// constructor
	CQuestionBlock(sf::Vector2f position, CAssetManager& assetManager, CAnimationManager& animationManager, ECollectible collectible);

	// open the question block
	void OpenQuestionBlock();

	// setter
	void SetCollectibleState(EMarioStage& stage);

	// getter
	inline const bool& IsOpened() { return m_isOpened; };
	inline const ECollectible& GetCollectible() { return m_collectibleInside; };
	inline const sf::FloatRect& GetBlockBounds() { return m_questionBlockSprite.getGlobalBounds(); };

	// update and render
	void Update(const float& deltaTime);
	void Draw(sf::RenderTarget& target);
	
};

