#pragma once
// external includes
#include <vector>
#include <memory>

// internal includes
#include "Player.h"
#include "Defines.h"

class CEngine;

class CSpawnManager
{
private:
	CEngine& m_engine;

	// winner
	sf::Text m_message;
	int m_score1;
	int m_score2;
	bool m_isGameRunning;


	// paddle
	CPaddles* m_paddle;

	// ball
	sf::CircleShape m_ball;
	short m_angle;

	// background
	sf::Sprite m_bgSprite;
	sf::Texture m_bgTexture;
	void LoadBackground();


	// Randomize Position
	void RandomizeAngle();

	// collision
	void CheckCollisionWithBall();
	void CheckCollisionWithBoundary();

	// display message
	void DisplayMessage(std::string massage, sf::Color color, sf::Vector2f position, unsigned int charSize, sf::RenderTarget& target);


public:
	// constructor
	CSpawnManager() = delete;
	CSpawnManager(CEngine& game, unsigned int width, unsigned int height);
	~CSpawnManager();

	//getter
	inline const bool IsGameRunning() { return m_isGameRunning; };

	// setter
	void SetGameRunning(bool state);
	void ResetGameState();
	
	// save and load (serialization)
	void SaveGameState();
	void LoadGameState();

	// Update and render
	void UpdateSpawns(const float& deltaTime);
	void RenderSpawns(sf::RenderTarget& target);

};

