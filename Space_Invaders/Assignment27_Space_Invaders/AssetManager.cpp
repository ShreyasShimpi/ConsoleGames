#include "AssetManager.h"

void CAssetManager::LoadSprites()
{
	//menu graphic 
	m_sprites[ESprite::Menu_Graphic] = sf::Sprite(m_textueT, sf::IntRect{ 0,0,617,180 });

	// player
	m_sprites[ESprite::Player] = sf::Sprite(m_textueT, sf::IntRect{ 277,228,26,16 });
	m_sprites[ESprite::Player_Bullet] = sf::Sprite(m_textueT, sf::IntRect{ 415,277,2,12 });
	m_sprites[ESprite::Player_Death] = sf::Sprite(m_textueT, sf::IntRect{ 367,275,30,16 });

	// enemy
	m_sprites[ESprite::Enemy_Squid_1] = sf::Sprite(m_textueT, sf::IntRect{ 7,225,16,16 });
	m_sprites[ESprite::Enemy_Squid_2] = sf::Sprite(m_textueT, sf::IntRect{ 40,225,16,16 });

	m_sprites[ESprite::Enemy_Flat_1] = sf::Sprite(m_textueT, sf::IntRect{ 147,226,24,16 });
	m_sprites[ESprite::Enemy_Flat_2] = sf::Sprite(m_textueT, sf::IntRect{ 179,226,24,16 });

	m_sprites[ESprite::Enemy_Crab_1] = sf::Sprite(m_textueT, sf::IntRect{ 74,225,22,16 });
	m_sprites[ESprite::Enemy_Crab_2] = sf::Sprite(m_textueT, sf::IntRect{ 107,225,22,16 });

	m_sprites[ESprite::Enemy_UFO] = sf::Sprite(m_textueT, sf::IntRect{ 215,224,48,21 });
	m_sprites[ESprite::Enemy_Bullet] = sf::Sprite(m_textueT, sf::IntRect{ 413,277,6,12 });
	m_sprites[ESprite::Enemy_Death] = sf::Sprite(m_textueT, sf::IntRect{ 437,276,26,16 });

	// shield
	m_sprites[ESprite::Shield] = sf::Sprite(m_textueT, sf::IntRect{ 316,213,44,32 });
	m_sprites[ESprite::Shield_Damaged_1] = sf::Sprite(m_textueT, sf::IntRect{ 480,210,44,32 });
	m_sprites[ESprite::Shield_Damaged_2] = sf::Sprite(m_textueT, sf::IntRect{ 428,210,36,32 });
	m_sprites[ESprite::Shield_Damaged_3] = sf::Sprite(m_textueT, sf::IntRect{ 373,211,44,32 });
	m_sprites[ESprite::Shield_Damaged_4] = sf::Sprite(m_textueT, sf::IntRect{ 480,265,44,32 });
}

CAssetManager::CAssetManager()
{
	// loading all the textures from the file
	m_textueT.loadFromFile("space_invaders_sprites.png");

	// position and area data to point to the correct sprite areas
	LoadSprites();
}

sf::Sprite CAssetManager::GetSprite(ESprite item)
{
	// search each map for the item
	// searching backgrounds
	if (m_sprites.find(item) != m_sprites.end())
	{
		return m_sprites[item];
	}

	// return the copy of the sprite here if found in the map
	return sf::Sprite();
}

