
#pragma once
#include<SFML/Graphics.hpp>
#include <iostream>
#include "CGame.h"

class CAssetManager;
class CAnimationManager;

// mario direction
enum class EFacing
{
	Right, Left
};

// mario state
enum class EMarioState
{
	Alive, Dead, Growing, FallenInPit, OnFire
};

class CPlayer
{
private:
	sf::Sprite m_playerSprite; // store mario sprite
	sf::Vector2f m_targetVelocity;
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;
	EFacing m_facing;
	EMarioState m_state;

	void Move(const float& deltaTime);
	void OnKeyPressed(sf::Event event);
	void OnKeyReleased(sf::Event event);

	//CInput m_input;
	FUNCTIONHANDLER onKeyPressedCB;
	FUNCTIONHANDLER onKeyReleasedCB;
	CGame& m_game;

	CAnimationManager* m_animationManager;
	CAssetManager* m_assetManager;

public:
	CPlayer(CAssetManager& assetmanager, CGame& game, CAnimationManager& animationManager);
	~CPlayer();

	// getters
	inline sf::Sprite& GetSprite() { return m_playerSprite; }
	inline const sf::Vector2f& GetPosition() { return m_position; };
	inline sf::Vector2f GetVelocity() { return m_velocity; };
	inline float GetWidth() { return m_playerSprite.getGlobalBounds().width; };
	inline float GetHeight() { return m_playerSprite.getGlobalBounds().height; };
	inline const EMarioState& GetMarioState() { return m_state; };

	// setters
	void SetPosition(const sf::Vector2f position);
	void SetVelocity(sf::Vector2f velocity);
	void SetVelocityX(const float velocityX);
	void SetVelocityY(const float velocityY);
	void SetMarioState(const EMarioState& state);

	bool m_isJumping; // check for jumping 

	//Functions
	void Update(const float& deltaTime);
	void Render(sf::RenderTarget& target);

	// used for death
	void MakeDead();
	void UpdateDeath(const float& deltaTime);

};