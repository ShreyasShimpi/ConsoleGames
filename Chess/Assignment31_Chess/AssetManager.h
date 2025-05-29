#pragma once

//external includes
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class CAssetManager
{
private:
	// all textures
	sf::Texture m_backgroundT;
	sf::Texture m_piecesT;

	// maps storing all the sprites
	std::unordered_map<std::string, sf::Sprite> m_sprites;

	// private functions
	void LoadSprites();

public:
	// constructor
	CAssetManager();

	// return a copy of the sprite requested
	sf::Sprite GetSprite(const std::string& spriteCode);
};

