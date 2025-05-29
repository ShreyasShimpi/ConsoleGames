#pragma once

//external includes
#include <SFML/Graphics.hpp>
#include <unordered_map>

// enum for all the sprites in the game
enum class EItems
{
	// background level image
	Background_1_1,

	// enemies (goomba)
	Goomba_1,
	Goomba_2,
	Goomba_Death,

	// enemies (turtle)
	Turtle_L_1,
	Turtle_L_2,
	Turtle_Shell,

	Mushroom_Red,
	// power ups
	Mushroom_Green,

	Fire_Flower_1,
	Fire_Flower_2,
	Fire_Flower_3,
	Fire_Flower_4,

	Fire_Ball,
	Fire_Ball_Explosion_1,
	Fire_Ball_Explosion_2,
	Fire_Ball_Explosion_3,

	Star_1,
	Star_2,
	Star_3,
	Star_4,

	// blocks
	Question_Block_1,
	Question_Block_2,
	Question_Block_3,
	Question_Block_4,

	Empty_Block,
	Floor_Brick,
	Solid_Block,

	// coins
	Coin_1,
	Coin_2,
	Coin_3,
	Coin_4,

	Block_Coin_1,
	Block_Coin_2,
	Block_Coin_3,
	Block_Coin_4,

	// brick
	Brick,
	Brick_Exploded,
	brick_Fragment_1,
	brick_Fragment_2,

	// flag
	Flag,
	Flag_Ball_Top,
	Flag_Pole,

	// pipe
	Pipe_Opening,
	Pipe_Body,
	Side_Pipe_Opening,
	Side_Pipe_Body,

	// mario small
	Mario_Running_R_1,
	Mario_Running_R_2,
	Mario_Running_R_3,
	Mario_Standing_R,
	Mario_Drag_R,
	Mario_Jump_R,
	Mario_Death_R,

	// mario invincible
	Mario_Star1_Running_R_1,
	Mario_Star1_Running_R_2,
	Mario_Star1_Running_R_3,
	Mario_Star1_Standing_R,
	Mario_Star1_Drag_R,
	Mario_Star1_Jump_R,
	Mario_Star1_Crouch_R,

	Mario_Grown,

	// mario big
	Mario_Big_Running_R_1,
	Mario_Big_Running_R_2,
	Mario_Big_Running_R_3,
	Mario_Big_Standing_R,
	Mario_Big_Drag_R,
	Mario_Big_Jump_R,
	Mario_Big_Crouch_R,

	// mario fire
	Mario_Fire_Running_R_1,
	Mario_Fire_Running_R_2,
	Mario_Fire_Running_R_3,
	Mario_Fire_Standing_R,
	Mario_Fire_Drag_R,
	Mario_Fire_Jump_R,
	Mario_Fire_Crouch_R,
	Mario_Fire_Death_R,
};

class CAssetManager
{
private:
	// level background
	sf::Texture m_backgroundLevel_1_1_T;

	// all textures
	sf::Texture m_itemsAndObjectsT;
	sf::Texture m_marioT;
	sf::Texture m_enemiesT;
	sf::Texture m_tilesT;

	// maps storing all the sprites
	std::unordered_map<EItems, sf::Sprite> m_backgroundSprites;
	std::unordered_map<EItems, sf::Sprite> m_enemiesSprites;
	std::unordered_map<EItems, sf::Sprite> m_marioSprites;
	std::unordered_map<EItems, sf::Sprite> m_tileSprites;
	std::unordered_map<EItems, sf::Sprite> m_itemAndObjectSprites;

	// private functions
	void LoadSprites();

public:
	// constructor
	CAssetManager();

	// return a copy of the sprite requested
	sf::Sprite GetSprite(EItems item);
};

