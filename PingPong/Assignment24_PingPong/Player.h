#pragma once

// external includes
#include <vector>

// internal includes
#include "EventHandler.h"
#include "InputHandler.h"

constexpr float MAXSPEED = 500.0f;
constexpr float ACCELERATION = 5000.0f;

class CEngine;

class CPaddles
{
private:
	// input handler
	CButton m_input;

	// snake body sprites
	sf::RectangleShape m_paddle1;
	sf::RectangleShape m_paddle2;
	void CreatePaddles();

	// velocity (only Y)
	float m_paddle1Velocity;
	float m_paddle1TargetVelocity;
	float m_paddle2Velocity;
	float m_paddle2TargetVelocity;

	// listener function objects
	// listener function objects
	FUNCTIONHANDLER m_playerKeyPressedListnerCB;
	FUNCTIONHANDLER m_playerKeyReleasedListnerCB;

	// listener functions
	void PlayerKeyPressedListner(sf::Event event);
	void PlayerKeyReleasedListner(sf::Event event);

	void KeyPressAction(const float& deltaTime);
	void KeyReleaseAction(const float& deltaTime);

public:
	CPaddles() = delete;
	CPaddles(CEngine& engine);

	// initialize
	void InitPaddles(float paddle1posX, float paddle1posY, float paddle2posX, float paddle2posY);

	// Getters
	inline CButton& GetInput() { return m_input; };
	inline sf::FloatRect GetPaddle1Bounds() { return m_paddle1.getGlobalBounds(); };
	inline sf::FloatRect GetPaddle2Bounds() { return m_paddle2.getGlobalBounds(); };

	// setter
	void SetPaddle1Velocity(float velocity);
	void SetPaddle2Velocity(float velocity);
	void SetPaddle1Position(sf::Vector2f position);
	void SetPaddle2Position(sf::Vector2f position);

	// player movement
	void Move(const float& deltaTime); // (override)
	void KeyAction(const float& deltaTime);

	// update and render (override)
	void Update(const float& deltaTime);
	void Render(sf::RenderTarget& target);

};