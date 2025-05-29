#pragma once

// external includes
#include <vector>

// internal includes
#include "EventHandler.h"
#include "InputHandler.h"
#include "Defines.h"

class CEngine;
class CAssetManager;

class CPlayer
{
private:
	CAssetManager* m_assetManager;

	// player
	sf::Sprite m_playerSprite;
	float m_playerVelocity; // only horizontal

	// bullet
	sf::Sprite m_bulletSprite;
	float m_bulletVelocity; // only vertical

	// input handler
	CButton m_keyInput;
	bool m_isBulletShot = false;

	// listener function objects
	FUNCTIONHANDLER m_playerKeyPressedListnerCB;
	FUNCTIONHANDLER m_playerKeyReleasedListnerCB;

	// listener functions
	void PlayerKeyPressedListner(sf::Event event);
	void PlayerKeyReleasedListner(sf::Event event);

	void KeyPressAction(const float& deltaTime);

public:
	CPlayer() = delete;
	CPlayer(const sf::Vector2f playerPosition, CEngine& engine, CAssetManager& assetmanager);
	
	// Getters
	inline CButton& GetKeyInput() { return m_keyInput; };
	inline const sf::Vector2f& GetPlayerPosition() { return m_playerSprite.getPosition(); };
	inline const sf::FloatRect& GetBulletBounds() { return m_bulletSprite.getGlobalBounds(); };
	inline const sf::FloatRect& GetPlayerBounds() { return m_playerSprite.getGlobalBounds(); };
	inline const bool IsBulletShot() { return m_isBulletShot; };

	// Setter
	void SetPlayerPosition(const sf::Vector2f& position);
	void ResetBullet();

	// player movement
	void Move(const float& deltaTime);

	// update and render
	void Update(const float& deltaTime);
	void Render(sf::RenderTarget& target);

};