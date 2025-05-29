#pragma once
// external includes
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>

// internal includes
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include "KeyDoor.h"
#include "Bomb.h"


class CEngine;

class CSpawnManager
{
private:
	CEngine& m_engine;

	// winner
	bool m_isWinner;
	bool m_isDead;
	sf::Text m_winnerMessage;

	// player
	CPlayer* m_player;

	// enemies
	std::vector<CEnemy*> m_enemies;

	// walls
	std::vector<CSolidWall*> m_solidWall;
	std::vector<CBrickWall*> m_brickWall;
	std::vector<sf::Vector2f> m_brickWallPositions;
	
	// door and key
	CKey* m_key;
	CDoor* m_door;

	// bomb
	bool m_isBombPlaced;
	CBomb* m_bomb;
	bool m_isExploding;
	float m_bombTime;
	std::vector<sf::Texture> m_expTexture;
	sf::Sprite m_expSprite;

	FUNCTIONHANDLER m_playerKeyPressedListnerCB;// listener function objects
	void BombKeyPressedListner(sf::Event event);// listener functions
	void BombAction(const float& deltaTime);
	void ActivateBomb(const float& deltaTime);
	void RunExplosionAnimation(float animationDelay);

	// background
	sf::Sprite m_bgSprite;
	sf::Texture m_bgTexture;

	// foreground tiles
	sf::Sprite m_fgTilesSprite;
	sf::Texture m_fgTilesTexture;

public:
	// constructor
	CSpawnManager(CEngine& game, unsigned int width, unsigned int height);
	~CSpawnManager();

	// Update and render
	void UpdateSpawns(const float& deltaTime);
	void RenderSpawns(sf::RenderTarget& target);

	// collision Check
	void CheckSolidWallCollision(CCharacter& character, const float& deltatime);
	void CheckBrickWallCollision(CCharacter& character, const float& deltatime);
	void CheckBoundaryCollision(CCharacter& character, const float& deltatime);

	// collision bomb
	void CheckBombBrickWallCollision();
	void CheckBombPlayerCollision();
	void CheckBombEnemyCollision();
	void CheckPlayerEnemyCollision();

	// check key
	void CheckKeyCollision();
	void CheckDoorCollision();

	// background Load
	void LoadBackground();
	void LoadForeGroundTiles();
	void InitExpTexture();

	// extras
	void InitBrickWalls();
	void InitSolidWalls();
	void InitEnemies();
	void RandomizeKeyAndDoor();

	// player text message
	void DisplayMessage(std::string massage, sf::Color color, sf::Vector2f position, unsigned int charSize, sf::RenderTarget& target);

};

