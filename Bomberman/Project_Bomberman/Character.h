#pragma once
// internal includes
#include "RectShape.h"

enum class ECharacterType
{
	NONE,
	PLAYER,
	ENEMY
};

class CCharacter : public CRectShape
{
protected:

	ECharacterType m_characterType;
	// vector of texture for animation (not in rectshape)
	std::vector<sf::Texture> m_texture;

	// non static objects
	sf::Vector2f m_velocity;
	sf::Vector2f m_targetVelocity;

	// animation variables
	bool m_isAnimationRunning;
	float m_nextFrameDelay;
	float m_totalTime;

public:
	// constructor/destructor
	CCharacter();

	// initialize
	virtual void InitTexture() = 0;
	virtual void InitSprite() = 0;
	virtual void InitCharacter(float initialPositionX, float initialPositionY) = 0;

	// getter
	inline sf::Vector2f GetVelocity() { return m_velocity; };
	inline const ECharacterType GetCharacterType() { return m_characterType; };

	// setter
	void SetVelocity(sf::Vector2f velocity);
	void SetTargetVelocityX(float velX);
	void SetTargetVelocityY(float velY);

	// movement
	virtual void Move(const float& deltaTime) = 0;


	// update and render
	virtual void Update(const float& deltaTime) = 0;
	virtual void Render(sf::RenderTarget& target) = 0;
};

