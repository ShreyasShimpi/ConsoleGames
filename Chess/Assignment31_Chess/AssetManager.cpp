#include "AssetManager.h"

void CAssetManager::LoadSprites()
{
	//chess board
	m_sprites["BG"] = sf::Sprite(m_backgroundT);

	// chess pieces 
	// black
	m_sprites["BP"] = sf::Sprite(m_piecesT, sf::IntRect{ 869,34,80,80 });
	m_sprites["BR"] = sf::Sprite(m_piecesT, sf::IntRect{ 367,34,80,80 });
	m_sprites["BN"] = sf::Sprite(m_piecesT, sf::IntRect{ 702,34,80,80 });

	m_sprites["BB"] = sf::Sprite(m_piecesT, sf::IntRect{ 528,26,90,90 });
	m_sprites["BB"].setScale(0.88f, 0.88f);

	m_sprites["BQ"] = sf::Sprite(m_piecesT, sf::IntRect{ 192,25,90,90 });
	m_sprites["BQ"].setScale(0.88f, 0.88f);

	m_sprites["BK"] = sf::Sprite(m_piecesT, sf::IntRect{ 30,28,80,80 });

	// white
	m_sprites["WP"] = sf::Sprite(m_piecesT, sf::IntRect{ 869,178,80,80 });
	m_sprites["WR"] = sf::Sprite(m_piecesT, sf::IntRect{ 367,178,80,80 });
	m_sprites["WN"] = sf::Sprite(m_piecesT, sf::IntRect{ 702,178,80,80 });

	m_sprites["WB"] = sf::Sprite(m_piecesT, sf::IntRect{ 530,168,90,90 });
	m_sprites["WB"].setScale(0.88f, 0.88f);

	m_sprites["WQ"] = sf::Sprite(m_piecesT, sf::IntRect{ 194,168,90,90 });
	m_sprites["WQ"].setScale(0.88f, 0.88f);

	m_sprites["WK"] = sf::Sprite(m_piecesT, sf::IntRect{ 32,172,80,80 });
}
CAssetManager::CAssetManager()
{
	// loading all the textures from the file
	m_backgroundT.loadFromFile("Sprites/chessboard.png");
	m_piecesT.loadFromFile("Sprites/pieces.png");

	// position and area data to point to the correct sprite areas
	LoadSprites();
}

sf::Sprite CAssetManager::GetSprite(const std::string& spriteCode)
{
	// search each map for the item
	// searching backgrounds

	if (m_sprites.find(spriteCode) != m_sprites.end())
	{
		return m_sprites[spriteCode];
	}

	// return the copy of the sprite here if found in the map
	return sf::Sprite();
}

