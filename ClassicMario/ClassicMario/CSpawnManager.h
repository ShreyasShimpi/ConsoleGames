#pragma once
#include "CGame.h"
#include "AssetManager.h"
#include "CAnimationManager.h"
#include"collision.h"
#include <memory>
#include "Goomba.h"
#include "Turtle.h"

class CPlayer;
class CGoomba;
class CLevelData;
class CQuestionBlock;
class CBrickBlock;
class CGrowthPower;
class CFireFlower;
class CStarPower;


//enum useful for enemies
enum class EEnemies
{
	GOOMBA, KOOPATROOPA
};

//
class CSpawnManager
{
public:

	CSpawnManager() = delete;
	CSpawnManager(CGame& game); 
	~CSpawnManager();

	//Used for updating game variables
	void Update(const float& deltaTime, sf::RenderWindow& window);
	
	//Updates whichever character is dead or alive
	void UpdateAlive(const float& deltaTime, sf::RenderWindow& window);

	//used for drawing everything on the window
	void Draw();
	
	//Used to move the camera
	void AdjustView();

	//used for checking the window boundaries
	void CheckWindowColiision();

	//used for initiliazing goombas
	void CreateGoombas();

	//Updating Collisions
	void UpdateCollisions(const float& deltaTime, sf::RenderWindow& window);
private:

	// references of different classes
	CGame& m_game;
	std::shared_ptr<CPlayer> m_player;

	//vector of emenies
	std::vector<std::shared_ptr<CGoomba>> m_goombas;
	std::shared_ptr<CTurtle> m_koopaTroopa;

	// vector of different types of blocks
	std::vector<CQuestionBlock> m_questionBlocks;
	std::vector<CBrickBlock> m_brickBlocks;

	//vector of different types of collectibles
	std::vector<CGrowthPower> m_growthPowers;
	std::vector<CFireFlower> m_fireflowers;
	std::vector<CStarPower> m_stars;
	
	//contains the level data in the form of float rects
	std::shared_ptr<CLevelData> m_levelData;

	// pointer to asset manager class
	std::shared_ptr<CAssetManager> m_assetManager;

	//pointer to animation manager class
	std::shared_ptr<CAnimationManager> m_animationManager;

	//pointer to collision manager class
	std::shared_ptr<CCollision> m_collisionManager;
	

	CTime m_time;


};

