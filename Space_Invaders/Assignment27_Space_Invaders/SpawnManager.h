#pragma once
// external includes
#include <vector>
#include <memory>

// internal includes
#include "Player.h"
#include "Enemy.h"
#include "Shield.h"
#include "Defines.h"

class CAssetManager;

// game state
enum class EGameState
{
	MainMenu,
	InGame,
	Winner,
	GameOver
};

class CEngine;

class CSpawnManager
{
private:
	CEngine& m_engine;
	CAssetManager* m_assetManager;
	EGameState m_gameState;
	// menu graphic
	sf::Sprite m_menu;

	// player
	std::unique_ptr<CPlayer> m_player;
	short m_playerScore;
	std::vector<sf::Sprite> m_playerLives;

	// enemy
	std::vector<std::unique_ptr<CEnemy>> m_enemies;

	// enemy bullet
	sf::Sprite m_enemyBulletSprite;
	float m_enemyBulletVelocity;
	bool m_isEnemyBulletShot;
	short m_enemiesAlive;
	bool m_isMovingLeft;
	bool m_moveDown;
	float m_elapsedTime;

	// shields
	std::vector<std::unique_ptr<CShield>> m_shields;

	// collision
	void CheckBoundaryForAll();

	void CheckPlayerBulletEnemyCollision();
	void CheckPlayerBulletShieldColiision();

	void CheckEnemyDefenceCollision();
	void CheckEnemyBulletShieldCollision();
	void CheckEnemyBulletPlayerCollision();

	// text
	sf::Text m_message;
	void DisplayMessage(std::string massage, sf::Color color, bool isCenter, sf::Vector2f position, unsigned int charSize, sf::RenderTarget& target);

	// function
	void MoveEnemyGrid();
	void AddToScore(EEnemyType type);
	void ShootBullet(const float& deltaTime);

public:
	// constructor
	CSpawnManager() = delete;
	CSpawnManager(CEngine& game);
	~CSpawnManager();

	// Update and render
	void UpdateSpawns(const float& deltaTime);
	void RenderSpawns(sf::RenderTarget& target);
};

