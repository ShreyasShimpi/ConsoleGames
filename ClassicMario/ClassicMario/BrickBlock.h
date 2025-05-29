#pragma once

// internal includes
#include "AssetManager.h"
#include "SFML/Graphics.hpp"

class CBrickBlock
{
private:
	// block sprite
	sf::Sprite m_brickBlockSprite;

public:
	// constructor
	CBrickBlock() = delete;
	CBrickBlock(sf::Vector2f position, CAssetManager& assetManager);

	// draw
	void Draw(sf::RenderTarget& target);
};

