#pragma once

// external includes
#include <vector>

// internal includes
#include "EventHandler.h"
#include "InputHandler.h"

constexpr float MAXSPEED = 500.0f;
constexpr float ACCELERATION = 5000.0f;

class CEngine;

class CShooter
{
private:
	// cross hair
	sf::Sprite m_crosshairSprite;
	sf::Texture m_crosshairTexture;


	// input handler
	CButton m_keyInput;
	CMouse m_mouseInput;
	bool m_isBulletShot = false;

	// snake body sprites

	// listener function objects
	// listener function objects
	FUNCTIONHANDLER m_playerKeyPressedListnerCB;
	FUNCTIONHANDLER m_playerKeyReleasedListnerCB;
	FUNCTIONHANDLER m_playerMouseClickedListnerCB;
	FUNCTIONHANDLER m_playerMouseClickReleasedListnerCB;
	FUNCTIONHANDLER m_playerMouseMovedListnerCB;

	// listener functions
	void PlayerKeyPressedListner(sf::Event event);
	void PlayerKeyReleasedListner(sf::Event event);
	void PlayerMouseClickedListner(sf::Event event);
	void PlayerMouseClickReleasedListner(sf::Event event);
	void PlayerMouseMovedListner(sf::Event event);

	void KeyPressAction(const float& deltaTime);
	void MouseClickeAction(const float& deltaTime);
	void MouseMovedAction(const float& deltaTime);

public:
	CShooter() = delete;
	CShooter(CEngine& engine);

	
	// initialize
	void InitShooter(float paddle1posX, float paddle1posY, float paddle2posX, float paddle2posY);

	// Getters
	inline CButton& GetKeyInput() { return m_keyInput; };
	inline CMouse& GetMouseInput() { return m_mouseInput; };
	inline const bool IsBulletShot() { return m_isBulletShot; };


	// player movement
	void Move(const float& deltaTime); // (override)
	void InputAction(const float& deltaTime);

	// update and render (override)
	void Update(const float& deltaTime);
	void Render(sf::RenderTarget& target);

};