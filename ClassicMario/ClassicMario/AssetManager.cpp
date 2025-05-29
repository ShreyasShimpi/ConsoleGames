#include "AssetManager.h"

void CAssetManager::LoadSprites()
{
	// loading level background sprite
	m_backgroundSprites[EItems::Background_1_1] = sf::Sprite(m_backgroundLevel_1_1_T);
	m_backgroundSprites[EItems::Background_1_1].setTextureRect(sf::IntRect(0, 0, 300, 224));

	// loading enemy sprites
	m_enemiesSprites[EItems::Goomba_1] = sf::Sprite(m_enemiesT, sf::IntRect{ 0,16,16,16 });
	m_enemiesSprites[EItems::Goomba_2] = sf::Sprite(m_enemiesT, sf::IntRect{ 16,16,16,16 });
	m_enemiesSprites[EItems::Goomba_Death] = sf::Sprite(m_enemiesT, sf::IntRect{ 32,16,16,16 });
	m_enemiesSprites[EItems::Turtle_L_1] = sf::Sprite(m_enemiesT, sf::IntRect{ 96,8,16,24 });
	m_enemiesSprites[EItems::Turtle_L_2] = sf::Sprite(m_enemiesT, sf::IntRect{ 112,8,16,24 });
	m_enemiesSprites[EItems::Turtle_Shell] = sf::Sprite(m_enemiesT, sf::IntRect{ 160,16,16,16 });


	// loading player sprites
	m_marioSprites[EItems::Mario_Running_R_1] = sf::Sprite(m_marioT, sf::IntRect{ 80, 32, 16, 16 });
	m_marioSprites[EItems::Mario_Running_R_2] = sf::Sprite(m_marioT, sf::IntRect{ 96, 32, 16, 16 });
	m_marioSprites[EItems::Mario_Running_R_3] = sf::Sprite(m_marioT, sf::IntRect{ 112, 32, 16, 16 });

	m_marioSprites[EItems::Mario_Standing_R] = sf::Sprite(m_marioT, sf::IntRect{ 176, 32, 16, 16 });
	m_marioSprites[EItems::Mario_Drag_R] = sf::Sprite(m_marioT, sf::IntRect{ 128, 32, 16, 16 });
	m_marioSprites[EItems::Mario_Jump_R] = sf::Sprite(m_marioT, sf::IntRect{ 144, 32, 16, 16 });
	m_marioSprites[EItems::Mario_Death_R] = sf::Sprite(m_marioT, sf::IntRect{ 160, 32, 16, 16 });


	m_marioSprites[EItems::Mario_Star1_Running_R_1] = sf::Sprite(m_marioT, sf::IntRect{ 80,144,16,32 });
	m_marioSprites[EItems::Mario_Star1_Running_R_2] = sf::Sprite(m_marioT, sf::IntRect{ 96,144,16,32 });
	m_marioSprites[EItems::Mario_Star1_Running_R_3] = sf::Sprite(m_marioT, sf::IntRect{ 112,144,16,32 });

	m_marioSprites[EItems::Mario_Star1_Standing_R] = sf::Sprite(m_marioT, sf::IntRect{ 176,144,16,32 });
	m_marioSprites[EItems::Mario_Star1_Drag_R] = sf::Sprite(m_marioT, sf::IntRect{ 128,144,16,32 });
	m_marioSprites[EItems::Mario_Star1_Jump_R] = sf::Sprite(m_marioT, sf::IntRect{ 144,144,16,32 });
	m_marioSprites[EItems::Mario_Star1_Crouch_R] = sf::Sprite(m_marioT, sf::IntRect{ 160,154,16,22 });

	m_marioSprites[EItems::Mario_Grown] = sf::Sprite(m_marioT, sf::IntRect{ 320, 8, 16, 24 });

	m_marioSprites[EItems::Mario_Big_Running_R_1] = sf::Sprite(m_marioT, sf::IntRect{ 80, 0, 16, 32 });
	m_marioSprites[EItems::Mario_Big_Running_R_1] = sf::Sprite(m_marioT, sf::IntRect{ 96, 0, 16, 32 });
	m_marioSprites[EItems::Mario_Big_Running_R_1] = sf::Sprite(m_marioT, sf::IntRect{ 112, 0, 16, 32 });

	m_marioSprites[EItems::Mario_Big_Standing_R] = sf::Sprite(m_marioT, sf::IntRect{ 176, 0, 16, 32 });
	m_marioSprites[EItems::Mario_Big_Drag_R] = sf::Sprite(m_marioT, sf::IntRect{ 128, 0, 16, 32 });
	m_marioSprites[EItems::Mario_Big_Jump_R] = sf::Sprite(m_marioT, sf::IntRect{ 144, 0, 16, 32 });
	m_marioSprites[EItems::Mario_Big_Crouch_R] = sf::Sprite(m_marioT, sf::IntRect{ 160, 10, 16, 22 });

	m_marioSprites[EItems::Mario_Fire_Running_R_1] = sf::Sprite(m_marioT, sf::IntRect{ 80, 48, 16, 32 });
	m_marioSprites[EItems::Mario_Fire_Running_R_1] = sf::Sprite(m_marioT, sf::IntRect{ 96, 48, 16, 32 });
	m_marioSprites[EItems::Mario_Fire_Running_R_1] = sf::Sprite(m_marioT, sf::IntRect{ 112, 48, 16, 32 });

	m_marioSprites[EItems::Mario_Fire_Standing_R] = sf::Sprite(m_marioT, sf::IntRect{ 176, 48, 16, 32 });
	m_marioSprites[EItems::Mario_Fire_Drag_R] = sf::Sprite(m_marioT, sf::IntRect{ 128, 48, 16, 32 });
	m_marioSprites[EItems::Mario_Fire_Jump_R] = sf::Sprite(m_marioT, sf::IntRect{ 144, 48, 16, 32 });
	m_marioSprites[EItems::Mario_Fire_Crouch_R] = sf::Sprite(m_marioT, sf::IntRect{ 160, 58, 16, 22 });
	m_marioSprites[EItems::Mario_Fire_Death_R] = sf::Sprite(m_marioT, sf::IntRect{ 160, 80, 16, 16 });

	// // loading tile sprites
	m_tileSprites[EItems::Brick] = sf::Sprite(m_tilesT, sf::IntRect{ 16,0,16,16 });
	m_tileSprites[EItems::Empty_Block] = sf::Sprite(m_tilesT, sf::IntRect{ 48,0,16,16 });
	m_tileSprites[EItems::Floor_Brick] = sf::Sprite(m_tilesT, sf::IntRect{ 0,0,16,16 });
	m_tileSprites[EItems::Solid_Block] = sf::Sprite(m_tilesT, sf::IntRect{ 0,16,16,16 });
	m_tileSprites[EItems::Flag_Ball_Top] = sf::Sprite(m_tilesT, sf::IntRect{ 260,136,8,8 });
	m_tileSprites[EItems::Flag_Pole] = sf::Sprite(m_tilesT, sf::IntRect{ 263,144,2,16 });

	m_tileSprites[EItems::Pipe_Opening] = sf::Sprite(m_tilesT, sf::IntRect{ 128,0,32,16 });
	m_tileSprites[EItems::Pipe_Body] = sf::Sprite(m_tilesT, sf::IntRect{ 144,0,32,16 });
	m_tileSprites[EItems::Side_Pipe_Opening] = sf::Sprite(m_tilesT, sf::IntRect{ 32,160, 48, 32 });
	m_tileSprites[EItems::Side_Pipe_Body] = sf::Sprite(m_tilesT, sf::IntRect{ 0,176,16,16 });


	// loading objects sprites
	m_itemAndObjectSprites[EItems::Mushroom_Red] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 0,0,16,16 });
	m_itemAndObjectSprites[EItems::Mushroom_Green] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 16, 0, 16, 16 });
	m_itemAndObjectSprites[EItems::Fire_Flower_1] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 0, 32, 16, 16 });
	m_itemAndObjectSprites[EItems::Fire_Flower_2] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 16, 32, 16, 16 });
	m_itemAndObjectSprites[EItems::Fire_Flower_3] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 32, 32, 16, 16 });
	m_itemAndObjectSprites[EItems::Fire_Flower_4] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 48, 32, 16, 16 });
	m_itemAndObjectSprites[EItems::Fire_Ball] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 96, 144, 8, 8 });
	m_itemAndObjectSprites[EItems::Fire_Ball_Explosion_1] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 112, 144, 16, 16 });
	m_itemAndObjectSprites[EItems::Fire_Ball_Explosion_2] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 112, 160, 16, 16 });
	m_itemAndObjectSprites[EItems::Fire_Ball_Explosion_3] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 112, 176, 16, 16 });
	m_itemAndObjectSprites[EItems::Star_1] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 0, 48, 16, 16 });
	m_itemAndObjectSprites[EItems::Star_2] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 16, 48, 16, 16 });
	m_itemAndObjectSprites[EItems::Star_3] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 32, 48, 16, 16 });
	m_itemAndObjectSprites[EItems::Star_4] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 48, 48, 16, 16 });

	m_itemAndObjectSprites[EItems::Question_Block_1] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 0,80,16,16 });
	m_itemAndObjectSprites[EItems::Question_Block_2] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 16,80,16,16 });
	m_itemAndObjectSprites[EItems::Question_Block_3] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 32,80,16,16 });
	m_itemAndObjectSprites[EItems::Question_Block_4] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 48,80,16,16 });

	m_itemAndObjectSprites[EItems::Coin_1] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 0,96,16,16 });
	m_itemAndObjectSprites[EItems::Coin_2] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 16,96,16,16 });
	m_itemAndObjectSprites[EItems::Coin_3] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 32,96,16,16 });
	m_itemAndObjectSprites[EItems::Coin_4] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 48,96,16,16 });

	m_itemAndObjectSprites[EItems::Block_Coin_1] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 0,112,16,16 });
	m_itemAndObjectSprites[EItems::Block_Coin_2] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 16,112,16,16 });
	m_itemAndObjectSprites[EItems::Block_Coin_3] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 32,112,16,16 });
	m_itemAndObjectSprites[EItems::Block_Coin_4] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 48,112,16,16 });

	m_itemAndObjectSprites[EItems::Brick_Exploded] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 64,0,16,16 });
	m_itemAndObjectSprites[EItems::brick_Fragment_1] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 64,16,16,16 });
	m_itemAndObjectSprites[EItems::brick_Fragment_2] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 64,32,16,16 });

	m_itemAndObjectSprites[EItems::Flag] = sf::Sprite(m_itemsAndObjectsT, sf::IntRect{ 128,32,16,16 });
}

