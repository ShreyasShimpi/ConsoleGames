#pragma once

//external includes
#include <SFML/Graphics.hpp>
#include <unordered_map>

// enum for all the sprites in the game
enum class ESprite
{
	// main menu graphic
	Menu_Graphic,

	// player
	Player,
	Player_Bullet,
	Player_Death,

	// enemy
	Enemy_Squid_1,
	Enemy_Squid_2,

	Enemy_Flat_1,
	Enemy_Flat_2,

	Enemy_Crab_1,
	Enemy_Crab_2,

	Enemy_UFO,
	Enemy_Bullet,
	Enemy_Death,

	// shield
	Shield,
	Shield_Damaged_1,
	Shield_Damaged_2,
	Shield_Damaged_3,
	Shield_Damaged_4
};

class CAssetManager
{
private:
	// all textures
	sf::Texture m_textueT;

	// maps storing all the sprites
	std::unordered_map<ESprite, sf::Sprite> m_sprites;

	// private functions
	void LoadSprites();

public:
	// constructor
	CAssetManager();

	// return a copy of the sprite requested
	sf::Sprite GetSprite(ESprite item);
};

