#pragma once

// internal includes
#include "EventHandler.h"
#include "Character.h"
#include "InputHandler.h"

constexpr float MAXSPEED = 100.0f;
constexpr float PLAYER_ANIMATION_DELAY = 1.0f;

#define RUNSPRITES 3
#define DEATHSPRITES 7
 
class CEngine;

class CPlayer : public CCharacter
{
private:	
	CButton m_input;
	bool m_hasKey;

	// death animation texture
	bool m_isDeathAnimationRunning;
	std::vector<sf::Texture> m_deathTexture;

	// listener function objects
	FUNCTIONHANDLER m_playerKeyPressedListnerCB;
	FUNCTIONHANDLER m_playerKeyReleasedListnerCB;

	// listener functions
	void PlayerKeyPressedListner(sf::Event event);
	void PlayerKeyReleasedListner(sf::Event event);

	void KeyPressAction(const float& deltaTime);
	void KeyReleaseAction(const float& deltaTime);

public:
	CPlayer() = delete;
	CPlayer(CEngine& engine);

	// initialize (override)
	void InitTexture();
	void InitSprite();
	void InitCharacter(float initialPositionX, float initialPositionY);

	// Input Getter
	inline CButton& GetInput() { return m_input; };

	// player movement
	void Move(const float& deltaTime); // (override)
	void KeyAction(const float& deltaTime);

	// animation
	void RunAnimation(float animationDelay, const float& deltaTime);
	void RunDeathAnimation(float animationDelay, const float& deltaTime);
	void StartAnimation();
	void StopAnimation();
	void SetPlayerMovementTexture();

	// acquire key
	void AcquireKey();
	inline bool HasKey() { return m_hasKey; };

	// update and render (override)
	void Update(const float& deltaTime);
	void Render(sf::RenderTarget& target);

};