CAssetManager::CAssetManager()
{
	// loading all the textures from the file
	m_itemsAndObjectsT.loadFromFile("resources\\graphics\\item_objects.png");
	m_marioT.loadFromFile("resources\\graphics\\mario_bros.png");
	m_enemiesT.loadFromFile("resources\\graphics\\enemies.png");
	m_tilesT.loadFromFile("resources\\graphics\\tile_set.png");

	// loading level background
	m_backgroundLevel_1_1_T.loadFromFile("resources\\graphics\\level_1.png");
	
	// position and area data to point to the correct sprite areas
	LoadSprites();
}

sf::Sprite CAssetManager::GetSprite(EItems item)
{
	// search each map for the item
	// searching backgrounds
	if (m_backgroundSprites.find(item) != m_backgroundSprites.end())
	{
		return m_backgroundSprites[item];
	}
	// searching enemy sprites
	if (m_enemiesSprites.find(item) != m_enemiesSprites.end())
	{
		return m_enemiesSprites[item];
	}

	// searching Mario sprites
	if (m_marioSprites.find(item) != m_marioSprites.end())
	{
		return m_marioSprites[item];
	}

	// searching tile sprites
	if (m_tileSprites.find(item) != m_tileSprites.end())
	{
		return m_tileSprites[item];
	}

	// searching enemy sprites
	if (m_itemAndObjectSprites.find(item) != m_itemAndObjectSprites.end())
	{
		return m_itemAndObjectSprites[item];
	}
	// return the copy of the sprite here if found in the map
	return sf::Sprite();
}

