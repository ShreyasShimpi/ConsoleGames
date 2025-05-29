#pragma once
// external includes
#include <vector>
#include <memory>

// internal includes
#include "Player.h"
#include "Ducks.h"
#include "Defines.h"

// game state
enum class EGameState
{
	MainMenu,
	Player1Turn,
	Player2Turn,
	DuckHit,
	TurnOver,
	GameOver
};



class CEngine;

class CSpawnManager
{
private:
	CEngine& m_engine;

	// winner
	sf::Text m_message;

	// player 1
	int m_player1Score;
	int m_player1Shots;

	// player 2
	int m_player2Score;
	int m_player2Shots;

	// game state
	EGameState m_gameState;

	// shooter
	std::unique_ptr<CShooter> m_shooter;

	// shooter
	std::unique_ptr<CDucks> m_duck;

	// foreground
	sf::Sprite m_fgSprite;
	sf::Texture m_fgTexture;
	void LoadForeground();

	// Randomize Position and angle
	void RandomizeDuck();

	// collision
	void ChcekBoundaryforDuck();
	void ChcekBulletDuckColiision();

	// display message
	void DisplayMessage(std::string massage, sf::Color color, sf::Vector2f position, unsigned int charSize, sf::RenderTarget& target);


public:
	// constructor
	CSpawnManager() = delete;
	CSpawnManager(CEngine& game, unsigned int width, unsigned int height);
	~CSpawnManager();

	//getter
	inline const EGameState GetGameState() { return m_gameState; };

	// setter
	void SetGameState(EGameState state);
	void ResetGameProperties();

	// Update and render
	void UpdateSpawns(const float& deltaTime);
	void RenderSpawns(sf::RenderTarget& target);

};

